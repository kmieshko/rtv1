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

static void	ft_center(t_plane *plane, char *tmp)
{
	char **del;

	if (ft_count_coord(tmp) == 0)
		ft_incorrect("plane");
	del = ft_strsplit(tmp, ',');
	plane->xyz[0] = ft_atod(del[0]);
	plane->xyz[1] = ft_atod(del[1]);
	plane->xyz[2] = ft_atod(del[2]);
	ft_free((void **)del);
}

static void	ft_vector(t_plane *plane, char *tmp)
{
	char **del;

	if (ft_count_coord(tmp) == 0)
		ft_incorrect("plane");
	del = ft_strsplit(tmp, ',');
	plane->v[0] = ft_atoi(del[0]);
	plane->v[1] = ft_atoi(del[1]);
	plane->v[2] = ft_atoi(del[2]);
	plane->v[0] = plane->v[0] / (length(plane->v));
	plane->v[1] = plane->v[1] / (length(plane->v));
	plane->v[2] = plane->v[2] / (length(plane->v));
	ft_free((void **)del);
}

static void	ft_specular(t_plane *plane, char *tmp)
{
	plane->specular = ft_atoi(tmp);
	if (plane->specular > 500)
		plane->specular = 500;
	else if (plane->specular < 0)
		plane->specular = 0;
}

static int	ft_main_condition(t_plane *plane, char **tmp, char *arr, int k)
{
	arr = ft_strtrim(tmp[0]);
	if (tmp[1])
	{
		if (ft_strcmp(arr, "vector") == 0)
			ft_vector(plane, tmp[1]);
		else if (ft_strcmp(arr, "center") == 0)
			ft_center(plane, tmp[1]);
		else if (ft_strcmp(arr, "color") == 0)
			plane->color = ft_atoi_base(tmp[1], 16);
		else if (ft_strcmp(arr, "specular") == 0)
			ft_specular(plane, tmp[1]);
		else
			ft_incorrect("plane");
		if (arr)
			free(arr);
	}
	else
		ft_incorrect("plane");
	ft_free((void **)tmp);
	return (k + 1);
}

t_plane		*ft_create_plane(int fd, char *line, int iter, t_closest *closest)
{
	t_plane	*plane;
	char	**tmp;

	closest->type[iter] = "plane";
	plane = (t_plane *)malloc(sizeof(t_plane));
	iter = 0;
	while (iter < 4)
	{
		if (get_next_line(fd, &(line)))
		{
			line = ft_tolowercase(line);
			tmp = ft_strsplit(line, ':');
			free(line);
			if (tmp[0])
				iter = ft_main_condition(plane, tmp, NULL, iter);
			else
				ft_wrong("plane");
		}
		else
			ft_wrong("plane");
	}
	return (plane);
}
