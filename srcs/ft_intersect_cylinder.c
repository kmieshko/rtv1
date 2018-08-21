/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:46:33 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:46:34 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	intersect_cylinder(double *cam, double *d, t_cylinder *c)
{
	t_koef	koef;
	double	oc[3];
	double	solve;

	koef.k1 = 0;
	koef.k2 = 0;
	koef.k3 = 0;
	koef.discrim = 0;
	solve = 0;
	oc[0] = cam[0] - c->xyz[0];
	oc[1] = cam[1] - c->xyz[1];
	oc[2] = cam[2] - c->xyz[2];
	koef.k1 = dot_product(d, d) - dot_product(d, c->v) * dot_product(d, c->v);
	koef.k2 = 2 * (dot_product(oc, d) - dot_product(d, c->v) *
			dot_product(oc, c->v));
	koef.k3 = dot_product(oc, oc) - dot_product(oc, c->v) *
			dot_product(oc, c->v) - c->r * c->r;
	koef.discrim = koef.k2 * koef.k2 - 4 * koef.k1 * koef.k3;
	if (koef.discrim < 0)
		solve = 100000;
	else
		solve = (-koef.k2 - sqrt(koef.discrim)) / (2 * koef.k1);
	return (solve);
}
