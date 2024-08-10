/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/10 15:24:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * if t is negative, no intersection found
 * 
 * 			t = -X|V / D|V
 * 
 * 			x = ray origin - center point of a shape
 *			v = plane normal
 * 			d = ray direction
 */
bool	intersect_plane(t_ray *ray, t_objs *plane, t_hit_data *hit)
{
	double	denom;

	denom = dot_product(plane->vector, ray->vector);
	if (denom == 0)
		return (false);
	hit->o_c = minus(ray->place, plane->center);
	hit->t = dot_product(hit->o_c, plane->vector) / denom;
	if (hit->t < EPSILON)
		return (false);
	plane->normal = plane->vector;
	if (dot_product(plane->normal, ray->vector) > 0)
		plane->normal = mult_vecdub(plane->vector, -1);
	plane->obj_t = hit->t;
	plane->hit_pos = mult_vecdub(ray->vector, plane->obj_t);
	ray_mult(&plane->hit_pos, ray, hit->t);

	return (true);
}

bool	plane(t_ray *ray, t_objs *plane, t_hit_data *hit)
{
	if (intersect_plane(ray, plane, hit))
		return (check_closest(hit));
	return (false);
}
