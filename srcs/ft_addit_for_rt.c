/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addit_for_rt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:42:01 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/14 16:42:02 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect	*ft_create_vect(double *cam, double *d, double solve)
{
	t_vect *v;

	v = (t_vect *)malloc(sizeof(t_vect));
	v->point[0] = cam[0] + (solve * d[0]);
	v->point[1] = cam[1] + (solve * d[1]);
	v->point[2] = cam[2] + (solve * d[2]);
	v->d[0] = d[0];
	v->d[1] = d[1];
	v->d[2] = d[2];
	v->norm[0] = 0;
	v->norm[1] = 0;
	v->norm[2] = 0;
	return (v);
}

int		ft_check_fig(t_closest *closest, int i, int id, char *str)
{
	if (ft_strcmp(closest->type[i], str) == 0 &&
		ft_strcmp(closest->type[id], str) == 0)
		return (1);
	return (0);
}
