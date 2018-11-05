/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:50:01 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/25 16:50:02 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	check_sphere(t_sphere **sphere)
{
	check_vector((*sphere)->center, "sphere->center");
	(*sphere)->radius = ft_clamp_with_param((*sphere)->radius, 0.05, 500);
	(*sphere)->specular = round(ft_clamp_with_param((*sphere)->specular, 0, 500));
	(*sphere)->reflect = ft_clamp_with_param((*sphere)->reflect, 0, 1);
	(*sphere)->transparency = ft_clamp_with_param((*sphere)->transparency, 0, 1);
}

char	*read_sphere(t_scene *scene, char *position)
{
	t_sphere	*sphere;
	char		res[LINE_SIZE];

	if (scene->nb_spheres >= NB_ITEMS)
		ft_error("number of spheres is bigger then NB_ITEMS");
	sphere = (t_sphere *)malloc(sizeof(t_sphere) + 1);
	move_position(&position);
	ft_set_vector_value(&(sphere->center), ft_find_coord(res, position, "position"));
	sphere->radius = ft_atod(ft_find_value(res, position, "radius"));
	sphere->specular = ft_atoi(ft_find_value(res, position, "specular"));
	sphere->reflect = ft_atod(ft_find_value(res, position, "reflection"));
	sphere->refract = ft_atod(ft_find_value(res, position, "refraction_index_inside")) / 
					ft_atod(ft_find_value(res, position, "refraction_index_outside"));
	sphere->transparency = ft_atod(ft_find_value(res, position, "transparency"));
	sphere->color = ft_atoi_base(ft_find_value(res, position, "color"), 16);
	check_sphere(&sphere);
	find_next_figure_bracket(&position);
	scene->sphere[scene->nb_spheres] = *sphere;
	scene->nb_spheres = scene->nb_spheres + 1;
	scene->nb_figures = scene->nb_figures + 1;
	free(sphere);
	return (position);
}
