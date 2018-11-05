/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:50:02 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:50:03 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		dot(t_vector vect1, t_vector vect2)
{
	double	res;

	res = vect1.x * vect2.x + vect1.y * vect2.y + vect1.z * vect2.z;
	return (res);
}

t_vector	mult(double num, t_vector vector)
{
	t_vector	res;

	res.x = num * vector.x;
	res.y = num * vector.y;
	res.z = num * vector.z;
	return (res);
}

t_vector	sub(t_vector vector1, t_vector vector2)
{
	t_vector	res;

	res.x = vector1.x - vector2.x;
	res.y = vector1.y - vector2.y;
	res.z = vector1.z - vector2.z;
	return (res);
}

t_vector	add(t_vector vector1, t_vector vector2)
{
	t_vector	res;

	res.x = vector1.x + vector2.x;
	res.y = vector1.y + vector2.y;
	res.z = vector1.z + vector2.z;
	return (res);
}

double		length(t_vector vector)
{
	double		length;

	length = sqrt(dot(vector, vector));
	return (length);
}

t_vector	get_normal(t_vector vector)
{
	t_vector	res;
	double		len;

	len = length(vector);
	res.x = vector.x / len;
	res.y = vector.y / len;
	res.z = vector.z / len;
	return (res);
}
