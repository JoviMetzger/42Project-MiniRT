/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 22:20:36 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/22 22:28:02 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Specular light contribution
void	specular_light(t_data *data, t_colour_vars *vars, t_ray *ray)
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
void	diffuse_light(t_data *data, t_colour_vars *vars)
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
void	init_vars(t_data *data, t_colour_vars *vars)
{
	vars->ambient_intensity = data->ambient.ratio; // (0.2)
	vars->diffuse_intensity = data->light.ratio; // (0.6)
	vars->specular_intensity = 0.2;
	vars->specular_power = 32;
	vars->ambient_red = vars->ambient_intensity * data->ambient.colour.r;
	vars->ambient_green = vars->ambient_intensity * data->ambient.colour.g;
	vars->ambient_blue = vars->ambient_intensity * data->ambient.colour.b;
}
