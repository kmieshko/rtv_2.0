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
	else
	{
		refract.x = 0;
		refract.y = 0;
		refract.z = 0;
	}
	return (refract);
}

// static double	if_max(double a, double b)
// {
// 	if (a > b)
// 		return (a);
// 	return (b);
// }

// double		fresnel(t_vector ray, t_vector normal, double ior, double reflect)
// {
// 	double cosi = ft_clamp_with_param(dot(ray, normal), -1, 1);
// 	double etai = 1;
// 	double etat = ior;
// 	if (cosi > 0)
// 	{
// 		double tmp;

// 		tmp = etai;
// 		etai = etat;
// 		etat = tmp;
// 	}
// 	double sint = etai / etat * sqrt(if_max(0, 1 - cosi * cosi));
// 	if (sint >= 1)
// 		reflect = 1;
// 	else
// 	{
// 		double cost = sqrt(if_max(0, 1 - sint * sint));
// 		cosi = fabs(cosi);
// 		double Rs = (-(etat * cosi) + (etai * cost)) / ((etat * cosi) + (etai * cost));
// 		double Rp = (-(etai * cosi) + (etat * cost)) / ((etai * cosi) + (etat * cost));
// 		reflect = (Rs * Rs + Rp * Rp) / 2; 
//     }
//     return (reflect);
// }

// double		reflectance(t_vector ray, t_vector normal, double n, double reflect)
// {
// 	double cosI = -dot(normal, ray);
// 	double sinT2 = n * n * (1 - 1 - cosI * cosI);
// 	if (sinT2 > 1)
// 		return (1);
// 	double cosT = sqrt(1 - sinT2);
// 	double r0th = (REFRACTIVE_INDEX_INSIDE * cosI - REFRACTIVE_INDEX_OUTSIDE * cosT) / (REFRACTIVE_INDEX_INSIDE * cosI + REFRACTIVE_INDEX_OUTSIDE * cosI);
// 	double rPar = (REFRACTIVE_INDEX_OUTSIDE * cosI - REFRACTIVE_INDEX_INSIDE * cosT) / (REFRACTIVE_INDEX_OUTSIDE * cosI + REFRACTIVE_INDEX_INSIDE * cosT);
// 	reflect = r0th * r0th + rPar * rPar / 2;
// 	return (reflect);
// }

// # define REFRACTIVE_INDEX_INSIDE 1
// # define REFRACTIVE_INDEX_OUTSIDE 1.33

// double schlick(t_vector normal, t_vector ray, t_figure f)
// {
// 	double n2;
// 	double n1;

// 	n2 = REFRACTIVE_INDEX_INSIDE;
// 	n2 = REFRACTIVE_INDEX_OUTSIDE;
// 	// double r0 = (n1 - n2) / (n1 + n2);
// 	double r0 = f.reflect;
// 	r0 *= r0;
// 	double cosX = -dot(normal, ray);
// 	if (n1 > n2)
// 	{
// 		const double n = n1 / n2;
// 		const double sinT2 = n * n * (1 - cosX * cosX);
// 		if (sinT2 > 1)
// 			return (1);
// 		cosX = sqrt(1 - sinT2);
// 	}
// 	const double x = 1 - cosX;
// 	double ret = (r0 + (1 - r0) * pow(x, 5));
// 	return (ret);
// }

int			trace_ray(t_vector cam, t_vector ray, t_scene scene, int reflection_depth, int refraction_depth)
{
	t_closest	closest;
	t_vector	reflect;
	t_vector	refract;
	t_figure	f;
	int			color;
	int			reflected_color;
	int			refracted_color;
	double		inten;


	closest = ft_closest_intersection(cam, ray, scene);
	if (closest.type == 0)
		return (0x0);
	f = ft_closest_figure(scene, cam, ray, closest);
	inten = ft_light(f, mult(-1, ray), scene);
	color = get_color(f.color, 0, inten, 1);
	if (reflection_depth > 0 && f.reflect > 0)
	{
		reflect = reflect_ray(f.normal, mult(-1, ray));
		scene.t_min = 0.0001;
		reflected_color = trace_ray(f.point, reflect, scene, reflection_depth--, 0);
	}
	if (refraction_depth > 0 && (f.refract || f.transparency))
	{
		refract = refract_ray(f.normal, ray, f.refract);
		scene.t_min = 0.0001;
		refracted_color = trace_ray(f.point, refract, scene, 0, refraction_depth--);
	}
	if (f.reflect > 0 || f.transparency > 0)
	{
		int only_reflected = 0;
		int only_refracted = 0;
		int refract_transparency = 0;
		int refr_refl = 0;

		if (f.reflect)
			inten *= (1 - f.reflect);
		if (f.transparency > 0)
			inten *= (1 - f.transparency);
		only_reflected = get_color(reflected_color, 0, f.reflect, 1);
		only_refracted = get_color(refracted_color, 0, 1 - f.reflect, 1);
		refract_transparency = get_color(only_refracted, 0, f.transparency, 1);
		refr_refl = get_color(only_reflected, refract_transparency, 0, 2);
		color = get_color(get_color(f.color, 0, inten, 1), refr_refl, 0, 2);
	}
	return (color);
}
