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

typedef struct	s_light
{
	char		*type;
	double		intensity;
	double		xyz[3];
}				t_light;

typedef struct	s_direction
{
	double		xyz[3];
}				t_direction;

typedef struct	s_cam
{
	double		xyz[3];
}				t_cam;

typedef struct	s_sphere
{
	int			r;
	double		xyz[3];
	int			color;
	double		specular;
}				t_sphere;

typedef struct	s_solve
{
	double		s1;
	double		s2;
}				t_solve;

typedef struct	s_oc
{
	double	xyz[3];
}				t_oc;

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
	double		inten;
}				t_mlx;

double			dot_product(double *a, double *b, size_t n);
double			length(double vector[]);
void			ft_pixel_put(t_mlx *mlx, int x, int y, int color);
double	ft_light(double *point, double *normal, t_direction *d, int specular);

#endif

//strcmp in ft_light