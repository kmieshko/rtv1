/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 11:04:49 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/06 11:04:50 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_center(t_cylinder *cylinder, char *tmp)
{
	char **del;

	if (ft_count_coord(tmp) == 0)
		ft_incorrect("cylinder");
	del = ft_strsplit(tmp, ',');
	cylinder->xyz[0] = ft_atod(del[0]);
	cylinder->xyz[1] = ft_atod(del[1]);
	cylinder->xyz[2] = ft_atod(del[2]);
	ft_free((void **)del);
}

static void	ft_vector(t_cylinder *cylinder, char *tmp)
{
	char **del;

	if (ft_count_coord(tmp) == 0)
		ft_incorrect("cylinder");
	del = ft_strsplit(tmp, ',');
	cylinder->v[0] = ft_atoi(del[0]);
	cylinder->v[1] = ft_atoi(del[1]);
	cylinder->v[2] = ft_atoi(del[2]);
	ft_free((void **)del);
}

static void	ft_specular(t_cylinder *cylinder, char *tmp)
{
	cylinder->specular = ft_atoi(tmp);
	if (cylinder->specular > 500)
		cylinder->specular = 500;
	else if (cylinder->specular < 0)
		cylinder->specular = 0;
}

static int	ft_main_condition(t_cylinder *cylinder, char **tmp, char *arr,
	int k)
{
	arr = ft_strtrim(tmp[0]);
	if (tmp[1])
	{
		if (ft_strcmp(arr, "radius") == 0)
		{
			if ((cylinder->r = ft_atod(tmp[1])) < 0)
				ft_incorrect("cylinder");
		}
		else if (ft_strcmp(arr, "vector") == 0)
			ft_vector(cylinder, tmp[1]);
		else if (ft_strcmp(arr, "center") == 0)
			ft_center(cylinder, tmp[1]);
		else if (ft_strcmp(arr, "color") == 0)
			cylinder->color = ft_atoi_base(tmp[1], 16);
		else if (ft_strcmp(arr, "specular") == 0)
			ft_specular(cylinder, tmp[1]);
		else
			ft_incorrect("cylinder");
		if (arr)
			free(arr);
	}
	else
		ft_incorrect("cylinder");
	ft_free((void **)tmp);
	return (k + 1);
}

t_cylinder	*ft_create_cylinder(int fd, char *line, int iter,
	t_closest *closest)
{
	t_cylinder	*cylinder;
	char		**tmp;

	closest->type[iter] = "cylinder";
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	iter = 0;
	while (iter < 5)
	{
		if (get_next_line(fd, &(line)))
		{
			line = ft_tolowercase(line);
			tmp = ft_strsplit(line, ':');
			free(line);
			if (tmp[0])
				iter = ft_main_condition(cylinder, tmp, NULL, iter);
			else
				ft_wrong("cylinder");
		}
		else
			ft_wrong("cylinder");
	}
	return (cylinder);
}
