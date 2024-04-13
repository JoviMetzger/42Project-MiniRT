/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/13 20:56:18 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * @todo	is the light correct? looks like the calculation is good..
 * 
 * float denom = normal.dot(ray.direction);

if (denom > 0)
{
    float t = -((center - ray.origin).dot(normal)) / denom;

    if (t >= 0)
    {
        rec.tHit = t;
        rec.anyHit = true;
        computeSurfaceHitFields(ray, rec);
        return true;
    }
}
 */
static bool	intersect_plane(t_ray *ray, t_objs *plane, t_obj_data *obj_data)
{
	t_vec3	oc;
	double	denom;

	denom = dot_product(ray->vector, plane->vector);
	if (fabs(denom) > 0)
	{
		oc = minus(ray->place, plane->center);
		obj_data->root1 = -(dot_product(oc, oc)) / denom;
		obj_data->root2 = dot_product(oc, oc) / denom;
		if (obj_data->root1 < obj_data->root2)
			obj_data->t = obj_data->root1;
		else
			obj_data->t = obj_data->root2;
		if (obj_data->t < 0)
			return (false);
		else
			return true;
	}
	return (false);
}



// static bool	intersect_plane(t_ray *ray, t_objs *plane, t_obj_data *obj_data)
// {
// 	t_vec3	oc;
// 	double	denom;

// 	denom = dot_product(ray->vector, plane->vector);
// 	if (fabs(denom) > 0)
// 	{
// 		oc = minus(ray->place, plane->center);
// 		obj_data->t = -(dot_product(oc, ray->place)) / denom;
// 		if (obj_data->t >= 0)
// 			return (true);
// 		else
// 			return false;
// 	}
// 	return (false);
// }

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