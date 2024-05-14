/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/14 17:16:58 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * 	d = ray direction
 *  x = ray origin - center point of a shape
 * 
 *			a   = D|D
 			b/2 = D|X
  			c   = X|X - r*r		
 * 
 * 		len(D*t+X) = r
  		dot(D*t+X) = r^2
  		D|D*(t^2) + 2*D|X*t + X|X - r^2 = 0 
 */
bool	intersect_sphere(t_ray *ray, t_objs *sphere, t_obj_data *obj_data)
{
	double	radius;
	t_vec3	oc;

	radius = sphere->diameter / 2;
	oc = minus(ray->place, sphere->center);
	obj_data->a = dot_product(ray->vector, ray->vector);
	obj_data->b = 2.0 * dot_product(ray->vector, oc);
	obj_data->c = dot_product(oc, oc) - radius * radius;
	if (quadratic(obj_data) == true)
		return (check_closest(obj_data));
	return (false);
}
