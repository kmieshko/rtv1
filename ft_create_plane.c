/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 10:49:46 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/06 10:49:48 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_plane	*ft_create_plane(int fd, char *line)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
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
			if (ft_strcmp(arr, "vector") == 0)
			{
				if (ft_count_coord(tmp[1]) == 0)
					ft_incorrect("plane");
				char **del;
				del = ft_strsplit(tmp[1], ',');
				plane->v[0] = ft_atoi(del[0]);
				plane->v[1] = ft_atoi(del[1]);
				plane->v[2] = ft_atoi(del[2]);
				ft_free((void **)del);
			}
			else if (ft_strcmp(arr, "center") == 0)
			{
				if (ft_count_coord(tmp[1]) == 0)
					ft_incorrect("plane");
				char **del;
				del = ft_strsplit(tmp[1], ',');
				plane->xyz[0] = ft_atoi(del[0]);
				plane->xyz[1] = ft_atoi(del[1]);
				plane->xyz[2] = ft_atoi(del[2]);
				ft_free((void **)del);
			}
			else if (ft_strcmp(arr, "color") == 0)
				plane->color = ft_atoi_base(tmp[1], 16);
			else if (ft_strcmp(arr, "specular") == 0)
			{
				plane->specular = ft_atoi_base(tmp[1], 10);
				if (plane->specular > 500)
					plane->specular = 500;
				else if (plane->specular < 0)
					plane->specular = 0;
			}
			else
				ft_incorrect("plane");
			free(line);
			ft_free((void **)tmp);
			free(arr);
			k++;
		}
		else
		{
			ft_putstr("Error: Wrong plane!");
			exit(0);
		}
	}
	plane->v[0] = plane->v[0] / (length(plane->v));
	plane->v[1] = plane->v[1] / (length(plane->v));
	plane->v[2] = plane->v[2] / (length(plane->v));
	return (plane);
}
