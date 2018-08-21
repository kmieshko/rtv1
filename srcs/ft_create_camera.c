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

static void	ft_center(t_camera *cam, char *tmp)
{
	char **del;

	if (ft_count_coord(tmp) == 0)
		ft_incorrect("camera");
	del = ft_strsplit(tmp, ',');
	cam->xyz[0] = ft_atod(del[0]);
	cam->xyz[1] = ft_atod(del[1]);
	cam->xyz[2] = ft_atod(del[2]);
	ft_free((void **)del);
}

static void	ft_main_condition(t_camera *cam, char **tmp, char *arr)
{
	if (tmp[0])
		arr = ft_strtrim(tmp[0]);
	if (tmp[1])
	{
		if (ft_strcmp(arr, "center") == 0)
			ft_center(cam, tmp[1]);
		else
			ft_incorrect("camera");
		if (arr)
			free(arr);
	}
	else
		ft_incorrect("camera");
}

t_camera	*ft_create_camera(int fd, char *line, int iter, t_closest *closest)
{
	t_camera	*cam;
	char		**tmp;

	tmp = NULL;
	cam = (t_camera *)malloc(sizeof(t_camera));
	if (get_next_line(fd, &(line)))
	{
		line = ft_tolowercase(line);
		tmp = ft_strsplit(line, ':');
		free(line);
		if (tmp[0])
		{
			ft_main_condition(cam, tmp, NULL);
			ft_free((void **)tmp);
		}
		else
			ft_wrong("camera");
	}
	else
		ft_wrong("camera");
	closest->type[iter] = "camera";
	return (cam);
}
