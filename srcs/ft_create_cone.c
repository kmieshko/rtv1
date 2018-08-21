/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 11:34:00 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/06 11:34:02 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_center(t_cone *cone, char *tmp)
{
	char **del;

	if (ft_count_coord(tmp) == 0)
		ft_incorrect("cone");
	del = ft_strsplit(tmp, ',');
	cone->xyz[0] = ft_atod(del[0]);
	cone->xyz[1] = ft_atod(del[1]);
	cone->xyz[2] = ft_atod(del[2]);
	ft_free((void **)del);
}

static void	ft_vector(t_cone *cone, char *tmp)
{
	char **del;

	if (ft_count_coord(tmp) == 0)
		ft_incorrect("cone");
	del = ft_strsplit(tmp, ',');
	cone->v[0] = ft_atoi(del[0]);
	cone->v[1] = ft_atoi(del[1]);
	cone->v[2] = ft_atoi(del[2]);
	ft_free((void **)del);
}

static void	ft_specular(t_cone *cone, char *tmp)
{
	cone->specular = ft_atoi(tmp);
	if (cone->specular > 500)
		cone->specular = 500;
	else if (cone->specular < 0)
		cone->specular = 0;
}

static int	ft_main_condition(t_cone *cone, char **tmp, char *arr, int k)
{
	arr = ft_strtrim(tmp[0]);
	if (tmp[1])
	{
		if (ft_strcmp(arr, "tangle") == 0)
			if (ft_atoi(tmp[1]) > 0 && ft_atoi(tmp[1]) < 90)
				cone->k = tan(RAD * ft_atoi(tmp[1]));
			else
				ft_incorrect("cone");
		else if (ft_strcmp(arr, "vector") == 0)
			ft_vector(cone, tmp[1]);
		else if (ft_strcmp(arr, "center") == 0)
			ft_center(cone, tmp[1]);
		else if (ft_strcmp(arr, "color") == 0)
			cone->color = ft_atoi_base(tmp[1], 16);
		else if (ft_strcmp(arr, "specular") == 0)
			ft_specular(cone, tmp[1]);
		else
			ft_incorrect("cone");
		if (arr)
			free(arr);
	}
	else
		ft_incorrect("cone");
	ft_free((void **)tmp);
	return (k + 1);
}

t_cone		*ft_create_cone(int fd, char *line, int iter, t_closest *closest)
{
	t_cone	*cone;
	char	**tmp;

	closest->type[iter] = "cone";
	cone = (t_cone *)malloc(sizeof(t_cone));
	iter = 0;
	while (iter < 5)
	{
		if (get_next_line(fd, &(line)))
		{
			line = ft_tolowercase(line);
			tmp = ft_strsplit(line, ':');
			free(line);
			if (tmp[0])
				iter = ft_main_condition(cone, tmp, NULL, iter);
			else
				ft_wrong("cone");
		}
		else
			ft_wrong("cone");
	}
	return (cone);
}
