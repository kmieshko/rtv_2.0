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
# include <errno.h>
# include "mlx.h"

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <OpenCL/OpenCL.h>

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

# define DIST	1.0
# define T_MIN	1.0
# define T_MAX	1000.0
# define NB_ITEMS	20
# define FILE_BUFFER	4096
# define LINE_SIZE	128

typedef struct	s_koef
{
	double		k1;
	double		k2;
	double		k3;
	double		discrim;
}				t_koef;

typedef struct	s_closest
{
	double		t;
	int			id;
	int			type;
}				t_closest;

typedef struct	s_solve
{
	double		t1;
	double		t2;
	int			type;
	int			id;
}				t_solve;

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_light
{
	int			type;
	char		*char_type;
	double		intensity;
	t_vector	ray;
}				t_light;

typedef struct	s_plane
{
	t_vector	center;
	t_vector	vector;
	int			color;
	int			specular;
	double		reflect;
	double		refract;
	double		transparency;
}				t_plane;

typedef struct	s_sphere
{
	t_vector	center;
	double		radius;
	int			color;
	int			specular;
	double		reflect;
	double		refract;
	double		transparency;
}				t_sphere;

typedef struct	s_cylinder
{
	t_vector	center;
	t_vector	vector;
	double		radius;
	double		maxm;
	int			color;
	int			specular;
	double		reflect;
	double		refract;
	double		transparency;
}				t_cylinder;

typedef struct	s_cone
{
	t_vector	center;
	t_vector	vector;
	double		k;
	double		maxm;
	double		minm;
	int			color;
	int			specular;
	double		reflect;
	double		refract;
	double		transparency;
}				t_cone;

typedef struct	s_figure
{
	t_vector	point;
	t_vector	normal;
	t_vector	ray;
	int			specular;
	int			color;
	double		reflect;
	double		refract;
	double		transparency;
}				t_figure;

typedef struct	s_scene
{
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_cone		*cone;
	t_light		*light;
	int			nb_planes;
	int			nb_spheres;
	int			nb_cylinders;
	int			nb_cones;
	int			nb_figures;
	int			nb_lights;
	t_vector	dir;
	t_vector	cam;
	t_vector	angle;
	int			reflection_depth;
	int			refraction_depth;
	double		t_min;
	double		t_max;
	int			win_w;
	int			win_h;
	int			vw;
	int			vh;
	double		camera_rotation[3][3];
}				t_scene;

typedef struct	s_window
{
	SDL_Event	e;
	SDL_Surface	*surface;
	SDL_Window	*window;
	int			quit;
	int			win_w;
	int			win_h;
}				t_window;

int				ft_clamp(int color);
double			ft_clamp_with_param(double value, double min, double max);
t_figure		ft_closest_figure(t_scene scene, t_vector cam, t_vector ray, t_closest closest);
t_closest		ft_closest_intersection(t_vector cam, t_vector ray, t_scene scene);
t_solve			ft_intersect_cone(t_vector cam, t_vector ray, t_cone co);
t_solve			ft_intersect_cylinder(t_vector cam, t_vector ray, t_cylinder cy);
t_solve			ft_intersect_plane(t_vector cam, t_vector ray, t_plane p);
t_solve			ft_intersect_sphere(t_vector cam, t_vector ray, t_sphere s);
double			ft_light(t_figure f, t_vector ray, t_scene scene);
void			ft_pixel_put(SDL_Surface *surface, int x, int y, int color);
int				trace_ray(t_vector cam, t_vector ray, t_scene scene, int recursion_depth, int refraction_depth);
t_vector		reflect_ray(t_vector normal, t_vector ray);
double			dot(t_vector vect1, t_vector vect2);
t_vector		mult(double num, t_vector vector);
t_vector		sub(t_vector vector1, t_vector vector2);
t_vector		add(t_vector vector1, t_vector vector2);
double			length(t_vector vector);
t_vector		get_normal(t_vector vector);

/* PARSER */

void		ft_free(void **arr);
void		move_position(char **position);
void		find_next_figure_bracket(char **position);
void		ft_set_vector_value(t_vector *vector, char *arr);
void		check_vector(t_vector vec, char *value);
void		ft_error(char *str);
void		ft_error_missing_in_block(char *needle, char *temp, char *merge_str);
char		*ft_find_coord(char *res, char *position, char *needle);
char		*ft_find_value(char *res, char *position, char *needle);
t_scene		*parse_scene(char *filename);
char		*read_cone(t_scene *scene, char *position);
char		*read_cylinder(t_scene *scene, char *position);
char		*read_light(t_scene *scene, char *position);
char		*read_plane(t_scene *scene, char *position);
char		*read_scene(t_scene *scene, char *position);
char		*read_sphere(t_scene *scene, char *position);

#endif
