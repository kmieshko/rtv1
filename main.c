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

	mlx->closest = NULL;

	mlx->closest = (t_closest *)malloc(sizeof(t_closest));
	
	mlx->closest->figure = (void**)malloc(sizeof(mlx->closest->figure) * 1024);
	mlx->closest->type = (char **)malloc(sizeof(char *) * 1024);
	mlx->closest->nb_fig = 0;
	mlx->closest->sphere = NULL;
	mlx->closest->plane = NULL;
	mlx->closest->cylinder = NULL;
	mlx->closest->cone = NULL;
	return (mlx);
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
	else
	{
		solve->s1 = (-k2 + sqrt(discrim)) / (2 * k1);
		solve->s2 = (-k2 - sqrt(discrim)) / (2 * k1);
	}
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

void	ft_null_closest(t_closest *closest)
{
	closest->sphere = NULL;
	closest->plane = NULL;
	closest->cylinder = NULL;
	closest->cone = NULL;
}

t_closest	*closest_intersection(double *cam, double *d, double min, int max, t_closest *mlx)
{
	t_closest	*closest;
	t_solve		*solve;
	int			i;

	closest = mlx;
	closest->t = max;
	ft_null_closest(closest);
	i = 0;
	while (i < closest->nb_fig)
	{
		if (ft_strcmp(closest->type[i], "sphere") == 0)
		{
			solve = intersect_sphere(cam, d,(t_sphere *)closest->figure[i]);
			if (solve->s2 < closest->t &&  solve->s2 > min && solve->s2 < max)
			{
				ft_null_closest(closest);
				closest->t = solve->s2;
				closest->sphere = (t_sphere *)closest->figure[i];
			}
		}
		else if (ft_strcmp(closest->type[i], "plane") == 0)
		{
			solve = intersect_plane(cam, d, (t_plane *)closest->figure[i]);
			if (solve->s2 < closest->t &&  solve->s2 > min && solve->s2 < max)
			{
				ft_null_closest(closest);
				closest->t = solve->s2;
				closest->plane = (t_plane *)closest->figure[i];
			}
		}
		else if (ft_strcmp(closest->type[i], "cylinder") == 0)
		{
			solve = intersect_cylinder(cam, d,  (t_cylinder *)closest->figure[i]);
			if (solve->s2 < closest->t &&  solve->s2 > min && solve->s2 < max)
			{
				ft_null_closest(closest);
				closest->t = solve->s2;
				closest->cylinder = (t_cylinder *)closest->figure[i];
			}
		}
		else if (ft_strcmp(closest->type[i], "cone") == 0)
		{
			solve = intersect_cone(cam, d,  (t_cone *)closest->figure[i]);
			if (solve->s2 < closest->t &&  solve->s2 > min && solve->s2 < max)
			{
				ft_null_closest(closest);
				closest->t = solve->s2;
				closest->cone = (t_cone *)closest->figure[i];
			}
		}
		i++;
	}
	if (closest->t == max)
	{
		return (NULL);
	}
	return (closest);
}

int	trace_ray(double *cam, double *d, int min, int max, t_closest *mlx)
{
	t_closest	*closest;

	closest = closest_intersection(cam, d, min, max, mlx);
	if (closest == NULL)
		return (0x0);
	int i = 0;
	double tmp = 1;
	double point[3];
	double normal[3];

	int r = 0;
	int g = 0;
	int b = 0;

	point[0] = cam[0] + (closest->t * d[0]);
	point[1] = cam[1] + (closest->t * d[1]);
	point[2] = cam[2] + (closest->t * d[2]);

	while (i < closest->nb_fig)
	{
		if (ft_strcmp(closest->type[i], "sphere") == 0 && closest->sphere)
		{
			normal[0] = point[0] - closest->sphere->xyz[0];
			normal[1] = point[1] - closest->sphere->xyz[1];
			normal[2] = point[2] - closest->sphere->xyz[2];

			normal[0] = (normal[0] / length(normal));
			normal[1] = (normal[1] / length(normal));
			normal[2] = (normal[2] / length(normal));

			r = (closest->sphere->color & 0xff0000) >> 16;
			g = (closest->sphere->color & 0x00ff00) >> 8;
			b = (closest->sphere->color & 0x0000ff);

			tmp = ft_light(point, normal, d, closest->sphere->specular, closest);
			ft_null_closest(closest);
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

			r = (closest->plane->color & 0xff0000) >> 16;
			g = (closest->plane->color & 0x00ff00) >> 8;
			b = (closest->plane->color & 0x0000ff);

			tmp = ft_light(point, normal, d, closest->plane->specular, closest);
			ft_null_closest(closest);
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

			r = (closest->cylinder->color & 0xff0000) >> 16;
			g = (closest->cylinder->color & 0x00ff00) >> 8;
			b = (closest->cylinder->color & 0x0000ff);

			tmp = ft_light(point, normal, d, closest->cylinder->specular, closest);
			ft_null_closest(closest);
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

			r = (closest->cone->color & 0xff0000) >> 16;
			g = (closest->cone->color & 0x00ff00) >> 8;
			b = (closest->cone->color & 0x0000ff);

			tmp = ft_light(point, normal, d, closest->cone->specular, closest);
			ft_null_closest(closest);
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

	return (rr + gg + bb);
}

int	ft_manage(int key)
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

int main(int argc, char **argv)
{
	double direction[3];
	t_mlx		*mlx;
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

	if (argc != 2)
	{
		ft_putstr("Error: use one scene file as argument!\n");
		return (0);
	}

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
	ft_read_scene(argv[1], mlx->closest);
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
			color = trace_ray(mlx->closest->cam->xyz, direction, 1, max, mlx->closest);
			ft_pixel_put(mlx, x + cw/2, ch/2 - y - 1, color);
			x++;
		}
		y++;
	}

	// for (int i = 0; i < 10; ++i)
	// {
	// 	if (mlx->closest->figure[i])
	// 	{
	// 		printf("closest->figure[%d] = %s\n", i, mlx->closest->type[i]);
	// 		if (ft_strcmp(mlx->closest->type[i], "sphere") == 0)
	// 			ft_print_sphere(i, mlx->closest->figure);
	// 		else if (ft_strcmp(mlx->closest->type[i], "plane") == 0)
	// 			ft_print_plane(i, mlx->closest->figure);	
	// 		else if (ft_strcmp(mlx->closest->type[i], "cylinder") == 0)
	// 			ft_print_cylinder(i, mlx->closest->figure);	
	// 		else if (ft_strcmp(mlx->closest->type[i], "cone") == 0)
	// 			ft_print_cone(i, mlx->closest->figure);	
	// 		else if (ft_strcmp(mlx->closest->type[i], "light") == 0)
	// 			ft_print_light(i, mlx->closest->figure);
	// 		else if (ft_strcmp(mlx->closest->type[i], "camera") == 0)
	// 			ft_print_camera(i, mlx->closest->figure);
	// 	}
	// }

	mlx_hook(mlx->win, 2, 5, ft_manage, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_loop(mlx->mlx);
	return (0);
}

void		ft_print_sphere(int i, void **res)
{
	t_sphere	*sphere = res[i];

	printf("Sphere\n");
	printf("Radius: %f\n", sphere->r);
	printf("Center:");
	for (int j = 0; j < 3; j++)
		printf(" %f |", sphere->xyz[j]);
	printf("\n");
	printf("Color: %#x\n", sphere->color);
	printf("Specular: %d\n", sphere->specular);
	printf("\n");
}

void		ft_print_plane(int i, void **res)
{
	t_plane	*plane = res[i];

	printf("Plane\n");
	printf("Center:");
	for (int j = 0; j < 3; j++)
		printf(" %f |", plane->xyz[j]);
	printf("\n");
	printf("Vector:");
	for (int j = 0; j < 3; j++)
		printf(" %f |", plane->v[j]);
	printf("\n");
	printf("Color: %#x\n", plane->color);
	printf("Specular: %d\n", plane->specular);
	printf("\n");
}

void		ft_print_cylinder(int i, void **res)
{
	t_cylinder	*cylinder = res[i];

	printf("Cylinder\n");
	printf("Radius: %f\n", cylinder->r);
	printf("Center:");
	for (int j = 0; j < 3; j++)
		printf(" %f |", cylinder->xyz[j]);
	printf("\n");
	printf("Vector:");
	for (int j = 0; j < 3; j++)
		printf(" %f |", cylinder->v[j]);
	printf("\n");
	printf("Color: %#x\n", cylinder->color);
	printf("Specular: %d\n", cylinder->specular);
	printf("\n");
}

void		ft_print_cone(int i, void **res)
{
	t_cone	*cone = res[i];

	printf("Cone\n");
	printf("Tangle: %f\n", cone->k);
	printf("Center:");
	for (int j = 0; j < 3; j++)
		printf(" %f |", cone->xyz[j]);
	printf("\n");
	printf("Vector:");
	for (int j = 0; j < 3; j++)
		printf(" %f |", cone->v[j]);
	printf("\n");
	printf("Color: %#x\n", cone->color);
	printf("Specular: %d\n", cone->specular);
	printf("\n");
}

void		ft_print_light(int i, void **res)
{
	t_light	*light = res[i];

	printf("Light\n");
	printf("Type: %s\n", light->type);
	printf("Intens: %f\n", light->intensity);
	printf("Center:");
	for (int j = 0; j < 3; j++)
		printf(" %f |", light->xyz[j]);
	printf("\n");
	printf("\n");
}

void		ft_print_camera(int i, void **res)
{
	t_camera	*cam = res[i];

	printf("Camera\n");
	printf("Center:");
	for (int j = 0; j < 3; j++)
		printf(" %f |", cam->xyz[j]);
	printf("\n");
	printf("\n");
}
