/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_colour.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 15:44:57 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/23 15:17:54 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// typedef	struct s_colour_vars
// {
// 	t_colour	result;
// 	double		ambient_intensity;
// 	double		diffuse_intensity;
// 	double		specular_intensity;
// 	double		specular_power;
// 	t_vec3		intersection_point;
// 	t_vec3		normal;
// 	double		ambient_red;
// 	double		ambient_green;
// 	double		ambient_blue;
// 	double		diffuse_red;
// 	double		diffuse_green;
// 	double		diffuse_blue;
	
// }			t_colour_vars;

// /**
//  * @todo add comments/description here
//  */
// static void	init_vars(t_data *data, t_colour_vars *vars)
// {
// 	vars->ambient_intensity = data->ambient.ratio; // (0.2)
// 	vars->diffuse_intensity = data->light.ratio; // (0.6)
// 	vars->specular_intensity = 0.2;
// 	vars->specular_power = 32;
	
// 	// Ambient light contribution
// 	vars->ambient_red = vars->ambient_intensity * data->ambient.colour.r;
// 	vars->ambient_green = vars->ambient_intensity * data->ambient.colour.g;
// 	vars->ambient_blue = vars->ambient_intensity * data->ambient.colour.b;
// }


// /**
//  * @todo add comments/description here
//  */
// t_colour get_plane_colour(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *plane)
// {
//     t_colour 		result;
//     t_colour_vars	vars;

// 	init_vars(data, &vars);

//     // Using the 'Phong reflection model'
// 	vars.intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));
// 	vars.normal = normalize_vector(minus(vars.intersection_point, plane->center));



// 	// Diffuse light contribution	
// 	t_vec3 light_direction = normalize_vector(minus(data->light.place, intersection_point));
// 	double diffuse_factor = dot_product(normal, light_direction);
// 	if (diffuse_factor < 0.0)
// 		diffuse_factor = 0.0;
// 	vars.diffuse_red = vars.diffuse_intensity * diffuse_factor * data->light.colour.r;
// 	vars.diffuse_green = vars.diffuse_intensity * diffuse_factor * data->light.colour.g;
// 	vars.diffuse_blue = vars.diffuse_intensity * diffuse_factor * data->light.colour.b;
	
// 	// Specular light contribution
// 	t_vec3 view_direction = normalize_vector(minus(ray.place, intersection_point));
// 	t_vec3 reflection_direction = normalize_vector(ft_reflect(light_direction, normal));
// 	double specular_factor = pow(dot_product(reflection_direction, view_direction), SPECULAR_POWER);
// 	if (specular_factor < 0.0)
// 		specular_factor = 0.0;
// 	double specular_red = SPECULAR_INTENSITY * specular_factor * data->light.colour.r;
// 	double specular_green= SPECULAR_INTENSITY * specular_factor * data->light.colour.g;
// 	double specular_blue = SPECULAR_INTENSITY * specular_factor * data->light.colour.b;

// 	// Combine ambient, diffuse, and specular contributions
// 	double final_red = ambient_red + diffuse_red + specular_red;
// 	double final_green = ambient_green + diffuse_green + specular_green;
// 	double final_blue = ambient_blue + diffuse_blue + specular_blue;
	
// 	// Clamp final values to [0, 255]
// 	final_red = fmin(fmax(final_red, plane->colour.r), 255);
// 	final_green = fmin(fmax(final_green, plane->colour.g), 255);
// 	final_blue = fmin(fmax(final_blue, plane->colour.b), 255);

// 	result.r = final_red;
// 	result.g = final_green;
// 	result.b = final_blue;
	
// 	return result;	
	
// }
