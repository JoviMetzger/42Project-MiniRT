/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/13 22:59:20 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * @todo	is the light correct? looks like the calculation is good..
 * 
 * should the plane flip? should it always be seen? how can i get rid of it if its behind camera?
 * or if we still see it then i dont want it to flip...
 * 
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

 */
		// obj_data->root1 = -(dot_product(oc, oc)) / denom;
		// obj_data->root2 = dot_product(oc, oc) / denom;
		// if (obj_data->root1 < obj_data->root2)
		// 	obj_data->t = obj_data->root1;
		// else
		// 	obj_data->t = obj_data->root2;
		// if (obj_data->t < 0)
		// 	return (false);
		// else
		// 	return true;

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