/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/22 17:20:47 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * if t is negative, no intersection found
 * 
 * 			t = -X|V / D|V
 * 
 * 			x = ray origin - center point of a shape
 *			v = plane normal
 * 			d = ray direction
 */
bool	intersect_plane(t_ray *ray, t_objs *plane, t_hit_data *hit_data)
{
	t_vec3	oc;
	double denom;

	denom = dot_product(ray->vector, plane->vector);
	if (fabs(denom) > EPSILON)
	{
		oc = minus(ray->place, plane->center);
		hit_data->t = -dot_product(oc, plane->vector) / denom;
		if (hit_data->t >= EPSILON)
		{
			if (denom > 0)
				plane->normal = normalize_vector(mult_vecdub(plane->vector, -1)); // reverse surface normal
			return (check_closest(hit_data)); 
		}
	}
	return (false);
}

// Clamp final values to [0, 255]
t_colour	get_pl_colour(t_data *data, t_hit_data *hit, t_ray ray, t_objs *obj)
{
	t_colour		result;
	t_colour_vars	vars;
	
	ft_bzero(&vars, sizeof(t_colour_vars));
	vars.inter_point = plus(ray.place, mult_vecdub(ray.vector, hit->closest_t));
	vars.normal = obj->normal;
	get_colour(data, &vars, ray);
	
	vars.final_red = vars.ambient_red + vars.diffuse_red;
	vars.final_red += vars.spec_red;
	vars.final_green = vars.ambient_green + vars.diffuse_green;
	vars.final_green += vars.spec_green;
	vars.final_blue = vars.ambient_blue + vars.diffuse_blue;
	vars.final_blue += vars.spec_blue;
	vars.final_red = fmin(fmax(vars.final_red, obj->colour.r), 255);
	vars.final_green = fmin(fmax(vars.final_green, obj->colour.g), 255);
	vars.final_blue = fmin(fmax(vars.final_blue, obj->colour.b), 255);
	result.r = vars.final_red;
	result.g = vars.final_green;
	result.b = vars.final_blue;
	return (result);
}
