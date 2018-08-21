/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_closest_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:37:33 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:37:34 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	sphere(t_closest *closest, int i, double *cam, double *d)
{
	double		solve;

	solve = intersect_sphere(cam, d, (t_sphere *)closest->figure[i]);
	if (solve < closest->t && solve > closest->min && solve < closest->max)
	{
		closest->t = solve;
		closest->id = i;
	}
}

static void	plane(t_closest *closest, int i, double *cam, double *d)
{
	double		solve;

	solve = intersect_plane(cam, d, (t_plane *)closest->figure[i]);
	if (solve < closest->t && solve > closest->min && solve < closest->max)
	{
		closest->t = solve;
		closest->id = i;
	}
}

static void	cylinder(t_closest *closest, int i, double *cam, double *d)
{
	double		solve;

	solve = intersect_cylinder(cam, d, (t_cylinder *)closest->figure[i]);
	if (solve < closest->t && solve > closest->min && solve < closest->max)
	{
		closest->t = solve;
		closest->id = i;
	}
}

static void	cone(t_closest *closest, int i, double *cam, double *d)
{
	double		solve;

	solve = intersect_cone(cam, d, (t_cone *)closest->figure[i]);
	if (solve < closest->t && solve > closest->min && solve < closest->max)
	{
		closest->t = solve;
		closest->id = i;
	}
}

t_closest	*closest_intersection(double *cam, double *d, t_closest *mlx)
{
	t_closest	*closest;
	int			i;

	closest = mlx;
	closest->t = mlx->max;
	i = 0;
	while (i < closest->nb_fig)
	{
		if (ft_strcmp(closest->type[i], "sphere") == 0)
			sphere(closest, i, cam, d);
		else if (ft_strcmp(closest->type[i], "plane") == 0)
			plane(closest, i, cam, d);
		else if (ft_strcmp(closest->type[i], "cylinder") == 0)
			cylinder(closest, i, cam, d);
		else if (ft_strcmp(closest->type[i], "cone") == 0)
			cone(closest, i, cam, d);
		i++;
	}
	if (closest->t == mlx->max)
		return (NULL);
	return (closest);
}
