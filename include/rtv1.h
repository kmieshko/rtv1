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
# include "../libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <pthread.h>

# define RAD M_PI / 180
# define C(x) cos(RAD * x)
# define S(x) sin(RAD * x)
# define C00(b, c) C(b) * C(c)
# define C10(a, b, c) S(a) * S(b) * C(c) + C(a) * S(c)
# define C20(a, b, c) -C(a) * S(b) * C(c) + S(a) * S(c)
# define C01(b, c) -C(b) * S(c)
# define C11(a, b, c) -S(a) * S(b) * S(c) + C(a) * C(c)
# define C21(a, b, c) C(a) * S(b) * S(c) + S(a) * C(c)
# define C02(b) S(b)
# define C12(a, b) -S(a) * C(b)
# define C22(a, b) C(a) * C(b)

typedef struct	s_count
{
	int			cam;
	int			rot;
	int			light;
}				t_count;

typedef struct	s_vect
{
	double		norm[3];
	double		d[3];
	double		point[3];
}				t_vect;

typedef struct	s_koef
{
	double		k1;
	double		k2;
	double		k3;
	double		discrim;
}				t_koef;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
	double		inten;
}				t_color;

typedef struct	s_camera
{
	double		xyz[3];
}				t_camera;

typedef struct	s_rotation
{
	int			angle[3];
}				t_rotation;

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
	int			specular;
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
	double		t;
	char		**type;
	void		**figure;
	int			nb_fig;
	t_camera	*cam;
	t_rotation	*rot;
	t_light		**light;
	int			id;
	int			max;
	double		min;
	t_color		*c;
}				t_closest;

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
	double		vh;
	double		vw;
	double		direction[3];
	double		camera_rotation[3][3];
	t_closest	*closest;
}				t_mlx;

double			dot_product(double *a, double *b);
double			length(double vector[]);
void			ft_pixel_put(t_mlx *mlx, int x, int y, int color);
double			ft_light(t_vect *v, int specular, t_closest *mlx);
t_closest		*closest_intersection(double *cam, double *d, t_closest *mlx);
int				trace_ray(double *cam, double *d, t_closest *mlx, int i);
t_mlx			*ft_create_mlx(void);
t_vect			*ft_create_vect(double *cam, double *d, double solve);
int				ft_check_fig(t_closest *closest, int i, int id, char *str);
int				clamp(int color);

void			ft_incorrect(char *type);
void			ft_wrong(char *type);
void			ft_null_line(char *line);
int				ft_exit_mouse(void);
int				ft_manage(int key);

int				ft_count_light(int fd, char *line, int i, t_closest *closest);
int				ft_count_cam(int fd, char *line, int i, t_closest *closest);
int				ft_count_rot(int fd, char *line, int i, t_closest *closest);
void			ft_check_cam_rot_light_inten_fig(t_count *count,
				t_light **light, int nb_fig);

char			*ft_tolowercase(char *str);
int				ft_count_coord(char *str);
void			ft_free(void **arr);
int				ft_check_type(char *line);

double			intersect_cylinder(double *cam, double *d, t_cylinder *c);
double			intersect_cone(double *cam, double *d, t_cone *c);
double			intersect_sphere(double *cam, double *d, t_sphere *s);
double			intersect_plane(double *cam, double *d, t_plane *p);

char			*ft_tolowercase(char *str);
void			ft_read_scene(char *str, t_closest *closest);
t_sphere		*ft_create_sphere(int fd, char *line, int iter,
				t_closest *closest);
t_plane			*ft_create_plane(int fd, char *line, int iter,
				t_closest *closest);
t_cylinder		*ft_create_cylinder(int fd, char *line, int iter,
				t_closest *closest);
t_cone			*ft_create_cone(int fd, char *line, int iter,
				t_closest *closest);
t_light			*ft_create_light(int fd, char *line, int iter,
				t_closest *closest);
t_camera		*ft_create_camera(int fd, char *line, int iter,
				t_closest *closest);
t_rotation		*ft_create_rotation(int fd, char *line, int iter,
				t_closest *closest);

#endif
