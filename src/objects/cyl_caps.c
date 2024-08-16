/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cyl_caps.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 19:12:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/16 17:04:03 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/* Intersect with bottom cap -> Test bottom cap first
 * cyl->normal = mult_vecdub(cyl->vector, -1); // Normal points downwards
 */
static void	boop_bottom(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	double	t1;
	t_vec3	hit_point1;
	t_vec3	cap1;

	t1 = dot_product(minus(cyl->center, ray->place), cyl->vector) / dot_product(cyl->vector, ray->vector);
	hit_point1 = plus(ray->place, mult_vecdub(ray->vector, t1));
	cap1 = minus(hit_point1, cyl->center);
	if (dot_product(cap1, cap1) <= (cyl->radius * cyl->radius))
	{
		hit->t = t1;
		hit->tmp_t = t1;
		cyl->normal = mult_vecdub(cyl->vector, -1);
	}
}

/* Intersect with top cap -> Test top cap next
 * cyl->normal = cyl->vector; // Normal points upwards
 */
static void	tap_top(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	t_vec3	top_center;
	double	t2;
	t_vec3	hit_point2;
	t_vec3	cap2;

	top_center = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height / 2.0));
	t2 = dot_product(minus(top_center, ray->place), cyl->vector) / dot_product(cyl->vector, ray->vector);
	hit_point2 = plus(ray->place, mult_vecdub(ray->vector, t2));
	cap2 = minus(hit_point2, top_center);
	if (dot_product(cap2, cap2) <= (cyl->radius * cyl->radius))
	{
		hit->t = t2;
		hit->tmp_t = t2;
		cyl->normal = cyl->vector;
	}
}

// calculating the caps
bool	intersect_caps(t_ray *ray, t_objs *cyl, t_hit_data *hit)
{
	double	denom;
	t_vec3	hit_to_c;
	t_vec3	hit_point;

	hit_point = plus(ray->place, mult_vecdub(ray->vector, hit->root1));
	hit_to_c = minus(hit_point, cyl->center);
	denom = dot_product(hit_to_c, cyl->vector);
	if (denom <= -cyl->height / 2.0 || denom >= cyl->height / 2.0)
	{
		hit->tmp_t = DBL_MAX;
		boop_bottom(hit, cyl, ray);
		tap_top(hit, cyl, ray);
	}
	return (hit->tmp_t != DBL_MAX);
}
