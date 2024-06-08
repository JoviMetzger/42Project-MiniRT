/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/08 14:23:09 by smclacke      ########   odam.nl         */
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
		return (check_closest(hit_data));
	return (false);
}

// Clamp final values to [0, 255]
t_colour	get_sp_colour(t_data *data, t_hit_data *hit, t_ray ray, t_objs *obj)
{
	t_colour		result;
	t_colour_vars	vars;
	
	ft_bzero(&vars, sizeof(t_colour_vars));
	vars.inter_point = plus(ray.place, mult_vecdub(ray.vector, hit->t));
	vars.normal = normalize(minus(vars.inter_point, obj->center));
	get_colour(data, &vars, ray);

	// specifically for sphere
	
	vars.final_red = fmin(fmax(vars.final_red, obj->colour.r), 255);
	vars.final_green = fmin(fmax(vars.final_green, obj->colour.g), 255);
	vars.final_blue = fmin(fmax(vars.final_blue, obj->colour.b), 255);
	result.r = vars.final_red;
	result.g = vars.final_green;
	result.b = vars.final_blue;
	return (result);
}
