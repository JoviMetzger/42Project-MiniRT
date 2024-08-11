/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/11 18:11:03 by jmetzger      ########   odam.nl         */
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

	denom = dot_product(ray->vector, plane->vector);
	if (fabs(denom) > EPSILON)
	{
		hit->o_c = minus(plane->center, ray->place);
		hit->t = dot_product(hit->o_c, plane->vector) / denom;
		if (hit->t >= EPSILON)
		{
			if (denom < 0)
				plane->normal = mult_vecdub(plane->vector, -1);
				
			// plane->hit_pos = plus(ray->place, mult_vecdub(ray->vector, plane->obj_t));
			plane->hit_pos = mult_vecdub(ray->vector, plane->obj_t);
			plane->obj_t = hit->t;
			return (true);
		}
	}
	return (false);
}

bool	plane(t_ray *ray, t_objs *plane, t_hit_data *hit)
{
	if (intersect_plane(ray, plane, hit))
		return (check_closest(hit));
	return (false);
}
