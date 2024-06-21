/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/15 22:06:37 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	intersect_cyl_plane(t_ray *ray, t_objs *cyl_plane, t_hit_data *hit)
{
	double	denom;

	denom = dot_product(ray->vector, cyl_plane->vector);
	if (fabs(denom) > EPSILON)
	{
		hit->o_c = minus(cyl_plane->center, ray->place);
		hit->t = dot_product(hit->o_c, cyl_plane->vector) / denom;
		if (hit->t >= EPSILON)
		{
			if (denom < 0)
				cyl_plane->normal = mult_vecdub(cyl_plane->vector, -1);
			cyl_plane->obj_t = hit->t;
			return (true);
		}
	}
	return (false);
}

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

	denom = dot_product(ray->vector, plane->vector);
	if (fabs(denom) > EPSILON)
	{
		hit->o_c = minus(plane->center, ray->place);
		hit->t = dot_product(hit->o_c, plane->vector) / denom;
		t_vec3 inter = plus(ray->place, mult_vecdub(ray->vector, hit->t));
		plane->normal = normalize(minus(inter, plane->center));
		if (hit->t >= EPSILON)
		{
			// printf("vec = %f %f %f\n", plane->vector.x, plane->vector.y, plane->vector.z);
			// plane->normal = normalize(plane->vector);
			// printf("norm = %f %f %f\n", plane->normal.x, plane->normal.y, plane->normal.z);
			if (denom < 0)
				plane->normal = mult_vecdub(plane->normal, -1);
			plane->obj_t = hit->t;
			plane->hit_pos = plus(ray->place, mult_vecdub(ray->vector, plane->obj_t));
			return (check_closest(hit));
		}
	}
	return (false);
}
