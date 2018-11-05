/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reflect_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:21:42 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/25 17:21:43 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	reflect_ray(t_vector normal, t_vector ray)
{
	t_vector	reflect;

	reflect = sub(mult(2 * dot(normal, ray), normal), ray);
	return (reflect);
}
