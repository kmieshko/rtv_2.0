/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:51:20 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:51:21 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	get_color(int color, int reflect_color, double intensity, int state)
{
	int		red;
	int		green;
	int		blue;

	if (state == 1)
	{
		red = ft_clamp(round((color & 0xFF0000) >> 16) * intensity);
		green = ft_clamp(round((color & 0xFF00) >> 8) * intensity);
		blue = ft_clamp(round((color & 0xFF)) * intensity);
	}
	else
	{
		red = ft_clamp(((color & 0xFF0000) >> 16) + ((reflect_color & 0xFF0000) >> 16));
		green = ft_clamp(((color & 0xFF00) >> 8) + ((reflect_color & 0xFF00) >> 8));
		blue = ft_clamp((color & 0xFF) + (reflect_color & 0xFF));
	}
	color = (red << 16) + (green << 8) + blue;
	return (color);
}

// t_vector	refract_ray(t_vector normal, t_vector ray, double n)
// {
// 	t_vector	refract;

// 	double cosI = -dot(normal, ray);
// 	double sinT2 = n * n * (1 - cosI * cosI);
// 	if (sinT2 > 1)
// 		ft_error("Invalid refract vector");
// 	double cosT = sqrt(1 - sinT2);
// 	refract = add(mult(n, ray), mult((n * cosI - cosT), normal));
// 	// refract = sub(mult(n, ray), mult(n + sqrt(1 - sinT2), normal));
// 	return (refract);
// }

t_vector	refract_ray(t_vector normal, t_vector ray, double n)
{
	t_vector	refract;

	double cos_theta = -dot(normal, ray);
	if (cos_theta < 0)
	{
		cos_theta *= -1;
		normal = mult(-1, normal);
		n = 1 / n;
	}
	double k = 1 - n * n * (1 - cos_theta * cos_theta);
	if (k >= 0)
	{
		refract = add(mult(n, ray), mult((n * cos_theta - sqrt(k)), normal));
		refract = get_normal(refract);
	}
	return (refract);
}

double schlick(t_vector normal, t_vector ray, double n1)
{
	double n2;

	n2 = 1;
	double r0 = (n1 - n2) / (n1 + n2);
	r0 *= r0;
	double cosX = -dot(normal, ray);
	if (n1 > n2)
	{
		const double n = n1 / n2;
		const double sinT2 = n * n * (1 - cosX * cosX);
		if (sinT2 > 1)
			return (1);
		cosX = sqrt(1 - sinT2);
	}
	const double x = 1 - cosX;
	return (r0 + (1 - r0) * pow(x, 5));
}


# define REFRACTIVE_INDEX_INSIDE 1
# define REFRACTIVE_INDEX_OUTSIDE 1

int			trace_ray(t_vector cam, t_vector ray, t_scene scene, int reflection_depth, int refraction_depth)
{
	t_closest	closest;
	t_vector	reflect;
	t_vector	refract;
	t_figure	f;
	int			color;
	int			reflected_color;
	int			refracted_color;
	int			transparency_color;

	closest = ft_closest_intersection(cam, ray, scene);
	if (closest.type == 0)
		return (0x0);
	f = ft_closest_figure(scene, cam, ray, closest);
	color = get_color(f.color, 0, ft_light(f, mult(-1, ray), scene), 1);
	if (f.reflect > 0)
	{
		f.reflect = schlick(f.normal, ray, 1 - f.reflect * 0.99);
		f.transparency = 0;
	}
	if (f.transparency > 0)
		f.refract = 1;
	if (reflection_depth > 0 && f.reflect > 0)
	{
		reflect = reflect_ray(f.normal, mult(-1, ray));
		scene.t_min = 0.0001;
		reflected_color = trace_ray(f.point, reflect, scene, reflection_depth--, refraction_depth);
	}
	if (refraction_depth > 0 && (f.refract > 0 || f.transparency > 0))
	{
		refract = refract_ray(f.normal, ray, f.refract);
		scene.t_min = 0.0001;
		refracted_color = trace_ray(f.point, refract, scene, 0, refraction_depth--);
	}
	if (f.reflect > 0 || f.refract > 0 || f.transparency > 0)
	{
		if (f.refract)
			color = refracted_color;
		if (f.transparency > 0)
			color = get_color(get_color(f.color, 0, (1 - f.transparency * 0.99) * ft_light(f, mult(-1, ray), scene), 1), get_color(refracted_color, 0, f.transparency, 1), 1, 2);
		if (f.reflect > 0)
			color = get_color(get_color(f.color, 0, (1 - f.reflect) * ft_light(f, mult(-1, ray), scene), 1), get_color(reflected_color, 0, f.reflect, 1), 1, 2);	
	}
	return (color);
}
