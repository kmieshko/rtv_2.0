/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:49:24 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/25 16:49:25 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	check_light(t_light **light)
{
	if ((*light)->type < 1 || (*light)->type > 3)
		ft_error("invalid light type");
	if ((*light)->intensity < 0.01)
		(*light)->intensity = 0.01;
	else if ((*light)->intensity > 1)
		(*light)->intensity = 1;
	if ((*light)->type == 2)
		check_vector((*light)->ray, "light->position");
	if ((*light)->type == 3)
		check_vector((*light)->ray, "light->direction");
}

char	*read_light(t_scene *scene, char *position)
{
	t_light *light;
	char	res[LINE_SIZE];

	move_position(&position);
	light = (t_light*)malloc(sizeof(t_light) + 1);
	light->char_type = ft_find_value(res, position, "type");
	if (ft_strcmp("ambient", light->char_type) == 0)
		light->type = 1;
	if (ft_strcmp("point", light->char_type) == 0)
	{
		light->type = 2;
		ft_set_vector_value(&(light->ray), ft_find_coord(res, position, "position"));
	}
	else if (ft_strcmp("direction", light->char_type) == 0)
	{
		light->type = 3;
		ft_set_vector_value(&(light->ray), ft_find_coord(res, position, "position"));
	}
	light->intensity = ft_atod(ft_find_value(res, position, "intensity"));
	check_light(&light);
	find_next_figure_bracket(&position);
	scene->light[scene->nb_lights] = *light;
	scene->nb_lights = scene->nb_lights + 1;
	free(light);
	return (position);
}
