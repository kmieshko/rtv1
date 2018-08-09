/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 14:49:42 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/07 14:49:43 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_camera	*ft_create_camera(int fd, char *line)
{
	int			k;
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	k = 0;
	while (k < 1)
	{
		if (get_next_line(fd, &(line)))
		{
			ft_tolowercase(line);
			char	**tmp;
			char	*arr;
			tmp = ft_strsplit(line, ':');
			if (tmp[0])
				arr = ft_strtrim(tmp[0]);
			if (ft_strcmp(arr, "center") == 0)
			{
				if (ft_count_coord(tmp[1]) == 0)
					ft_incorrect("camera");
				char **del;
				del = ft_strsplit(tmp[1], ',');
				cam->xyz[0] = ft_atod(del[0]);
				cam->xyz[1] = ft_atod(del[1]);
				cam->xyz[2] = ft_atod(del[2]);
				ft_free((void **)del);
			}
			else
				ft_incorrect("camera");
			free(line);
			ft_free((void **)tmp);
			free(arr);
			k++;
		}
		else
		{
			ft_putstr("Error: Wrong camera!");
			exit(0);
		}
	}
	return (cam);
}
