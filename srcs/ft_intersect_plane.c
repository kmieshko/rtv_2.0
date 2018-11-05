/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:47:12 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:47:13 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_solve		ft_intersect_plane(t_vector cam, t_vector ray, t_plane p)
{
	t_solve	t;

	t.type = 2;
	if (dot(ray, p.vector))
	{
		t.t1 = -dot(sub(cam, p.center), p.vector) / dot(ray, p.vector);
		t.t2 = t.t1;
		return (t);
	}
	else
	{
		t.t1 = T_MAX;
		t.t2 = T_MAX;
		return (t);
	}
}
