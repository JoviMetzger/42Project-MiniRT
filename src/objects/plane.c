/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/15 15:35:36 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

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

bool	calc_plane(t_ray *ray, t_objs *plane, t_obj_data *obj_data)
{
	if (intersect_plane(ray, plane, obj_data))
	{
		if (obj_data->t < obj_data->closest_t)
		{
			obj_data->closest_t = obj_data->t;
			return (true);
		}
	}
	return (false);
}

