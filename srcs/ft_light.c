/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 13:04:33 by kmieshko          #+#    #+#             */
/*   Updated: 2018/07/17 13:04:34 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double		get_intensity(t_figure f, t_scene scene, t_vector vec_l, int i)
{
	double		inten;
	t_vector	reflect;
	t_light		light;
	t_closest	closest;
	t_figure	closest_fig;
	t_closest	closest_from_light;
	t_closest	clos2;
	t_figure	clos_fig2;

	light = scene.light[i];
	inten = 0.0;
	if (light.type == 1)
		return (light.intensity);
	scene.t_min = 0.001;
	closest = ft_closest_intersection(f.point, vec_l, scene);
	closest_fig = ft_closest_figure(scene, f.point, vec_l, closest);
	if (!closest.type)
	{
		if (dot(f.normal, vec_l) > 0)
			inten += ((light.intensity * dot(f.normal, vec_l)) / (length(f.normal) * length(vec_l)));
		if (f.specular > 0)
		{
			reflect = reflect_ray(f.normal, vec_l);
			if (dot(reflect, f.ray) > 0)
				inten += light.intensity * pow(dot(reflect, f.ray) / (length(reflect) * length(f.ray)), f.specular);
		}
	}
	else
	{
		closest_from_light = ft_closest_intersection(light.ray, mult(-1, vec_l), scene);
		if (closest_from_light.id == closest.id)
		{
			if (closest_fig.transparency)
			{
				clos2 = ft_closest_intersection(closest_fig.point, vec_l, scene);
				clos_fig2 = ft_closest_figure(scene, closest_fig.point, vec_l, clos2);
				if (!clos2.type)
				{
					if (dot(f.normal, vec_l) > 0)
						inten += closest_fig.transparency * ((light.intensity * dot(f.normal, vec_l)) / (length(f.normal) * length(vec_l)));
				}
				else
				{
					if (clos_fig2.transparency)
					{
						if (dot(f.normal, vec_l) > 0)
							inten += clos_fig2.transparency * ((light.intensity * dot(f.normal, vec_l)) / (length(f.normal) * length(vec_l)));
					}
					else
						if (dot(f.normal, vec_l) > 0)
							inten = inten - 0.1 * closest_fig.transparency * ((light.intensity * dot(f.normal, vec_l)) / (length(f.normal) * length(vec_l)));
				}
			}
		}
	}
	return (inten);
}

double		ft_light(t_figure f, t_vector ray, t_scene scene)
{
	int			i;
	double		inten;
	t_vector	vec_l;

	inten = 0;
	i = 0;
	f.ray = ray;
	while (i < scene.nb_lights)
	{
		if (scene.light[i].type == 2)
		{
			vec_l = sub(scene.light[i].ray, f.point);
			scene.t_max = 1;
		}
		else if (scene.light[i].type == 3)
		{
			vec_l = scene.light[i].ray;
			scene.t_max = T_MAX;
		}
		inten += get_intensity(f, scene, vec_l, i);
		i++;
	}
	inten = ft_clamp_with_param(inten, 0, 1);
	return (inten);
}