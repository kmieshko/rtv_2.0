/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_closest_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:37:33 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:37:34 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_solve		get_solve(int i, t_scene s, t_vector cam, t_vector ray)
{
	t_solve		t;

	if (i < s.nb_planes)
	{
		t = ft_intersect_plane(cam, ray, s.plane[i]);
		t.id = i;
	}
	else if (i - s.nb_planes < s.nb_spheres)
	{
		t = ft_intersect_sphere(cam, ray, s.sphere[i - s.nb_planes]);
		t.id = i - s.nb_planes;
	}
	else if (i - s.nb_planes - s.nb_spheres < s.nb_cylinders)
	{
		t = ft_intersect_cylinder(cam, ray, s.cylinder[i - s.nb_planes - s.nb_spheres]);
		t.id = i - s.nb_planes - s.nb_spheres;
	}
	else
	{
		t = ft_intersect_cone(cam, ray, s.cone[i - s.nb_planes - s.nb_spheres - s.nb_cylinders]);
		t.id = i - s.nb_planes - s.nb_spheres - s.nb_cylinders;
	}
	return (t);
}

t_closest	ft_closest_intersection(t_vector cam, t_vector ray, t_scene scene)
{
	int			i;
	t_closest	closest;
	t_solve		t;

	i = 0;
	closest.t = T_MAX;
	closest.type = 0;
	while (i < scene.nb_figures)
	{
		t = get_solve(i, scene, cam, ray);
		if (t.t1 < closest.t && (t.t1 < scene.t_max && t.t1 > scene.t_min))
		{
			closest.t = t.t1;
			closest.id = t.id;
			closest.type = t.type;
		}
		if (t.t2 < closest.t && (t.t2 < scene.t_max && t.t2 > scene.t_min))
		{
			closest.t = t.t2;
			closest.id = t.id;
			closest.type = t.type;
		}
		i++;
	}
	return (closest);
}
