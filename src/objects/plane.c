/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/30 17:12:59 by jmetzger      ########   odam.nl         */
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
bool intersect_plane(t_ray *ray, t_objs *plane, t_obj_hit *obj_hit)
{
	t_vec3	oc;
	double	denom;
	
	denom = dot_product(ray->vector, plane->vector);
	if (fabs(denom) > EPSILON)
	{
		oc = minus(ray->place, plane->center);
		obj_hit->t = -dot_product(oc, plane->vector) / denom;
		if (obj_hit->t >= EPSILON)
			return (check_closest(obj_hit));
	}
	return (false);
}
