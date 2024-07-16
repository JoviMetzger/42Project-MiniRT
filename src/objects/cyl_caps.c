/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cyl_caps.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 19:12:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/16 17:58:42 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Intersect with bottom cap
static void	tap_top(t_hit_data *hit, t_objs *cyl, t_ray *ray, double denom)
{
	double	t1;
	t_vec3	hit_point1;

	t1 = dot_product(minus(cyl->center, ray->place), cyl->vector) / denom;
	hit_point1 = plus(ray->place, mult_vecdub(ray->vector, t1));
	if (t1 > 0 && dot_product(minus(hit_point1, cyl->center), minus(hit_point1, cyl->center)) <= cyl->radius * cyl->radius)
	{
		if (t1 < hit->tmp_t)
		{
			hit->tmp_t = t1;
			hit->t = t1;
			cyl->normal = mult_vecdub(cyl->vector, -1);
		}
	}
}

// Intersect with top cap
static void	boop_bottom(t_hit_data *hit, t_objs *cyl, t_ray *ray, double denom)
{
	t_vec3	top_center;
	double	t2;
	t_vec3	hit_point2;

	top_center = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
	t2 = dot_product(minus(top_center, ray->place), cyl->vector) / denom;
	hit_point2 = plus(ray->place, mult_vecdub(ray->vector, t2));
	if (t2 > 0 && dot_product(minus(hit_point2, top_center), minus(hit_point2, top_center)) <= cyl->radius * cyl->radius)
	{
		if (t2 < hit->tmp_t)
		{
			hit->tmp_t = t2;
			hit->t = t2;
			cyl->normal = cyl->vector;
		}
	}
}

// calculating the caps
bool	intersect_caps(t_ray *ray, t_objs *cyl, t_hit_data *hit)
{
	double	denom;

	denom = dot_product(ray->vector, cyl->vector);
	if (fabs(denom) > EPSILON)
	{ 
		tap_top(hit, cyl, ray, denom);
		boop_bottom(hit, cyl, ray, denom);
	}
	return (hit->tmp_t != DBL_MAX);
}
