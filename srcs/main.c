/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 12:20:57 by kmieshko          #+#    #+#             */
/*   Updated: 2018/07/16 12:20:58 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_fill_camera_rotation(t_mlx *mlx)
{
	int		a;
	int		b;
	int		c;

	a = mlx->closest->rot->angle[0];
	b = mlx->closest->rot->angle[1];
	c = mlx->closest->rot->angle[2];
	mlx->camera_rotation[0][0] = C00(b, c);
	mlx->camera_rotation[0][1] = C01(b, c);
	mlx->camera_rotation[0][2] = C02(b);
	mlx->camera_rotation[1][0] = C10(a, b, c);
	mlx->camera_rotation[1][1] = C11(a, b, c);
	mlx->camera_rotation[1][2] = C12(a, b);
	mlx->camera_rotation[2][0] = C20(a, b, c);
	mlx->camera_rotation[2][1] = C21(a, b, c);
	mlx->camera_rotation[2][2] = C22(a, b);
}

static void	ft_get_direction(t_mlx *mlx)
{
	int		i;
	int		j;
	double	res[3];

	i = 0;
	res[0] = 0;
	res[1] = 0;
	res[2] = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res[i] += mlx->direction[j] * mlx->camera_rotation[i][j];
			j++;
		}
		i++;
	}
	mlx->direction[0] = res[0];
	mlx->direction[1] = res[1];
	mlx->direction[2] = res[2];
}

static void	ft_main_loop(t_mlx *mlx)
{
	int		x;
	int		y;
	int		color;

	color = 0xffffff;
	y = -mlx->height / 2;
	while (y < mlx->height / 2)
	{
		x = -mlx->width / 2;
		while (x < mlx->width / 2)
		{
			mlx->direction[0] = x * mlx->vw * 0.5 / mlx->width;
			mlx->direction[1] = y * mlx->vh * 0.5 / mlx->height;
			mlx->direction[2] = 1;
			mlx->closest->max = 100000;
			mlx->closest->min = 1;
			ft_get_direction(mlx);
			color = trace_ray(mlx->closest->cam->xyz, mlx->direction,
				mlx->closest, -1);
			ft_pixel_put(mlx, x + mlx->width / 2, mlx->height / 2 - y - 1,
				color);
			x++;
		}
		y++;
	}
}

int			main(int argc, char **argv)
{
	t_mlx		*mlx;

	if (argc != 2)
	{
		ft_putstr("Error: use one scene file as argument!\n");
		return (0);
	}
	mlx = ft_create_mlx();
	ft_read_scene(argv[1], mlx->closest);
	ft_fill_camera_rotation(mlx);
	if (!(mlx->mlx = mlx_init()))
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, argv[1]);
	mlx->img = mlx_new_image(mlx->win, mlx->width, mlx->height);
	mlx->addr = mlx_get_data_addr(mlx->img, &(mlx->bpp), &(mlx->size_line),
		&(mlx->endian));
	ft_main_loop(mlx);
	mlx_hook(mlx->win, 2, 5, ft_manage, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_hook(mlx->win, 17, 1L << 17, ft_exit_mouse, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
