/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/02 16:10:37 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * 
 * t_inter_point ft_cylinder_collision(t_ray ray, t_pack cylinder, int id)
{
    t_inter_point inter_point;
    t_delta delta;
    t_ray new_ray;
    t_vect c_to_o;

    inter_point.hit = FALSE;
    inter_point.id = id;
    new_ray.origin = ray.origin;
    cylinder.rot = normalize(cylinder.rot);
    new_ray.direction = cross(ray.direction, cylinder.rot);
	
    c_to_o = sub(ray.origin, cylinder.pos);
    delta.a = dot(new_ray.direction, new_ray.direction);
    delta.b = 2 * dot(new_ray.direction, cross(c_to_o, cylinder.rot));
    delta.c = dot(cross(c_to_o, cylinder.rot), cross(c_to_o, cylinder.rot)) - pow(cylinder.diameter / 2, 2);
    delta.delta = pow(delta.b, 2) - 4 * delta.c * delta.a;
   
    if (delta.delta < 0)
        return (inter_point);
    inter_point.t1 = (-delta.b - sqrt(delta.delta)) / (2 * delta.a);
    inter_point.t2 = (-delta.b + sqrt(delta.delta)) / (2 * delta.a);
    if (inter_point.t2 < 0)
        return (inter_point);
    inter_point.t = (inter_point.t1 > 0 ? inter_point.t1 : inter_point.t2);
    return (ft_find_edges(cylinder, ray, inter_point));
}
*/

// coords, 3D ector, diameter, height, rgb
bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
{
	t_vec3	oc;

	// c_to_o = sub(ray.origin, cylinder.pos);
	oc = minus(ray->place, cylinder->center);
	
    // delta.a = dot(new_ray.direction, new_ray.direction);
	obj_data->a = dot_product(ray->vector, ray->vector);
	
    // delta.b = 2 * dot(new_ray.direction, cross(c_to_o, cylinder.rot));
	obj_data->b = 2.0 * dot_product(oc, ray->vector);
	
    // delta.c = dot(cross(c_to_o, cylinder.rot), cross(c_to_o, cylinder.rot)) - pow(cylinder.diameter / 2, 2);
	obj_data->c = dot_product(oc, oc) - pow(cylinder->diameter / 2, 2);

    // delta.delta = pow(delta.b, 2) - 4 * delta.c * delta.a;
	obj_data->d = pow(obj_data->b, 2) - 4 * obj_data->c * obj_data->a;
	// obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c; // from sphere

	if (obj_data->d < 0)
		return (false); // no intersection
	else
	{
		obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2.0 * obj_data->a);
		obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2.0 * obj_data->a);
		if (obj_data->root1 < 0)
			obj_data->t = obj_data->root1;
		else
			obj_data->t = obj_data->root2;
		return (true); // intersection found
	}
}
