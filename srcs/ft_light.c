/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 13:04:33 by kmieshko          #+#    #+#             */
/*   Updated: 2018/07/17 13:04:34 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	ft_shadow(double *vec_l, t_vect *v, t_light *light,
	int specular)
{
	double	n_dot_l;
	double	res;
	double	vec_r[3];
	double	view[3];
	double	r_dot_v;

	res = 0;
	view[0] = -v->d[0];
	view[1] = -v->d[1];
	view[2] = -v->d[2];
	n_dot_l = dot_product(v->norm, vec_l);
	if (n_dot_l > 0)
		res += light->intensity * n_dot_l / (length(v->norm) * length(vec_l));
	if (specular > 0)
	{
		vec_r[0] = 2 * v->norm[0] * dot_product(v->norm, vec_l) - vec_l[0];
		vec_r[1] = 2 * v->norm[1] * dot_product(v->norm, vec_l) - vec_l[1];
		vec_r[2] = 2 * v->norm[2] * dot_product(v->norm, vec_l) - vec_l[2];
		r_dot_v = dot_product(vec_r, view);
		if (r_dot_v > 0)
			res += light->intensity * pow(r_dot_v /
				(length(vec_r) * length(view)), specular);
	}
	return (res);
}

static double	ft_point_light(t_vect *v, t_light *light, int specular,
	t_closest *mlx)
{
	double	vec_l[3];
	double	inten;

	inten = 0;
	if (ft_strcmp(light->type, "point") == 0)
	{
		vec_l[0] = light->xyz[0] - v->point[0];
		vec_l[1] = light->xyz[1] - v->point[1];
		vec_l[2] = light->xyz[2] - v->point[2];
		mlx->max = 1;
	}
	mlx->min = 0.00001;
	if (!(closest_intersection(v->point, vec_l, mlx)))
		inten += ft_shadow(vec_l, v, light, specular);
	return (inten);
}

double			ft_light(t_vect *v, int specular, t_closest *mlx)
{
	int			i;
	double		inten;
	t_light		**light;

	light = mlx->light;
	inten = 0;
	i = 0;
	while (light[i])
	{
		mlx->max = 100000;
		if (ft_strcmp(light[i]->type, "ambient") == 0)
			inten += light[i]->intensity;
		else
			inten += ft_point_light(v, light[i], specular, mlx);
		if (inten > 1)
			inten = 1;
		else if (inten < 0)
			inten = 0;
		i++;
	}
	return (inten);
}
