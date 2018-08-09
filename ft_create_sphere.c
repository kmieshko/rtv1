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

t_sphere	*ft_create_sphere(int fd, char *line)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	int		k;

	k = 0;
	while (k < 4)
	{
		if (get_next_line(fd, &(line)))
		{
			ft_tolowercase(line);
			char	**tmp;
			char	*arr;
			tmp = ft_strsplit(line, ':');
			if (tmp[0])
				arr = ft_strtrim(tmp[0]);
			if (ft_strcmp(arr, "radius") == 0)
			{
				sphere->r = ft_atoi(tmp[1]);
				if (sphere->r < 0)
					ft_incorrect("sphere");
			}
			else if (ft_strcmp(arr, "center") == 0)
			{
				if (ft_count_coord(tmp[1]) == 0)
					ft_incorrect("sphere");
				char **del;
				del = ft_strsplit(tmp[1], ',');
				sphere->xyz[0] = ft_atoi(del[0]);
				sphere->xyz[1] = ft_atoi(del[1]);
				sphere->xyz[2] = ft_atoi(del[2]);
				ft_free((void **)del);
			}
			else if (ft_strcmp(arr, "color") == 0)
				sphere->color = ft_atoi_base(tmp[1], 16);
			else if (ft_strcmp(arr, "specular") == 0)
			{
				sphere->specular = ft_atoi_base(tmp[1], 10);
				if (sphere->specular > 500)
					sphere->specular = 500;
				else if (sphere->specular < 0)
					sphere->specular = 0;
			}
			else
				ft_incorrect("sphere");
			free(line);
			ft_free((void **)tmp);
			free(arr);
			k++;
		}
		else
		{
			ft_putstr("Error: Wrong sphere!");
			exit(0);
		}
	}
	return (sphere);
}
