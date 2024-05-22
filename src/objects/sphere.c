/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/22 18:52:13 by smclacke      ########   odam.nl         */
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
bool	intersect_sphere(t_ray *ray, t_objs *sphere, t_hit_data *hit_data)
{
	t_vec3	oc;
	double radius;

	radius = sphere->diameter / 2;

	oc = minus(ray->place, sphere->center);
	hit_data->a = dot_product(ray->vector, ray->vector);
	hit_data->b = 2.0 * dot_product(ray->vector, oc);
	hit_data->c = dot_product(oc, oc) - radius * radius;
	if (quadratic(hit_data) == true)
	{
		t_vec3 inter_point = plus(ray->place, mult_vecdub(ray->vector, hit_data->t));
		sphere->normal = normalize_vector(minus(inter_point, sphere->center));
		return (check_closest(hit_data));
	}
	return (false);
}
