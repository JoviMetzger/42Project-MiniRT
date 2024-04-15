/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/15 20:28:59 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool intersect_sphere(t_ray *ray, t_objs *sphere, t_obj_data *obj_data)
{
    double radius;
    t_vec3	oc;

	radius = sphere->diameter / 2;
    oc = minus(ray->place, sphere->center);
    obj_data->a = dot_product(ray->vector, ray->vector);
    obj_data->b = 2.0 * dot_product(oc, ray->vector);
    obj_data->c = dot_product(oc, oc) - radius * radius;
    obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;
	if (quadratic(obj_data) == true)
		return (check_closest(obj_data));
	return (false);
}
