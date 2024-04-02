/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/02 18:36:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * 
 * double	inter_plane(t_CamRay *ray, t_objs *pl)
{
	t_vec	x;
	t_vec	normal;
	double	t;
	double	b;
	double	a;

	normal = get_normalized(pl->dir);
	x = sub_vec(ray->origin, pl->cen);
	b = dot_product(ray->dir, normal);
	if (b != 0)
	{
		a = dot_product(x, normal);
		t = -a / b;
		if (t < EPS)
			return (-1.0);
		return (t);
	}
	return (-1.0);
}
*/

// coords, 3D vector, rgb
bool intersect_plane(t_ray *ray, t_objs *plane, t_obj_data *obj_data)
{
	t_vec3	oc;

	oc = minus(ray->place, plane->center);
	// plane->center = minus(ray->vector, plane->vector);
	obj_data->a = dot_product(ray->vector, ray->vector);
	if (obj_data->a != 0)
	{
		obj_data->b = dot_product(plane->center, oc);
		// obj_data->b = 2.0 * dot_product(oc, ray->vector);
		obj_data->t = -obj_data->a / obj_data->b;
		if (obj_data->t > 0.000001)
			return (true);
	}
	return (false);



	
    // t_vec3	oc;

    // oc = minus(ray->place, plane->center);
    // obj_data->a = dot_product(ray->vector, ray->vector);
    // obj_data->b = 2.0 * dot_product(oc, ray->vector);
    // obj_data->c = dot_product(oc, oc) - radius * radius;
    // obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;

    // if (obj_data->d < 0)
    //     return (false);	// No intersection
    // else 
    // {
    //     obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2.0 * obj_data->a);
    //     obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2.0 * obj_data->a);
    //     if (obj_data->root1 < obj_data->root2)
    //         obj_data->t = obj_data->root1;
    //     else
    //         obj_data->t = obj_data->root2;
    //     return (true); // Intersection found
    // }
}
