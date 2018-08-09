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

void	ft_pixel_put(t_mlx *mlx, int x, int y, int color)
{

	int r;
	int	g;
	int	b;

	r = (color & 0xff);
	g = ((color >> 8) & 0xff);
	b = ((color >> 16) & 0xff);

	mlx->addr[y * mlx->size_line + 4 * x] = r;
	mlx->addr[y * mlx->size_line + 4 * x + 1] = g;
	mlx->addr[y * mlx->size_line + 4 * x + 2] = b;
}
