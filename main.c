/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 12:20:57 by kmieshko          #+#    #+#             */
/*   Updated: 2018/07/16 12:20:58 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		dot_product(double *a, double *b)
{
	double		sum;
	size_t	i;

	i = 0;
	sum = 0;
	while (i < 3)
	{
		sum += a[i] * b[i];
		i++;
	}
	return (sum);
}

double		length(double *vector)
{
	double	length;

	length = sqrt(dot_product(vector, vector));
	return (length);
}

t_mlx	*ft_create_mlx(void)
{
	t_mlx *mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->img = NULL;
	mlx->size_line = 0;
	mlx->bpp = 0;
	mlx->endian = 0;
	mlx->addr = NULL;
	mlx->width = 600;
	mlx->height = 600;
	mlx->color = 0xffffff;
	return (mlx);
}

t_sphere	*ft_sphere_create(void)
{
	t_sphere *sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->xyz[0] = 0;
	sphere->xyz[1] = -1;
	sphere->xyz[2] = 2.5;
	sphere->r = 1;
	sphere->color = 0xff0000;
	sphere->specular = 100;
	return (sphere);
}

t_sphere	*ft_sphere_create1(void)
{
	t_sphere *sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->xyz[0] = 2;
	sphere->xyz[1] = 0;
	sphere->xyz[2] = 4;
	sphere->r = 1;
	sphere->color = 0x00ff00;
	sphere->specular = 100;
	return (sphere);
}

t_sphere	*ft_sphere_create2(void)
{
	t_sphere *sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->xyz[0] = -1;
	sphere->xyz[1] = 1;
	sphere->xyz[2] = 3;
	sphere->r = 1;
	sphere->color = 0x0000ff;
	sphere->specular = 100;
	return (sphere);
}

t_plane	*ft_plane_create(void)
{
	t_plane *plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->xyz[0] = 0;
	plane->xyz[1] = 0;
	plane->xyz[2] = 7;
	plane->v[0] = 0;
	plane->v[1] = 0;
	plane->v[2] = -1;
	plane->color = 0xffffff;
	plane->specular = 1;
	plane->v[0] = plane->v[0] / (length(plane->v));
	plane->v[1] = plane->v[1] / (length(plane->v));
	plane->v[2] = plane->v[2] / (length(plane->v));
	return (plane);
}

t_plane	*ft_plane_create1(void)
{
	t_plane *plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->xyz[0] = 0;
	plane->xyz[1] = -1;
	plane->xyz[2] = 0;
	plane->v[0] = 0;
	plane->v[1] = 1;
	plane->v[2] = 0;
	plane->color = 0xffff00;
	plane->specular = 1;
	plane->v[0] = plane->v[0] / (length(plane->v));
	plane->v[1] = plane->v[1] / (length(plane->v));
	plane->v[2] = plane->v[2] / (length(plane->v));
	return (plane);
}

t_cylinder	*ft_cylinder_create(void)
{
	t_cylinder *cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->xyz[0] = 0;
	cylinder->xyz[1] = 0;
	cylinder->xyz[2] = 4;
	cylinder->v[0] = 0;
	cylinder->v[1] = -1;
	cylinder->v[2] = 0;
	cylinder->r = 1;
	cylinder->color = 0x00ffff;
	cylinder->specular = 100;
	cylinder->v[0] = cylinder->v[0] / (length(cylinder->v));
	cylinder->v[1] = cylinder->v[1] / (length(cylinder->v));
	cylinder->v[2] = cylinder->v[2] / (length(cylinder->v));
	return (cylinder);
}

t_cone	*ft_cone_create(void)
{
	t_cone *cone;

	cone = (t_cone *)malloc(sizeof(t_cone));
	cone->xyz[0] = 0;
	cone->xyz[1] = 2;
	cone->xyz[2] = 3;
	cone->v[0] = 1;
	cone->v[1] = 1;
	cone->v[2] = 0;
	cone->k = tan(RAD * 2);
	cone->color = 0xff00ff;
	cone->specular = 100;
	cone->v[0] = cone->v[0] / (length(cone->v));
	cone->v[1] = cone->v[1] / (length(cone->v));
	cone->v[2] = cone->v[2] / (length(cone->v));
	return (cone);
}

t_solve	*intersect_cylinder(double *cam, double *d, t_cylinder *c)
{
	double	oc[3];
	t_solve *solve;
	double	k1 = 0;
	double	k2 = 0;
	double	k3 = 0;
	double	discrim = 0;

	solve = (t_solve *)malloc(sizeof(t_solve));
	oc[0] = cam[0] - c->xyz[0];
	oc[1] = cam[1] - c->xyz[1];
	oc[2] = cam[2] - c->xyz[2];
	k1 = dot_product(d, d) - dot_product(d, c->v) * dot_product(d, c->v);
	k2 = 2 * (dot_product(oc, d) - dot_product(d, c->v) * dot_product(oc, c->v));
	k3 = dot_product(oc, oc) - dot_product(oc, c->v) * dot_product(oc, c->v) - c->r * c->r;
	discrim = k2 * k2 - 4 * k1 * k3;
	if (discrim < 0)
	{
		solve->s1 = 1000000;
		solve->s2 = 1000000;
	}
	else
	{
		solve->s1 = (-k2 + sqrt(discrim)) / (2 * k1);
		solve->s2 = (-k2 - sqrt(discrim)) / (2 * k1);
	}
	return (solve);
}

t_solve	*intersect_cone(double *cam, double *d, t_cone *c)
{
	double	oc[3];
	t_solve *solve;
	double	k1 = 0;
	double	k2 = 0;
	double	k3 = 0;
	double	discrim = 0;

	solve = (t_solve *)malloc(sizeof(t_solve));
	oc[0] = cam[0] - c->xyz[0];
	oc[1] = cam[1] - c->xyz[1];
	oc[2] = cam[2] - c->xyz[2];
	k1 = dot_product(d, d) - (1 + c->k * c->k) * dot_product(d, c->v) * dot_product(d, c->v);
	k2 = 2 * (dot_product(oc, d) - (1 + c->k * c->k) * dot_product(d, c->v) * dot_product(oc, c->v));
	k3 = dot_product(oc, oc) - (1 + c->k * c->k) * dot_product(oc, c->v) * dot_product(oc, c->v);
	discrim = k2 * k2 - 4 * k1 * k3;
	if (discrim < 0)
	{
		solve->s1 = 1000000;
		solve->s2 = 1000000;
	}
	else
	{
		solve->s1 = (-k2 + sqrt(discrim)) / (2 * k1);
		solve->s2 = (-k2 - sqrt(discrim)) / (2 * k1);
	}
	return (solve);
}

t_solve	*intersect_sphere(double *cam, double *d, t_sphere *s)
{
	double oc[3];
	t_solve *solve;
	double 	k1 = 0;
	double	k2 = 0;
	double	k3 = 0;
	double discrim = 0;

	solve = (t_solve *)malloc(sizeof(t_solve));
	oc[0] = cam[0] - s->xyz[0];
	oc[1] = cam[1] - s->xyz[1];
	oc[2] = cam[2] - s->xyz[2];
	k1 = dot_product(d, d);
	k2 = 2 * dot_product(oc, d);
	k3 = dot_product(oc, oc) - s->r * s->r;
	discrim = k2 * k2 - 4 * k1 * k3;
	if (discrim < 0)
	{
		solve->s1 = 1000000;
		solve->s2 = 1000000;
	}
	solve->s1 = (-k2 + sqrt(discrim)) / (2 * k1);
	solve->s2 = (-k2 - sqrt(discrim)) / (2 * k1);
	return (solve);
}

t_solve	*intersect_plane(double *cam, double *d, t_plane *p)
{
	double oc[3];
	double v[3];
	double	k1;
	double	k2;
	t_solve *solve;

	solve = (t_solve *)malloc(sizeof(t_solve));
	oc[0] = cam[0] - p->xyz[0];
	oc[1] = cam[1] - p->xyz[1];
	oc[2] = cam[2] - p->xyz[2];
	k1 = (dot_product(oc, p->v));
	k2 = (dot_product(d, p->v));
	if (k2 != 0)
		solve->s1 = -k1 / k2;
	else
		solve->s1 = 1000000;
	solve->s2 = solve->s1;
	return (solve);
}

#define NUM_FIG 7

t_closest	*closest_intersection(double *cam, double *d, double min, int max)
{
	t_closest	*closest;
	t_solve		*solve;

	t_sphere	**sphere;
	t_plane		**plane;
	t_cylinder	**cylinder;
	t_cone		**cone;

	closest = NULL;
	closest = (t_closest *)malloc(sizeof(t_closest));
	closest->t = 2000;
	closest->sphere = NULL;
	closest->plane = NULL;
	closest->cylinder = NULL;
	closest->cone = NULL;
	closest->type = (char **)malloc(sizeof(char *) * NUM_FIG);
	
	sphere = (t_sphere **)malloc(sizeof(t_sphere *) * 4);
	sphere[0] = ft_sphere_create();
	sphere[1] = ft_sphere_create1();
	sphere[2] = ft_sphere_create2();
	
	plane = (t_plane **)malloc(sizeof(t_plane *) * 4);
	plane[0] = ft_plane_create();
	plane[1] = ft_plane_create1();

	cylinder = (t_cylinder **)malloc(sizeof(t_cylinder *) * 4);
	cylinder[0] = ft_cylinder_create();

	cone = (t_cone **)malloc(sizeof(t_cone *) * 4);
	cone[0] = ft_cone_create();

	closest->type[0] = "sphere";
	closest->type[1] = "sphere";
	closest->type[2] = "sphere";
	closest->type[3] = "plane";
	closest->type[4] = "plane";
	closest->type[5] = "cylinder";
	closest->type[6] = "cone";

	int i = 0;
	int ss = 0;
	int pp = 0;
	int	cy = 0;
	int	co = 0;
	while (i < NUM_FIG) // count of objects in the scene
	{
		if (ft_strcmp(closest->type[i], "sphere") == 0)
		{
			solve = intersect_sphere(cam, d, sphere[ss]);
			if (solve->s1 < closest->t && min < solve->s1 && solve->s1 < max)
			{
				closest->t = solve->s1;
				closest->sphere = sphere[ss];
			}
			if (solve->s2 < closest->t && min < solve->s2 && solve->s2 < max)
			{
				closest->t = solve->s2;
				closest->sphere = sphere[ss];
			}
			ss++;
		}
		else if (ft_strcmp(closest->type[i], "plane") == 0)
		{
			solve = intersect_plane(cam, d, plane[pp]);
			if (solve->s1 < closest->t && min < solve->s1 && solve->s1 < max)
			{
				closest->t = solve->s1;
				closest->plane = plane[pp];
			}
			if (solve->s2 < closest->t && min < solve->s2 && solve->s2 < max)
			{
				closest->t = solve->s2;
				closest->plane = plane[pp];
			}
			pp++;
		}
		else if (ft_strcmp(closest->type[i], "cylinder") == 0)
		{
			solve = intersect_cylinder(cam, d, cylinder[cy]);
			if (solve->s1 < closest->t && min < solve->s1 && solve->s1 < max)
			{
				closest->t = solve->s1;
				closest->cylinder = cylinder[cy];
			}
			if (solve->s2 < closest->t && min < solve->s2 && solve->s2 < max)
			{
				closest->t = solve->s2;
				closest->cylinder = cylinder[cy];
			}
			cy++;
		}
		else if (ft_strcmp(closest->type[i], "cone") == 0)
		{
			solve = intersect_cone(cam, d, cone[co]);
			if (solve->s1 < closest->t && min < solve->s1 && solve->s1 < max)
			{
				closest->t = solve->s1;
				closest->cone = cone[co];
			}
			if (solve->s2 < closest->t && min < solve->s2 && solve->s2 < max)
			{
				closest->t = solve->s2;
				closest->cone = cone[co];
			}
			co++;
		}
		i++;
	}
	if (closest->t == 2000)
	{
		free(closest);
		return (NULL);
	}
	return (closest);
}

int	trace_ray(double *cam, double *d, int min, int max, t_mlx *mlx)
{
	t_closest	*closest;

	closest = closest_intersection(cam, d, min, max);
	if (closest == NULL)
		return (0x0);
	int i = 0;
	double tmp;
	double point[3];
	double normal[3];

	int r = 0;
	int g = 0;
	int b = 0;

	while (i < NUM_FIG)
	{
		point[0] = cam[0] + (closest->t * d[0]);
		point[1] = cam[1] + (closest->t * d[1]);
		point[2] = cam[2] + (closest->t * d[2]);
		if (ft_strcmp(closest->type[i], "sphere") == 0 && closest->sphere)
		{
			normal[0] = point[0] - closest->sphere->xyz[0];
			normal[1] = point[1] - closest->sphere->xyz[1];
			normal[2] = point[2] - closest->sphere->xyz[2];

			normal[0] = (normal[0] / length(normal));
			normal[1] = (normal[1] / length(normal));
			normal[2] = (normal[2] / length(normal));

			tmp = ft_light(point, normal, d, closest->sphere->specular);
			r = (closest->sphere->color & 0xff0000) >> 16;
			g = (closest->sphere->color & 0x00ff00) >> 8;
			b = (closest->sphere->color & 0x0000ff);
		}
		else if (ft_strcmp(closest->type[i], "plane") == 0 && closest->plane)
		{
			normal[0] = closest->plane->v[0];
			normal[1] = closest->plane->v[1];
			normal[2] = closest->plane->v[2];

			normal[0] = (normal[0] / length(normal));
			normal[1] = (normal[1] / length(normal));
			normal[2] = (normal[2] / length(normal));

			if (dot_product(d, closest->plane->v) > 0)
			{
				normal[0] = -normal[0];
				normal[1] = -normal[1];
				normal[2] = -normal[2];
			}
		
			tmp = ft_light(point, normal, d, closest->plane->specular);
			r = (closest->plane->color & 0xff0000) >> 16;
			g = (closest->plane->color & 0x00ff00) >> 8;
			b = (closest->plane->color & 0x0000ff);
		}
		else if (ft_strcmp(closest->type[i], "cylinder") == 0 && closest->cylinder)
		{
			double	oc[3];
			oc[0] = cam[0] - closest->cylinder->xyz[0];
			oc[1] = cam[1] - closest->cylinder->xyz[1];
			oc[2] = cam[2] - closest->cylinder->xyz[2];

			double m;
			m = dot_product(d, closest->cylinder->v) * closest->t + dot_product(oc, closest->cylinder->v);
			normal[0] = point[0] - closest->cylinder->xyz[0] - closest->cylinder->v[0] * m;
			normal[1] = point[1] - closest->cylinder->xyz[1] - closest->cylinder->v[1] * m;
			normal[2] = point[2] - closest->cylinder->xyz[2] - closest->cylinder->v[2] * m;

			normal[0] = (normal[0] / length(normal));
			normal[1] = (normal[1] / length(normal));
			normal[2] = (normal[2] / length(normal));

			tmp = ft_light(point, normal, d, closest->cylinder->specular);
			r = (closest->cylinder->color & 0xff0000) >> 16;
			g = (closest->cylinder->color & 0x00ff00) >> 8;
			b = (closest->cylinder->color & 0x0000ff);
		}
		else if (ft_strcmp(closest->type[i], "cone") == 0 && closest->cone)
		{
			double	oc[3];
			oc[0] = cam[0] - closest->cone->xyz[0];
			oc[1] = cam[1] - closest->cone->xyz[1];
			oc[2] = cam[2] - closest->cone->xyz[2];

			double m;
			m = dot_product(d, closest->cone->v) * closest->t + dot_product(oc, closest->cone->v);
			normal[0] = point[0] - closest->cone->xyz[0] - (1 + closest->cone->k * closest->cone->k) * closest->cone->v[0] * m;
			normal[1] = point[1] - closest->cone->xyz[1] - (1 + closest->cone->k * closest->cone->k) * closest->cone->v[1] * m;
			normal[2] = point[2] - closest->cone->xyz[2] - (1 + closest->cone->k * closest->cone->k) * closest->cone->v[2] * m;

			normal[0] = (normal[0] / length(normal));
			normal[1] = (normal[1] / length(normal));
			normal[2] = (normal[2] / length(normal));

			tmp = ft_light(point, normal, d, closest->cone->specular);
			r = (closest->cone->color & 0xff0000) >> 16;
			g = (closest->cone->color & 0x00ff00) >> 8;
			b = (closest->cone->color & 0x0000ff);
		}
	i++;
	}

	int rr = r * tmp;
	int gg = g * tmp;
	int bb = b * tmp;

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

	rr = rr << 16;
	gg = gg << 8;

	free(closest);
	return (rr + gg + bb);
}

int	ft_manage(int key, t_sphere *sphere)
{
	if (key == 53)
		exit(0);
	return (0);
}

#define A 0
#define B 0
#define C 0

#define C00 cos(RAD * B) * cos(RAD * C)
#define C10 sin(RAD * A) * sin(RAD * B) * cos(RAD * C) + cos(RAD * A) * sin(RAD * C)
#define C20 -cos(RAD * A) * sin(RAD * B) * cos(RAD * C) + sin(RAD * A) * sin(RAD * C)

#define C01 -cos(RAD * B) * sin(RAD * C)
#define C11 -sin(RAD * A) * sin(RAD * B) * sin(RAD * C) + cos(RAD * A) * cos(RAD * C)
#define C21 cos(RAD * A) * sin(RAD * B) * sin(RAD * C) + sin(RAD * A) * cos(RAD * C)

#define C02 sin(RAD * B)
#define C12 -sin(RAD * A) * cos(RAD * B)
#define C22 cos(RAD * A) * cos(RAD * B)

int main() // int argc, char **argv
{
	double direction[3];
	t_mlx		*mlx;
	double		*cam;
	double		cw;
	double		ch;
	int		color;
	double 	vh;
	double	vw;

	int		x;
	int		y;

	cw = 600;
	ch = 600;
	vh = 1;
	vw = 1;

	cam = (double *)malloc(sizeof(double) * 3);

	// cam[0] = -20;
	// cam[1] = 3;
	// cam[2] = 5;

	cam[0] = 0;
	cam[1] = 5;
	cam[2] = -30;

	double camera_rotation[3][3] = {
		{C00, C01, C02},
		{C10, C11, C12},
		{C20, C21, C22}
		};

	// printf("------------------\n");

	// for(int k = 0; k < 3; k++)
	// {
	// 	for (int kk = 0; kk < 3; kk++)
	// 	{
	// 		printf("%f | ", camera_rotation[k][kk]);
	// 	}
	// 	printf("\n");
	// }

	// printf("------------------\n");

	int max = 100000;

	mlx = ft_create_mlx();
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "42");
	mlx->img = mlx_new_image(mlx->win, mlx->width, mlx->height);
	mlx->addr = mlx_get_data_addr(mlx->img, &(mlx->bpp), &(mlx->size_line), &(mlx->endian));
	y = -ch / 2;
	while (y < ch / 2)
	{
		x = -cw / 2;
		while (x < cw / 2)
		{
			direction[0] = x * vw * 0.5 / cw;
			direction[1] = y * vh * 0.5 / ch;
			direction[2] = 1;

			double  res[3] = {0, 0, 0};

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					res[i] += direction[j] * camera_rotation[i][j]; 
				}
			}
			direction[0] = res[0];
			direction[1] = res[1];
			direction[2] = res[2];

			color = trace_ray(cam, direction, 1, max, mlx);
			ft_pixel_put(mlx, x + cw/2, ch/2 - y - 1, color);
			x++;
		}
		y++;
	}
	mlx_hook(mlx->win, 2, 5, ft_manage, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_loop(mlx->mlx);
	return (0);
}
