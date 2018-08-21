/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 15:44:46 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/14 15:44:47 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_mlx	*ft_create_mlx(void)
{
	t_mlx	*mlx;
	int		k;

	k = 0;
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->img = NULL;
	mlx->size_line = 0;
	mlx->bpp = 0;
	mlx->endian = 0;
	mlx->addr = NULL;
	mlx->width = 600;
	mlx->height = 600;
	mlx->vh = 1;
	mlx->vw = 1;
	mlx->closest = (t_closest *)malloc(sizeof(t_closest));
	mlx->closest->c = (t_color *)malloc(sizeof(t_color));
	mlx->closest->figure = (void**)malloc(sizeof(mlx->closest->figure) * 1024);
	mlx->closest->type = (char **)malloc(sizeof(char *) * 1024);
	mlx->closest->nb_fig = 0;
	mlx->closest->light = (t_light **)malloc(sizeof(t_light *) * 11);
	while (k < 11)
		mlx->closest->light[k++] = NULL;
	return (mlx);
}
