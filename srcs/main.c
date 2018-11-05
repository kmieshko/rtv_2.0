/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:16:08 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/22 20:16:09 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_fill_camera_rotation(t_scene *scene, t_vector angle)
{
	int		a;
	int		b;
	int		c;

	a = angle.x;
	b = angle.y;
	c = angle.z;
	scene->camera_rotation[0][0] = C00(b, c);
	scene->camera_rotation[0][1] = C01(b, c);
	scene->camera_rotation[0][2] = C02(b);
	scene->camera_rotation[1][0] = C10(a, b, c);
	scene->camera_rotation[1][1] = C11(a, b, c);
	scene->camera_rotation[1][2] = C12(a, b);
	scene->camera_rotation[2][0] = C20(a, b, c);
	scene->camera_rotation[2][1] = C21(a, b, c);
	scene->camera_rotation[2][2] = C22(a, b);
}

static void	ft_get_direction(t_vector dir, t_scene *scene)
{
	int			i;
	int			j;
	double		res[3];
	double		tmp[3];

	tmp[0] = dir.x;
	tmp[1] = dir.y;
	tmp[2] = dir.z;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res[i] += tmp[j] * scene->camera_rotation[i][j];
			j++;
		}
		i++;
	}
	scene->dir.x = res[0];
	scene->dir.y = res[1];
	scene->dir.z = res[2];
}

static void		ft_main_loop(t_window *win, t_scene scene)
{
	int			x;
	int			y;
	int			color;

	scene.t_min = T_MIN;
	scene.t_max = T_MAX;
	scene.vw = 1;
	scene.vh = 1;
	win->win_w = scene.win_w;
	win->win_h = scene.win_h;
	y = -(scene.win_h / 2);
	ft_fill_camera_rotation(&scene, scene.angle);
	while (y < (scene.win_h / 2))
	{
		x = -(scene.win_w / 2);
		while (x < (scene.win_w / 2))
		{
			scene.dir.x = x * scene.vw * 0.5 / win->win_w;
			scene.dir.y = y * scene.vh * 0.5 / win->win_h;
			scene.dir.z = DIST;
			ft_get_direction(scene.dir, &scene);
			color = trace_ray(scene.cam, scene.dir, scene, scene.reflection_depth, scene.refraction_depth);
			ft_pixel_put(win->surface, x + win->win_w / 2, win->win_h / 2 - y - 1, color);
			x++;
		}
		y++;
	}
}

int			main(int argc, char **argv)
{
	t_window	win;
	t_scene		*scene;

	if (argc != 2)
		ft_error("Error: use one scene file as argument!");
	scene = parse_scene(argv[1]);
	win.quit = 0;
	win.surface = NULL;
	win.window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (0);
	win.window = SDL_CreateWindow(argv[1], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scene->win_w, scene->win_h, SDL_WINDOW_SHOWN);
	win.surface = SDL_GetWindowSurface(win.window);
	while (!win.quit)
	{
		while (SDL_PollEvent(&win.e) != 0)
		{
			if (win.e.type == SDL_QUIT)
				win.quit = 1;
			if (win.e.type == SDL_KEYDOWN)
			{
				if (win.e.key.keysym.sym == SDLK_ESCAPE)
				{
					win.quit = 1;
					break ;
				}
			}
		}
		ft_main_loop(&win, *scene);
		SDL_UpdateWindowSurface(win.window);
	}
	SDL_FreeSurface(win.surface);
	win.surface = NULL;
	SDL_DestroyWindow(win.window);
	win.window = NULL;
	SDL_Quit();
	// system("leaks RTv1");
	return (0);
}


