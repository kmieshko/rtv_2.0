/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:49:43 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/25 16:49:44 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	check_cylinder(t_cylinder **cylinder)
{
	check_vector((*cylinder)->center, "cylinder->center");
	(*cylinder)->radius = ft_clamp_with_param((*cylinder)->radius, 0.05, 500);
	(*cylinder)->specular = round(ft_clamp_with_param((*cylinder)->specular, 0, 500));
	(*cylinder)->reflect = ft_clamp_with_param((*cylinder)->reflect, 0, 1);
	(*cylinder)->transparency = ft_clamp_with_param((*cylinder)->transparency, 0, 1);
}

char	*read_cylinder(t_scene *scene, char *position)
{
	t_cylinder	*cyl;
	char		res[LINE_SIZE];

	if (scene->nb_cylinders >= NB_ITEMS)
		ft_error("number of cylinders is bigger then NB_ITEMS");
	cyl = (t_cylinder *)malloc(sizeof(t_cylinder) + 1);
	move_position(&position);
	ft_set_vector_value(&(cyl->center), ft_find_coord(res, position, "position"));
	ft_set_vector_value(&(cyl->vector), ft_find_coord(res, position, "direction"));
	if (!(cyl->vector.x == 0 && cyl->vector.y == 0 && cyl->vector.z == 0))
		cyl->vector = get_normal(cyl->vector);
	else
		ft_error("invalid cylinder direction parameters");
	cyl->radius = ft_atod(ft_find_value(res, position, "radius"));
	cyl->specular = ft_atoi(ft_find_value(res, position, "specular"));
	cyl->reflect = ft_atod(ft_find_value(res, position, "reflection"));
	cyl->refract = ft_atod(ft_find_value(res, position, "refraction_index_inside")) / 
					ft_atod(ft_find_value(res, position, "refraction_index_outside"));
	cyl->transparency = ft_atod(ft_find_value(res, position, "transparency"));
	cyl->color = ft_atoi_base(ft_find_value(res, position, "color"), 16);
	check_cylinder(&cyl);
	find_next_figure_bracket(&position);
	scene->cylinder[scene->nb_cylinders] = *cyl;
	scene->nb_cylinders = scene->nb_cylinders + 1;
	scene->nb_figures = scene->nb_figures + 1;
	free(cyl);
	return (position);
}
