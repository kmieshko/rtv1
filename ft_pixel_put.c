/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 10:32:22 by kmieshko          #+#    #+#             */
/*   Updated: 2018/07/17 10:32:25 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		if_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double		if_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double		clamp(double color)
{
	double res;

	res = if_min(255, if_max(0, color));
	return (res);
}

void	ft_pixel_put(t_mlx *mlx, int x, int y, int color)
{

	int r;
	int	g;
	int	b;
	// mlx->inten = 1;

	int fig[3];
	int res[3];
	double light;

	r = (color & 0xff);
	g = ((color >> 8) & 0xff);
	b = ((color >> 16) & 0xff);

	if (mlx->inten > 1)
		mlx->inten = 1;
	else if (mlx->inten < 0)
		mlx->inten = 0;

	light = mlx->inten;

	// if (light > 0)
	// 	printf("%#x\n", light);

int rr = r * light;
int gg = g * light;
int bb = b * light;

	if (rr > 255)
		rr = 255;
	else if (gg > 255)
		gg = 255;
	else if (bb > 255)
		bb = 255;

	if (rr < 0)
		rr = 0;
	else if (gg < 0)
		gg = 0;
	else if (bb < 0)
		bb = 0;

	mlx->addr[y * mlx->size_line + 4 * x] = rr;
	mlx->addr[y * mlx->size_line + 4 * x + 1] = gg;
	mlx->addr[y * mlx->size_line + 4 * x + 2] = bb;

	// printf("%f | %f | %f\n", (color & 0xff) * mlx->inten, ((color >> 8) & 0xff) * mlx->inten, ((color >> 16) & 0xff) * mlx->inten);
}
