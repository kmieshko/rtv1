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

static t_light	*ft_create_light(char *type, double intensity, double pos[])
{
	t_light *l;
	int		i;

	i = 0;
	l = (t_light *)malloc(sizeof(t_light));
	l->type = type;
	l->intensity = intensity;
	while (i < 3)
	{
		l->xyz[i] = pos[i];
		i++;
	}
	return (l);
}

double	ft_light(double *point, double *normal, t_direction *d, int specular)
{
	t_light		*light[3];
	double		pos[3][3] = {
		{0, 0, 0},
		{2, 1, 0},
		{1, 4, 4}
	};

	light[0] = ft_create_light("ambient", 0.2, pos[0]);
	light[1] = ft_create_light("point", 0.5, pos[1]);
	light[2] = ft_create_light("directional", 0.3, pos[2]);

	int i = 0;
	double inten = 0;
	while (i < 3)
	{
		if (ft_strcmp(light[i]->type, "ambient") == 0)
		{
			inten += light[i]->intensity;
		}
		else
		{
			double vec_l[3] = {0, 0, 0};
			if (ft_strcmp(light[i]->type, "point") == 0)
			{
				vec_l[0] = light[i]->xyz[0] - point[0];
				vec_l[1] = light[i]->xyz[1] - point[1];
				vec_l[2] = light[i]->xyz[2] - point[2];
			}
			else
			{
				vec_l[0] = light[i]->xyz[0];
				vec_l[1] = light[i]->xyz[1];
				vec_l[2] = light[i]->xyz[2];
			}

			double n_dot_l = dot_product(normal, vec_l, 3);
			if(n_dot_l > 0)
			{
				inten += light[i]->intensity * n_dot_l / (length(normal) * length(vec_l));
			}

				double	view[3];

				view[0] = -d->xyz[0];
				view[1] = -d->xyz[1];
				view[2] = -d->xyz[2];

			double	vec_r[3];
			if (specular != -1)
			{
				vec_r[0] = 2 * normal[0] * dot_product(normal, vec_l, 3) - vec_l[0];
				vec_r[1] = 2 * normal[1] * dot_product(normal, vec_l, 3) - vec_l[1];
				vec_r[2] = 2 * normal[2] * dot_product(normal, vec_l, 3) - vec_l[2];
				double r_dot_v = dot_product(vec_r, view, 3);
				if (r_dot_v > 0)
				{
					inten += light[i]->intensity * pow(r_dot_v / (length(vec_r) * length(view)), specular);
				}
			}
		}
		i++;
	}
	// printf("%f\n", inten);
	return (inten);
}
