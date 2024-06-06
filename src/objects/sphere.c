/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/30 17:12:59 by jmetzger      ########   odam.nl         */
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
bool intersect_sphere(t_ray *ray, t_objs *sphere, t_obj_hit *obj_hit)
{
    double radius;
    t_vec3	oc;

	radius = sphere->diameter / 2;
    oc = minus(ray->place, sphere->center);
    obj_hit->a = dot_product(ray->vector, ray->vector);
    obj_hit->b = 2.0 * dot_product(ray->vector, oc);
    obj_hit->c = dot_product(oc, oc) - radius * radius;
	if (quadratic(obj_hit) == true)
		return (check_closest(obj_hit));
	return (false);
}

