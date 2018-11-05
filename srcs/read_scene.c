/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:48:30 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/25 16:48:31 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	check_scene(t_scene **scene)
{
	check_vector((*scene)->cam, "scene->cam");
	(*scene)->refraction_depth = round(ft_clamp_with_param((*scene)->refraction_depth, 0, 10));
	(*scene)->reflection_depth = round(ft_clamp_with_param((*scene)->reflection_depth, 0, 10));
}

char	*read_scene(t_scene *scene, char *position)
{
	char	res[LINE_SIZE];

	scene->win_w = 720;
	scene->win_h = 720;
	move_position(&position);
	ft_set_vector_value(&(scene->cam), ft_find_coord(res, position, "position"));
	ft_set_vector_value(&(scene->angle), ft_find_coord(res, position, "rotation"));
	scene->reflection_depth = ft_atoi(ft_find_value(res, position, "reflection"));
	scene->refraction_depth = ft_atoi(ft_find_value(res, position, "refraction"));
	check_scene(&scene);
	find_next_figure_bracket(&position);
	return (position);
}
