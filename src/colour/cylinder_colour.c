/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_colour.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 15:45:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/22 22:29:13 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Using the 'Phong reflection model'
// Combine ambient, diffuse, and specular contributions
// Clamp final values to [0, 255]
t_colour	cyl_colour(t_data *data, t_obj_data *obj, t_ray ray, t_objs *cyl)
{
	t_colour		result;
	t_colour_vars	*vars;

	ft_bzero(vars, sizeof(t_colour_vars));
	init_vars(data, vars);
	diffuse_light(data, vars);
	specular_light(data, vars, &ray);
	vars->inter_point = plus(ray.place, mult_vecdub(ray.vector, obj->t));
	vars->normal = normalize_vector(minus(vars->inter_point, cyl->center));
	vars->final_red = vars->ambient_red + vars->diffuse_red;
	vars->final_red += vars->specular_red;
	vars->final_green = vars->ambient_green + vars->diffuse_green;
	vars->final_green += vars->specular_green;
	vars->final_blue = vars->ambient_blue + vars->diffuse_blue;
	vars->final_blue += vars->specular_blue;
	vars->final_red = fmin(fmax(vars->final_red, cyl->colour.r), 255);
	vars->final_green = fmin(fmax(vars->final_green, cyl->colour.g), 255);
	vars->final_blue = fmin(fmax(vars->final_blue, cyl->colour.b), 255);
	result.r = vars->final_red;
	result.g = vars->final_green;
	result.b = vars->final_blue;
	return (result);
}
