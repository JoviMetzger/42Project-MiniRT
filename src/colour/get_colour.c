/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_colour.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 15:45:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/23 17:18:20 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Specular light contribution
static void	specular_light(t_data *data, t_colour_vars *vars, t_ray *ray)
{
	vars->view_direction = normalize_vector(minus(ray->place, vars->inter_point));
	vars->reflection_direction = normalize_vector(ft_reflect(vars->light_direction, vars->normal));
	vars->specular_factor = pow(dot_product(vars->reflection_direction, vars->view_direction), vars->specular_power);
	if (vars->specular_factor < 0.0)
		vars->specular_factor = 0.0;
	vars->specular_red = vars->specular_power * vars->specular_factor * data->light.colour.r;
	vars->specular_green= vars->specular_power * vars->specular_factor * data->light.colour.g;
	vars->specular_blue = vars->specular_power * vars->specular_factor * data->light.colour.b;
}

// Diffuse light contribution	
static void	diffuse_light(t_data *data, t_colour_vars *vars)
{
	vars->light_direction = normalize_vector(minus(data->light.place, vars->inter_point));
	vars->diffuse_factor = dot_product(vars->normal, vars->light_direction);
	if (vars->diffuse_factor < 0.0)
		vars->diffuse_factor = 0.0;
	vars->diffuse_red = vars->diffuse_intensity * vars->diffuse_factor * data->light.colour.r;
	vars->diffuse_green = vars->diffuse_intensity * vars->diffuse_factor * data->light.colour.g;
	vars->diffuse_blue = vars->diffuse_intensity * vars->diffuse_factor * data->light.colour.b;
}

// Ambient intensity
// Ambient light contribution
static void	init_vars(t_data *data, t_colour_vars *vars)
{
	vars->ambient_intensity = data->ambient.ratio; // (0.2)
	vars->diffuse_intensity = data->light.ratio; // (0.6)
	vars->specular_intensity = 0.2;
	vars->specular_power = 32;
	vars->ambient_red = vars->ambient_intensity * data->ambient.colour.r;
	vars->ambient_green = vars->ambient_intensity * data->ambient.colour.g;
	vars->ambient_blue = vars->ambient_intensity * data->ambient.colour.b;
}

// Using the 'Phong reflection model'
// Combine ambient, diffuse, and specular contributions
// Clamp final values to [0, 255]
// obj - data_obj | obj_i - specific object passed
t_colour	get_colour(t_data *data, t_obj_data *obj, t_ray ray, t_objs *obj_i)
{
	t_colour		result;
	t_colour_vars	vars;

	// vars = NULL;
	// ft_bzero(vars, sizeof(t_colour_vars));
	init_vars(data, &vars);
	diffuse_light(data, &vars);
	specular_light(data, &vars, &ray);
	vars.inter_point = plus(ray.place, mult_vecdub(ray.vector, obj->t));
	vars.normal = normalize_vector(minus(vars.inter_point, obj_i->center));
	vars.final_red = vars.ambient_red + vars.diffuse_red;
	vars.final_red += vars.specular_red;
	vars.final_green = vars.ambient_green + vars.diffuse_green;
	vars.final_green += vars.specular_green;
	vars.final_blue = vars.ambient_blue + vars.diffuse_blue;
	vars.final_blue += vars.specular_blue;
	vars.final_red = fmin(fmax(vars.final_red, obj_i->colour.r), 255);
	vars.final_green = fmin(fmax(vars.final_green, obj_i->colour.g), 255);
	vars.final_blue = fmin(fmax(vars.final_blue, obj_i->colour.b), 255);
	result.r = vars.final_red;
	result.g = vars.final_green;
	result.b = vars.final_blue;
	return (result);
}
