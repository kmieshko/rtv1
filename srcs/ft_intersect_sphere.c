/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:47:03 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:47:04 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	intersect_sphere(double *cam, double *d, t_sphere *s)
{
	double	oc[3];
	double	solve;
	t_koef	koef;

	koef.k1 = 0;
	koef.k2 = 0;
	koef.k3 = 0;
	koef.discrim = 0;
	solve = 0;
	oc[0] = cam[0] - s->xyz[0];
	oc[1] = cam[1] - s->xyz[1];
	oc[2] = cam[2] - s->xyz[2];
	koef.k1 = dot_product(d, d);
	koef.k2 = 2 * dot_product(oc, d);
	koef.k3 = dot_product(oc, oc) - s->r * s->r;
	koef.discrim = koef.k2 * koef.k2 - 4 * koef.k1 * koef.k3;
	if (koef.discrim < 0)
		solve = 100000;
	else
		solve = (-koef.k2 - sqrt(koef.discrim)) / (2 * koef.k1);
	return (solve);
}
