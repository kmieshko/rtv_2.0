/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:46:54 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:46:56 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_solve		ft_intersect_cone(t_vector cam, t_vector ray, t_cone co)
{
	t_koef		koef;
	t_solve		t;
	t_vector	oc;

	oc = sub(cam, co.center);
	koef.k1 = dot(ray, ray) - pow(dot(ray, co.vector), 2) * (1 + co.k * co.k);
	koef.k2 = 2 * (dot(ray, oc) - (1 + co.k * co.k) * dot(ray, co.vector) * dot(oc, co.vector));
	koef.k3 = dot(oc, oc) - (1 + co.k * co.k) * pow(dot(oc, co.vector), 2);
	koef.discrim = koef.k2 * koef.k2 - 4 * koef.k1 * koef.k3;
	t.type = 4;
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