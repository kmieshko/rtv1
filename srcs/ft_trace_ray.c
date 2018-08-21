/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:51:20 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:51:21 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	sphere(t_vect *v, t_closest *closest, t_sphere *s)
{
	t_color *c;

	c = closest->c;
	v->norm[0] = v->point[0] - s->xyz[0];
	v->norm[1] = v->point[1] - s->xyz[1];
	v->norm[2] = v->point[2] - s->xyz[2];
	v->norm[0] = (v->norm[0] / length(v->norm));
	v->norm[1] = (v->norm[1] / length(v->norm));
	v->norm[2] = (v->norm[2] / length(v->norm));
	c->r = (s->color & 0xff0000) >> 16;
	c->g = (s->color & 0x00ff00) >> 8;
	c->b = (s->color & 0x0000ff);
	c->inten = ft_light(v, s->specular, closest);
}

static void	plane(t_vect *v, t_closest *closest, t_plane *p)
{
	t_color *c;

	c = closest->c;
	p->v[0] /= length(p->v);
	p->v[1] /= length(p->v);
	p->v[2] /= length(p->v);
	v->norm[0] = p->v[0];
	v->norm[1] = p->v[1];
	v->norm[2] = p->v[2];
	v->norm[0] = (v->norm[0] / length(v->norm));
	v->norm[1] = (v->norm[1] / length(v->norm));
	v->norm[2] = (v->norm[2] / length(v->norm));
	if (dot_product(v->d, p->v) > 0)
	{
		v->norm[0] = -v->norm[0];
		v->norm[1] = -v->norm[1];
		v->norm[2] = -v->norm[2];
	}
	c->r = (p->color & 0xff0000) >> 16;
	c->g = (p->color & 0x00ff00) >> 8;
	c->b = (p->color & 0x0000ff);
	c->inten = ft_light(v, p->specular, closest);
}

static void	cylinder(t_vect *vec, t_closest *closest, t_cylinder *cy,
	double *cam)
{
	t_color	*c;
	double	oc[3];
	double	m;

	c = closest->c;
	oc[0] = cam[0] - cy->xyz[0];
	oc[1] = cam[1] - cy->xyz[1];
	oc[2] = cam[2] - cy->xyz[2];
	cy->v[0] /= length(cy->v);
	cy->v[1] /= length(cy->v);
	cy->v[2] /= length(cy->v);
	m = dot_product(vec->d, cy->v) * closest->t + dot_product(oc, cy->v);
	vec->norm[0] = vec->point[0] - cy->xyz[0] - cy->v[0] * m;
	vec->norm[1] = vec->point[1] - cy->xyz[1] - cy->v[1] * m;
	vec->norm[2] = vec->point[2] - cy->xyz[2] - cy->v[2] * m;
	vec->norm[0] = (vec->norm[0] / length(vec->norm));
	vec->norm[1] = (vec->norm[1] / length(vec->norm));
	vec->norm[2] = (vec->norm[2] / length(vec->norm));
	c->r = (cy->color & 0xff0000) >> 16;
	c->g = (cy->color & 0x00ff00) >> 8;
	c->b = (cy->color & 0x0000ff);
	c->inten = ft_light(vec, cy->specular, closest);
}

static void	cone(t_vect *v, t_closest *closest, t_cone *co, double *cam)
{
	t_color	*c;
	double	oc[3];
	double	m;

	c = closest->c;
	oc[0] = cam[0] - co->xyz[0];
	oc[1] = cam[1] - co->xyz[1];
	oc[2] = cam[2] - co->xyz[2];
	co->v[0] /= length(co->v);
	co->v[1] /= length(co->v);
	co->v[2] /= length(co->v);
	m = dot_product(v->d, co->v) * closest->t + dot_product(oc, co->v);
	v->norm[0] = v->point[0] - co->xyz[0] - (1 + co->k * co->k) * co->v[0] * m;
	v->norm[1] = v->point[1] - co->xyz[1] - (1 + co->k * co->k) * co->v[1] * m;
	v->norm[2] = v->point[2] - co->xyz[2] - (1 + co->k * co->k) * co->v[2] * m;
	v->norm[0] = (v->norm[0] / length(v->norm));
	v->norm[1] = (v->norm[1] / length(v->norm));
	v->norm[2] = (v->norm[2] / length(v->norm));
	c->r = (co->color & 0xff0000) >> 16;
	c->g = (co->color & 0x00ff00) >> 8;
	c->b = (co->color & 0x0000ff);
	closest->c->inten = ft_light(v, co->specular, closest);
}

int			trace_ray(double *cam, double *d, t_closest *mlx, int i)
{
	t_vect		*v;
	t_closest	*closest;
	t_color		color;
	int			id;

	if (!(closest = closest_intersection(cam, d, mlx)))
		return (0x0);
	v = ft_create_vect(cam, d, closest->t);
	id = closest->id;
	while (++i < closest->nb_fig)
	{
		if (ft_check_fig(closest, i, id, "sphere"))
			sphere(v, closest, (t_sphere *)closest->figure[id]);
		else if (ft_check_fig(closest, i, id, "plane"))
			plane(v, closest, (t_plane *)closest->figure[id]);
		else if (ft_check_fig(closest, i, id, "cylinder"))
			cylinder(v, closest, (t_cylinder *)closest->figure[id], cam);
		else if (ft_check_fig(closest, i, id, "cone"))
			cone(v, closest, (t_cone *)closest->figure[id], cam);
	}
	color.r = clamp(closest->c->r * closest->c->inten) << 16;
	color.g = clamp(closest->c->g * closest->c->inten) << 8;
	color.b = clamp(closest->c->b * closest->c->inten);
	free(v);
	return (color.r + color.g + color.b);
}
