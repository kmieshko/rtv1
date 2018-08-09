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

t_cone	*ft_create_cone(int fd, char *line)
{
	t_cone	*cone;

	cone = (t_cone *)malloc(sizeof(t_cone));
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
			if (ft_strcmp(arr, "tangle") == 0)
			{
				cone->k = tan(RAD * ft_atoi(tmp[1]));
				if (ft_atoi(tmp[1]) < 0 && ft_atoi(tmp[1]) > 90)
					ft_incorrect("cone");
			}
			else if (ft_strcmp(arr, "vector") == 0)
			{
				if (ft_count_coord(tmp[1]) == 0)
					ft_incorrect("cone");
				char **del;
				del = ft_strsplit(tmp[1], ',');
				cone->v[0] = ft_atoi(del[0]);
				cone->v[1] = ft_atoi(del[1]);
				cone->v[2] = ft_atoi(del[2]);
				ft_free((void **)del);
			}
			else if (ft_strcmp(arr, "center") == 0)
			{
				if (ft_count_coord(tmp[1]) == 0)
					ft_incorrect("cone");
				char **del;
				del = ft_strsplit(tmp[1], ',');
				cone->xyz[0] = ft_atoi(del[0]);
				cone->xyz[1] = ft_atoi(del[1]);
				cone->xyz[2] = ft_atoi(del[2]);
				ft_free((void **)del);
			}
			else if (ft_strcmp(arr, "color") == 0)
				cone->color = ft_atoi_base(tmp[1], 16);
			else if (ft_strcmp(arr, "specular") == 0)
			{
				cone->specular = ft_atoi_base(tmp[1], 10);
				if (cone->specular > 500)
					cone->specular = 500;
				else if (cone->specular < 0)
					cone->specular = 0;
			}
			else
				ft_incorrect("cone");
			free(line);
			ft_free((void **)tmp);
			free(arr);
			k++;
		}
		else
		{
			ft_putstr("Error: Wrong cone!");
			exit(0);
		}
	}
	cone->v[0] = cone->v[0] / (length(cone->v));
	cone->v[1] = cone->v[1] / (length(cone->v));
	cone->v[2] = cone->v[2] / (length(cone->v));
	return (cone);
}
