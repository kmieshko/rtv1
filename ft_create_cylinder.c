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

t_cylinder	*ft_create_cylinder(int fd, char *line)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	int		k;

	k = 0;
	while (k < 5)
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
				cylinder->r = ft_atoi(tmp[1]);
				if (cylinder->r < 0)
					ft_incorrect("cylinder");
			}
			else if (ft_strcmp(arr, "vector") == 0)
			{
				if (ft_count_coord(tmp[1]) == 0)
					ft_incorrect("cylinder");
				char **del;
				del = ft_strsplit(tmp[1], ',');
				cylinder->v[0] = ft_atoi(del[0]);
				cylinder->v[1] = ft_atoi(del[1]);
				cylinder->v[2] = ft_atoi(del[2]);
				ft_free((void **)del);
			}
			else if (ft_strcmp(arr, "center") == 0)
			{
				if (ft_count_coord(tmp[1]) == 0)
					ft_incorrect("cylinder");
				char **del;
				del = ft_strsplit(tmp[1], ',');
				cylinder->xyz[0] = ft_atoi(del[0]);
				cylinder->xyz[1] = ft_atoi(del[1]);
				cylinder->xyz[2] = ft_atoi(del[2]);
				ft_free((void **)del);
			}
			else if (ft_strcmp(arr, "color") == 0)
				cylinder->color = ft_atoi_base(tmp[1], 16);
			else if (ft_strcmp(arr, "specular") == 0)
			{
				cylinder->specular = ft_atoi_base(tmp[1], 10);
				if (cylinder->specular > 500)
					cylinder->specular = 500;
				else if (cylinder->specular < 0)
					cylinder->specular = 0;
			}
			else
				ft_incorrect("cylinder");
			free(line);
			ft_free((void **)tmp);
			free(arr);
			k++;
		}
		else
		{
			ft_putstr("Error: Wrong cylinder!");
			exit(0);
		}
	}
	cylinder->v[0] = cylinder->v[0] / (length(cylinder->v));
	cylinder->v[1] = cylinder->v[1] / (length(cylinder->v));
	cylinder->v[2] = cylinder->v[2] / (length(cylinder->v));
	return (cylinder);
}
