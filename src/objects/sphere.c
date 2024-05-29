/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/29 17:16:28 by smclacke      ########   odam.nl         */
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
bool	intersect_sphere(t_ray *ray, t_objs *sphere, t_hit_data *hit)
{
	// t_vec3	oc; // make sure by using the struct one, i did break shit
	double radius;

	radius = sphere->diameter / 2;

	hit->o_c = minus(ray->place, sphere->center);
	hit->a = dot_product(ray->vector, ray->vector);
	hit->b = 2.0 * dot_product(ray->vector, hit->o_c);
	hit->c = dot_product(hit->o_c, hit->o_c) - radius * radius;
	if (quadratic(hit) == true)
	{
		t_vec3 inter_point = plus(ray->place, mult_vecdub(ray->vector, hit->t));
		sphere->normal = normalize_vector(minus(inter_point, sphere->center));
		return (check_closest(hit));
	}
	return (false);
}
