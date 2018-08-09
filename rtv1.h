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

#include <stdio.h> /////////////////////////////

# include <fcntl.h>
# include <mlx.h>

#define RAD M_PI / 180

typedef struct	s_camera
{
	double		xyz[3];
}				t_camera;

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
	int		specular;
}				t_cylinder;

typedef struct	s_cone
{
	double		k;
	double		xyz[3];
	double		v[3];
	int			color;
	int			specular;
}				t_cone;

typedef struct	s_sphere
{
	double		r;
	double		xyz[3];
	int			color;
	int			specular;
}				t_sphere;

typedef struct	s_plane
{
	double		xyz[3];
	double		v[3];
	int			color;
	int			specular;
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
	int			nb_fig;
	t_camera	*cam;
	t_light		**light;
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
	t_closest	*closest;

	char		*argv;
}				t_mlx;

// DRAW

double			dot_product(double *a, double *b);
double			length(double vector[]);
void			ft_pixel_put(t_mlx *mlx, int x, int y, int color);
double			ft_light(double *point, double *normal, double *d, int specular, t_closest *mlx);
t_closest		*closest_intersection(double *cam, double *d, double min, int max, t_closest *mlx);


// INTERSECT

void	ft_null_closest(t_closest *closest);

t_solve			*intersect_cylinder(double *cam, double *d, t_cylinder *c);
t_solve			*intersect_cone(double *cam, double *d, t_cone *c);
t_solve			*intersect_sphere(double *cam, double *d, t_sphere *s);
t_solve			*intersect_plane(double *cam, double *d, t_plane *p);

// MAP

void			ft_read_scene(char *str, t_closest *closest);

t_sphere		*ft_create_sphere(int fd, char *line);
t_plane			*ft_create_plane(int fd, char *line);
t_cylinder		*ft_create_cylinder(int fd, char *line);
t_cone			*ft_create_cone(int fd, char *line);
t_light			*ft_create_light(int fd, char *line);
t_camera		*ft_create_camera(int fd, char *line);


void		ft_incorrect(char *type);
void		ft_free(void **arr);
int			ft_count_coord(char *str);
char		*ft_tolowercase(char *str);


// PRINT MAP

void		ft_print_sphere(int i, void **res);
void		ft_print_plane(int i, void **res);
void		ft_print_cylinder(int i, void **res);
void		ft_print_cone(int i, void **res);
void		ft_print_light(int i, void **res);
//void		ft_print_camera(t_camera *cam);
void		ft_print_camera(int i, void **res);

#endif

//strcmp in ft_light