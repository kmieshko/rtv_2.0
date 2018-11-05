/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:46:33 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:46:34 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_solve		ft_intersect_cylinder(t_vector cam, t_vector ray, t_cylinder cy)
{
	t_koef		koef;
	t_solve		t;
	t_vector	oc;

	oc = sub(cam, cy.center);
	koef.k1 = dot(ray, ray) - pow(dot(ray, cy.vector), 2);
	koef.k2 = 2 * (dot(ray, oc) - dot(ray, cy.vector) * dot(oc, cy.vector));
	koef.k3 = dot(oc, oc) - pow(dot(oc, cy.vector), 2) - cy.radius * cy.radius;
	koef.discrim = koef.k2 * koef.k2 - 4 * koef.k1 * koef.k3;
	t.type = 3;
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
