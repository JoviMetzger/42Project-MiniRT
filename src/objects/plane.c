/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/11 16:34:52 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * @todo		check this... also, light/colour isn't correct yet
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
