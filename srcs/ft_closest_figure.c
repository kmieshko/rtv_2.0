/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_closest_figure.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 19:18:50 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/22 19:18:52 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_figure	sphere(t_scene scene, t_vector cam, t_vector ray, t_closest closest)
{
	t_figure	fig;
	t_sphere	s;

	s = scene.sphere[closest.id];
	fig.point = add(cam, mult(closest.t, ray));
	fig.normal = sub(fig.point, s.center);
	fig.normal = get_normal(fig.normal);
	fig.color = s.color;
	fig.specular = s.specular;
	fig.reflect = s.reflect;
	fig.refract = s.refract;
	fig.transparency = s.transparency;
	return (fig);

}

static t_figure	plane(t_scene scene, t_vector cam, t_vector ray, t_closest closest)
{
	t_figure	fig;
	t_plane		p;

	p = scene.plane[closest.id];
	fig.point = add(cam, mult(closest.t, ray));
	fig.normal = p.vector;
	if (dot(ray, fig.normal) > 0)
		fig.normal = mult(-1, fig.normal);
	fig.specular = p.specular;
	fig.color = p.color;
	fig.reflect = p.reflect;
	fig.refract = p.refract;
	fig.transparency = p.transparency;
	return (fig);
}

static t_figure	cylinder(t_scene scene, t_vector cam, t_vector ray, t_closest closest)
{
	t_figure	fig;
	t_cylinder	cy;
	double		m;
	t_vector	oc;

	cy = scene.cylinder[closest.id];
	fig.point = add(cam, mult(closest.t, ray));
	oc = sub(cam, cy.center);
	m = dot(ray, cy.vector) * closest.t + dot(oc, cy.vector);
	fig.normal = sub(sub(fig.point, cy.center), mult(m, cy.vector));
	fig.normal = get_normal(fig.normal);
	fig.specular = cy.specular;
	fig.color = cy.color;
	fig.reflect = cy.reflect;
	fig.refract = cy.refract;
	fig.transparency = cy.transparency;
	return (fig);
}

static t_figure	cone(t_scene scene, t_vector cam, t_vector ray, t_closest closest)
{
	t_figure	fig;
	t_cone		co;
	double		m;
	t_vector	oc;

	co = scene.cone[closest.id];
	fig.point = add(cam, mult(closest.t, ray));
	oc = sub(cam, co.center);
	m = dot(ray, co.vector) * closest.t + dot(oc, co.vector);
	fig.normal = sub(sub(fig.point, co.center), mult((1 + co.k * co.k) * m, co.vector));
	fig.normal = get_normal(fig.normal);
	fig.specular = co.specular;
	fig.color = co.color;
	fig.reflect = co.reflect;
	fig.refract = co.refract;
	fig.transparency = co.transparency;
	return (fig);
}

t_figure		ft_closest_figure(t_scene scene, t_vector cam, t_vector ray, t_closest closest)
{
	t_figure	fig;


	if (closest.type == 1)
		fig = sphere(scene, cam, ray, closest);
	else if (closest.type == 2)
		fig = plane(scene, cam, ray, closest);
	else if (closest.type == 3)
		fig = cylinder(scene, cam, ray, closest);
	else if (closest.type == 4)
		fig = cone(scene, cam, ray, closest);
	return (fig);
}
