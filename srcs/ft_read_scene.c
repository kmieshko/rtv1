/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 16:52:51 by kmieshko          #+#    #+#             */
/*   Updated: 2018/07/25 16:52:52 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_count	*ft_create_count(void)
{
	t_count	*count;

	count = (t_count *)malloc(sizeof(t_count));
	count->cam = 0;
	count->rot = 0;
	count->light = 0;
	return (count);
}

static void		ft_main_condition(t_count *count, int fd, char *line,
	t_closest *closest)
{
	int i;

	i = closest->nb_fig;
	if (ft_strcmp(line, "sphere") == 0)
		closest->figure[i] = ft_create_sphere(fd, line, i, closest);
	else if (ft_strcmp(line, "plane") == 0)
		closest->figure[i] = ft_create_plane(fd, line, i, closest);
	else if (ft_strcmp(line, "cylinder") == 0)
		closest->figure[i] = ft_create_cylinder(fd, line, i, closest);
	else if (ft_strcmp(line, "cone") == 0)
		closest->figure[i] = ft_create_cone(fd, line, i, closest);
	else if (ft_strcmp(line, "light") == 0)
		count->light = ft_count_light(fd, line, i, closest);
	else if (ft_strcmp(line, "camera") == 0)
		count->cam = ft_count_cam(fd, line, i, closest);
	else if (ft_strcmp(line, "rotation") == 0)
		count->rot = ft_count_rot(fd, line, i, closest);
	closest->nb_fig++;
}

void			ft_read_scene(char *str, t_closest *closest)
{
	int		fd;
	char	*line;
	t_count	*count;

	line = NULL;
	count = ft_create_count();
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &(line)))
	{
		ft_null_line(line);
		line = ft_tolowercase(line);
		if (ft_check_type(line) == 1)
		{
			ft_main_condition(count, fd, line, closest);
			free(line);
		}
		else
		{
			free(line);
			ft_wrong("scene");
		}
	}
	ft_check_cam_rot_light_inten_fig(count, closest->light, closest->nb_fig);
	free(count);
}
