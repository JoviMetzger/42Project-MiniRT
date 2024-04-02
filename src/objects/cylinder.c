/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/02 20:42:48 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// height, rotation... cylinder vector... 

bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
{
	t_vec3	oc;
	double	radius;

	radius = cylinder->diameter / 2;
	oc = minus(ray->place, cylinder->center);

	obj_data->a = (dot_product(ray->vector, ray->vector)) - (pow(dot_product(ray->vector, cylinder->center), 2));
	obj_data->b = 2.0 * dot_product(oc, ray->vector) - (dot_product(ray->vector, cylinder->center) * dot_product(oc, cylinder->center));
	obj_data->c = dot_product(oc, oc) - pow(dot_product(oc, cylinder->center), 2) - pow(radius, 2);

	// dont know if this is necessary
	// if (obj_data->a == 0 && obj_data->b != 0)
	// {
	// 	obj_data->root1 = -obj_data->c / obj_data->b;
	// 	return (true);
	// }
	
	obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;
	if (obj_data->d < 0)
		return (false); // no intersection
	else
	{
		obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2 * obj_data->a);
		obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2 * obj_data->a);
		if (obj_data->root1 > obj_data->root2)
			obj_data->t = obj_data->root1;
		else
			obj_data->t = obj_data->root2;
		return (true); // Intersection found
	}
}

