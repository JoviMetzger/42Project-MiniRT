/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/04 19:41:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * 
		Plane
		// plane degined by p (p.xyz must be normalized)
		float plaIntersect( in vec3 ro, in vec3 rd, in vec4 p )
		{
			return -(dot(ro,p.xyz)+p.w)/dot(rd,p.xyz);
		}
 */

bool intersect_plane(t_ray *ray, t_objs *plane, t_obj_data *obj_data)
{
	t_vec3	oc;
	double	denom;
	
	denom = dot_product(ray->vector, plane->vector);
	if (fabs(denom) > EPSILON)
	{
		oc = minus(ray->place, plane->center);
		obj_data->t = dot_product(oc, ray->vector) / denom;
		if (obj_data->t >= EPSILON)
			return (true);
	}
	return (false);
}
