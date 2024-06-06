/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/06 12:04:59 by smclacke      ########   odam.nl         */
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

		The equation for a sphere of radius r
		that is centered at the origin is an important mathematical equation:

		x2+y2+z2=r2
		You can also think of this as saying that if a given point (x,y,z)
		is on the surface of the sphere, then x2+y2+z2=r2
		. If a given point (x,y,z)
		is inside the sphere, then x2+y2+z2<r2
		, and if a given point (x,y,z)
		is outside the sphere, then x2+y2+z2>r2
.
 */
bool	intersect_sphere(t_ray *ray, t_objs *sphere, t_hit_data *hit)
{
	double	radius;
	t_vec3	inter_point;

	radius = sphere->diameter / 2; //
	hit->o_c = minus(ray->place, sphere->center);
	hit->a = dot_product(ray->vector, ray->vector);
	hit->b = 2.0 * dot_product(ray->vector, hit->o_c);
	hit->c = dot_product(hit->o_c, hit->o_c) - radius * radius;
	if (quadratic(hit) == true)
	{
		inter_point = plus(ray->place, mult_vecdub(ray->vector, hit->t));
		sphere->normal = normalize_vector(minus(inter_point, sphere->center));
		return (check_closest(hit));
	}
	return (false);
}
