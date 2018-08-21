/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 11:19:03 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/15 11:19:05 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_count_light(int fd, char *line, int i, t_closest *closest)
{
	static int light = 0;

	if (light < 10)
	{
		closest->figure[i] = ft_create_light(fd, line, i, closest);
		closest->light[light] = closest->figure[i];
		light++;
	}
	else
		ft_wrong("number of light");
	return (light);
}

int			ft_count_cam(int fd, char *line, int i, t_closest *closest)
{
	static int cam = 0;

	closest->figure[i] = ft_create_camera(fd, line, i, closest);
	closest->cam = closest->figure[i];
	cam++;
	return (cam);
}

int			ft_count_rot(int fd, char *line, int i, t_closest *closest)
{
	static int rot = 0;

	closest->figure[i] = ft_create_rotation(fd, line, i, closest);
	closest->rot = closest->figure[i];
	rot++;
	return (rot);
}

void		ft_check_cam_rot_light_inten_fig(t_count *count, t_light **light,
	int nb_fig)
{
	int		i;
	double	inten;

	i = 0;
	inten = 0;
	if (count->cam != 1)
		ft_wrong("number of camera");
	else if (!count->light)
		ft_wrong("number of light");
	else if (count->rot != 1)
		ft_wrong("number of rotation");
	else if ((count->rot + count->cam + count->light) == nb_fig)
		ft_wrong("number of figures in the scene");
	while (light[i])
	{
		if (light[i]->intensity > 0)
		{
			inten += light[i]->intensity;
			if (inten > 1)
				ft_wrong("intensity");
		}
		i++;
	}
}
