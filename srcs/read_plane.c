/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:49:53 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/25 16:49:54 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	check_plane(t_plane **plane)
{
	check_vector((*plane)->center, "plane->center");
	(*plane)->specular = round(ft_clamp_with_param((*plane)->specular, 0, 500));
	(*plane)->reflect = ft_clamp_with_param((*plane)->reflect, 0, 1);
	(*plane)->transparency = ft_clamp_with_param((*plane)->transparency, 0, 1);
}

char	*read_plane(t_scene *scene, char *position)
{
	t_plane	*plane;
	char	res[LINE_SIZE];

	if (scene->nb_planes >= NB_ITEMS)
		ft_error("number of planes is bigger then NB_ITEMS");
	plane = (t_plane *)malloc(sizeof(t_plane) + 1);
	move_position(&position);
	ft_set_vector_value(&(plane->center), ft_find_coord(res, position, "position"));
	ft_set_vector_value(&(plane->vector), ft_find_coord(res, position, "direction"));
	if (plane->vector.x == 0 && plane->vector.y == 0 && plane->vector.z == 0)
		ft_error("invalid plane direction parameters");
	else
		plane->vector = get_normal(plane->vector);
	plane->specular = ft_atoi(ft_find_value(res, position, "specular"));
	plane->reflect = ft_atod(ft_find_value(res, position, "reflection"));
	plane->refract = ft_atod(ft_find_value(res, position, "refraction_index_inside")) / 
					ft_atod(ft_find_value(res, position, "refraction_index_outside"));
	plane->transparency = ft_atod(ft_find_value(res, position, "transparency"));
	plane->color = ft_atoi_base(ft_find_value(res, position, "color"), 16);
	check_plane(&plane);
	find_next_figure_bracket(&position);
	scene->plane[scene->nb_planes] = *plane;
	scene->nb_planes = scene->nb_planes + 1;
	scene->nb_figures = scene->nb_figures + 1;
	free(plane);
	return (position);
}
