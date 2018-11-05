/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:49:35 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/25 16:49:36 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	check_cone(t_cone **cone)
{
	check_vector((*cone)->center, "cone->center");
	(*cone)->k = ft_clamp_with_param((*cone)->k, 0.01, 57);
	(*cone)->specular = round(ft_clamp_with_param((*cone)->specular, 0, 500));
	(*cone)->reflect = ft_clamp_with_param((*cone)->reflect, 0, 1);
	(*cone)->transparency = ft_clamp_with_param((*cone)->transparency, 0, 1);
}

char	*read_cone(t_scene *scene, char *position)
{
	t_cone	*cone;
	char		res[LINE_SIZE];

	if (scene->nb_cones >= NB_ITEMS)
		ft_error("number of cones is bigger then NB_ITEMS");
	cone = (t_cone *)malloc(sizeof(t_cone) + 1);
	move_position(&position);
	ft_set_vector_value(&(cone->center), ft_find_coord(res, position, "position"));
	ft_set_vector_value(&(cone->vector), ft_find_coord(res, position, "direction"));
	if (!(cone->vector.x == 0 && cone->vector.y == 0 && cone->vector.z == 0))
		cone->vector = get_normal(cone->vector);
	else
		ft_error("invalid cylinder direction parameters");
	cone->k = tan(RAD * ft_atod(ft_find_value(res, position, "angle")));
	cone->specular = ft_atoi(ft_find_value(res, position, "specular"));
	cone->reflect = ft_atod(ft_find_value(res, position, "reflection"));
	cone->refract = ft_atod(ft_find_value(res, position, "refraction_index_inside")) / 
					ft_atod(ft_find_value(res, position, "refraction_index_outside"));
	cone->transparency = ft_atod(ft_find_value(res, position, "transparency"));
	cone->color = ft_atoi_base(ft_find_value(res, position, "color"), 16);
	check_cone(&cone);
	find_next_figure_bracket(&position);
	scene->cone[scene->nb_cones] = *cone;
	scene->nb_cones = scene->nb_cones + 1;
	scene->nb_figures = scene->nb_figures + 1;
	free(cone);
	return (position);
}
