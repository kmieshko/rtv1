/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 10:38:59 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/06 10:39:00 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_center(t_sphere *sphere, char *tmp)
{
	char **del;

	if (ft_count_coord(tmp) == 0)
		ft_incorrect("sphere");
	del = ft_strsplit(tmp, ',');
	sphere->xyz[0] = ft_atod(del[0]);
	sphere->xyz[1] = ft_atod(del[1]);
	sphere->xyz[2] = ft_atod(del[2]);
	ft_free((void **)del);
}

static void	ft_specular(t_sphere *sphere, char *tmp)
{
	sphere->specular = ft_atoi(tmp);
	if (sphere->specular > 500)
		sphere->specular = 500;
	else if (sphere->specular < 0)
		sphere->specular = 0;
}

static int	ft_main_condition(t_sphere *sphere, char **tmp, char *arr, int k)
{
	arr = ft_strtrim(tmp[0]);
	if (tmp[1])
	{
		if (ft_strcmp(arr, "radius") == 0)
		{
			sphere->r = ft_atod(tmp[1]);
			if (sphere->r < 0)
				ft_incorrect("sphere");
		}
		else if (ft_strcmp(arr, "center") == 0)
			ft_center(sphere, tmp[1]);
		else if (ft_strcmp(arr, "color") == 0)
			sphere->color = ft_atoi_base(tmp[1], 16);
		else if (ft_strcmp(arr, "specular") == 0)
			ft_specular(sphere, tmp[1]);
		else
			ft_incorrect("sphere");
		if (arr)
			free(arr);
	}
	else
		ft_incorrect("sphere");
	ft_free((void **)tmp);
	return (k + 1);
}

t_sphere	*ft_create_sphere(int fd, char *line, int iter, t_closest *closest)
{
	t_sphere	*sphere;
	char		**tmp;

	closest->type[iter] = "sphere";
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	iter = 0;
	while (iter < 4)
	{
		if (get_next_line(fd, &(line)))
		{
			line = ft_tolowercase(line);
			tmp = ft_strsplit(line, ':');
			free(line);
			if (tmp[0])
				iter = ft_main_condition(sphere, tmp, NULL, iter);
			else
				ft_wrong("sphere");
		}
		else
			ft_wrong("sphere");
	}
	return (sphere);
}
