/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:46:03 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/25 16:46:04 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	check_reader(char *str, char **item_name)
{
	if (ft_strncmp(*item_name, str, ft_strlen(str)) == 0)
	{
		*item_name += ft_strlen(str);
		return (1);
	}
	return (0);
}

static void	ft_select_reader(t_scene *scene, char *position)
{
	while (*position)
	{
		while (*position && ft_isspace(*position))
			position++;
		if (check_reader("scene", &position))
			position = read_scene(scene, position);
		else if (check_reader("light", &position))
			position = read_light(scene, position);
		else if (check_reader("sphere", &position))
			position = read_sphere(scene, position);
		else if (check_reader("plane", &position))
			position = read_plane(scene, position);
		else if (check_reader("cylinder", &position))
			position = read_cylinder(scene, position);
		else if (check_reader("cone", &position))
			position = read_cone(scene, position);
		else
			break ;
	}
}

static t_scene	*new_scene(void)
{
	t_scene *scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	scene->nb_planes = 0;
	scene->nb_spheres = 0;
	scene->nb_cylinders = 0;
	scene->nb_cones = 0;
	scene->nb_figures = 0;
	scene->nb_lights = 0;
	scene->light = (t_light *)malloc(sizeof(t_light) * NB_ITEMS);
	scene->sphere = (t_sphere *)malloc(sizeof(t_sphere) * NB_ITEMS);
	scene->plane = (t_plane *)malloc(sizeof(t_plane) * NB_ITEMS);
	scene->cylinder = (t_cylinder *)malloc(sizeof(t_cylinder) * NB_ITEMS);
	scene->cone = (t_cone *)malloc(sizeof(t_cone) * NB_ITEMS);
	return (scene);
}

t_scene		*parse_scene(char *filename)
{
	int		fd;
	char	*position;
	char 	*tmp;
	char	file[FILE_BUFFER];
	t_scene	*scene;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
		ft_error(strerror(errno));
	file[read(fd, file, FILE_BUFFER)] = '\0';
	close(fd);
	position = ft_strdup(ft_tolowercase(file));
	position = replace_match(position, '\n');
	position = replace_match(position, '{');
	position = replace_match(position, '}');
	position = rm_symb(position, ' ');
	position = rm_symb(position, '\t');
	tmp = position;
	if (!(*position))
		ft_error("Empty file");
	scene = new_scene();
	ft_select_reader(scene, position);
	if (!scene->nb_figures || !scene->nb_lights)
		ft_error("scene objects missing");
	ft_strdel(&tmp);
	return (scene);
}
