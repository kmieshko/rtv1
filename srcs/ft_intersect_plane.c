/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:47:12 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:47:13 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	intersect_plane(double *cam, double *d, t_plane *p)
{
	double	oc[3];
	double	solve;
	t_koef	koef;

	koef.k1 = 0;
	koef.k2 = 0;
	koef.k3 = 0;
	koef.discrim = 0;
	solve = 0;
	oc[0] = cam[0] - p->xyz[0];
	oc[1] = cam[1] - p->xyz[1];
	oc[2] = cam[2] - p->xyz[2];
	koef.k1 = (dot_product(oc, p->v));
	koef.k2 = (dot_product(d, p->v));
	if (koef.k2 != 0)
		solve = -koef.k1 / koef.k2;
	else
		solve = 100000;
	return (solve);
}
