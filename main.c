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
	mlx->color = 0xff;
	return (mlx);
}

t_sphere	*ft_sphere_create(void)
{
	t_sphere *sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->xyz[0] = 0;
	sphere->xyz[1] = 1;
	sphere->xyz[2] = 3;
	sphere->r = 2;
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
	sphere->r = 2;
	sphere->color = 0x00ff00;
	sphere->specular = 100;
	return (sphere);
}

t_sphere	*ft_sphere_create2(void)
{
	t_sphere *sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->xyz[0] = -2;
	sphere->xyz[1] = 0;
	sphere->xyz[2] = 4;
	sphere->r = 2;
	sphere->color = 0x0000ff;
	sphere->specular = 100;
	return (sphere);
}

double		dot_product(double *a, double *b, size_t n)
{
	double		sum;
	size_t	i;

	i = 0;
	sum = 0;
	while (i < n)
	{
		sum += a[i] * b[i];
		i++;
	}
	return (sum);
}

double		length(double *vector)
{
	double	length;

	length = sqrt(dot_product(vector, vector, 3));
	return (length);
}

t_solve	*intersect(t_cam *c, t_direction *d, t_sphere *s)
{
	t_oc *oc;
	t_solve *solve;

	oc = (t_oc *)malloc(sizeof(t_oc));

	solve = (t_solve *)malloc(sizeof(t_solve));


	oc->xyz[0] = c->xyz[0] - s->xyz[0];
	oc->xyz[1] = c->xyz[1] - s->xyz[1];
	oc->xyz[2] = c->xyz[2] - s->xyz[2];

	// for (int k = 0; k < 3; k++)
	// 	printf("| %f |", oc->xyz[k]);
	// printf("\n");

	double 	k1 = 0;
	double	k2 = 0;
	double	k3 = 0;

	k1 = dot_product(d->xyz, d->xyz, 3);
	k2 = 2 * dot_product(oc->xyz, d->xyz, 3);
	k3 = dot_product(oc->xyz, oc->xyz, 3) - s->r * s->r;

	// printf("%f | %f | %f\n", k1, k2, k3);
	
	double discrim = k2 * k2 - 4 * k1 * k3;

	if (discrim < 0)
	{
		solve->s1 = 1000000;
		solve->s2 = 1000000;
	}
	solve->s1 = (-k2 + sqrt(discrim)) / (2 * k1);
	solve->s2 = (-k2 - sqrt(discrim)) / (2 * k1);
	return (solve);
}

int	trace_ray(t_cam *cam, t_direction *d, int min, int max, t_mlx *mlx)
{
	double		closest_t;
	t_sphere	*closest_sphere;
	t_solve		*solve;
	t_sphere	**sphere;


	sphere = (t_sphere **)malloc(sizeof(t_sphere *) * 3);
	

	sphere[0] = ft_sphere_create();
	sphere[1] = ft_sphere_create1();
	sphere[2] = ft_sphere_create2();

	closest_t = 10000; 
	closest_sphere = NULL;
	for (int i = 0; i < 3; i++) // count of objects in the scene
	{
		solve = intersect(cam, d, sphere[i]);

		// printf("%f | %f\n", solve->s1, solve->s2);

		if (solve->s1 < closest_t && min < solve->s1 && solve->s1 < max)
		{
			closest_t = solve->s1;
			closest_sphere = sphere[i];
		}
		if (solve->s2 < closest_t && min < solve->s2 && solve->s2 < max)
		{
			closest_t = solve->s2;
			closest_sphere = sphere[i];
		}
	}

	if (closest_sphere == NULL)
		return (0x0);

	double point[3];

	point[0] = cam->xyz[0] + (closest_t * d->xyz[0]);
	point[1] = cam->xyz[1] + (closest_t * d->xyz[1]);
	point[2] = cam->xyz[2] + (closest_t * d->xyz[2]);

	double normal[3];

	normal[0] = point[0] - closest_sphere->xyz[0];
	normal[1] = point[1] - closest_sphere->xyz[1];
	normal[2] = point[2] - closest_sphere->xyz[2];

	normal[0] = (normal[0] / length(normal));
	normal[1] = (normal[1] / length(normal));
	normal[2] = (normal[2] / length(normal));
	
	double tmp = ft_light(point, normal, d, closest_sphere->specular);

	// printf("%f\n", tmp);

	// tmp = 1;

	mlx->inten = tmp;

int	r = (closest_sphere->color & 0xff0000) >> 16;
int	g = (closest_sphere->color & 0x00ff00) >> 8;
int	b = (closest_sphere->color & 0x0000ff);

// int rd = r << 16;
// int gd = g << 8;
// int bd = b;

// printf("%d | %d | %d\n", rd, gd, bd);

	// return ((((int)(r * tmp)) << 16) + (((int)(g * tmp)) << 8) + (int)(b * tmp));
return (closest_sphere->color);
// return (r + g + b);
}

int	ft_manage(int key)
{
	if (key == 53)
		exit(0);
	return (0);
}

int main()
{
	t_direction *direction;
	t_cam		*cam;
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

	cam = (t_cam *)malloc(sizeof(t_cam));

	cam->xyz[0] = 0;
	cam->xyz[1] = 0;
	cam->xyz[2] = -10;

	int max = 100;

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
			direction->xyz[0] = x * vw * 0.5 / cw;
			direction->xyz[1] = y * vh * 0.5 / ch;
			direction->xyz[2] = 1;

// for (int j = 0; j < 3; j++)
// 	printf("%f |", direction->xyz[j]);
// printf("\n");

			color = trace_ray(cam, direction, 1, max, mlx);

			// if (color > 0)
			// 	printf("%#.6x\n", color);

			ft_pixel_put(mlx, x + cw/2, ch/2 - y, color);
			// mlx_pixel_put(mlx->mlx, mlx->win, x + cw/2, y + ch/2, color);
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
