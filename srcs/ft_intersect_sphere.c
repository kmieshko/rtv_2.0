/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:47:03 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:47:04 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_solve		ft_intersect_sphere(t_vector cam, t_vector ray, t_sphere s)
{
	t_koef		koef;
	t_solve		t;
	t_vector	oc;

	oc = sub(cam, s.center);
	koef.k1 = dot(ray, ray);
	koef.k2 = 2 * dot(sub(cam, s.center), ray);
	koef.k3 = dot(oc, oc) - s.radius * s.radius;
	koef.discrim = koef.k2 * koef.k2 - 4 * koef.k1 * koef.k3;
	t.type = 1;
	if (koef.discrim < 0)
	{
		t.t1 = T_MAX;
		t.t2 = T_MAX;
		return (t);
	}
	t.t1 = (-koef.k2 + sqrt(koef.discrim)) / (2 * koef.k1);
	t.t2 = (-koef.k2 - sqrt(koef.discrim)) / (2 * koef.k1);
	return (t);
}
