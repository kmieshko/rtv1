/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 12:21:11 by kmieshko          #+#    #+#             */
/*   Updated: 2018/07/16 12:21:12 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
#include "libft/libft.h"

# include <unistd.h>
# include <stdlib.h>
#include <stdio.h>

# include <mlx.h>

#define RAD M_PI / 180

typedef struct	s_light
{
	char		*type;
	double		intensity;
	double		xyz[3];
}				t_light;

typedef struct	s_cylinder
{
	double		r;
	double		xyz[3];
	double		v[3];
	int			color;
	double		specular;
}				t_cylinder;

typedef struct	s_cone
{
	double		k;
	double		xyz[3];
	double		v[3];
	int			color;
	double		specular;
}				t_cone;

typedef struct	s_sphere
{
	double		r;
	double		xyz[3];
	int			color;
	double		specular;
}				t_sphere;

typedef struct	s_plane
{
	double		xyz[3];
	double		v[3];
	int			color;
	double		specular;
}				t_plane;

typedef struct	s_closest
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_cone		*cone;
	double		t;
	char		**type;
	void		**figure;
}				t_closest;

typedef struct	s_solve
{
	double		s1;
	double		s2;
}				t_solve;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	int			size_line;
	int			bpp;
	int			endian;
	char		*addr;
	int			width;
	int			height;
	int			color;
	double		cam[3];
}				t_mlx;

double			dot_product(double *a, double *b);
double			length(double vector[]);
void			ft_pixel_put(t_mlx *mlx, int x, int y, int color);
double			ft_light(double *point, double *normal, double *d, int specular);
t_closest		*closest_intersection(double *cam, double *d, double min, int max);

#endif

//strcmp in ft_light