/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_colour.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 15:45:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/02 19:18:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

t_colour get_cylinder_colour(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *cylinder)
{
    t_colour result;
    double AMBIENT_INTENSITY = data->ambient.ratio; // (0.2)
    double DIFFUSE_INTENSITY = data->light.ratio;   // (0.6)
    double SPECULAR_INTENSITY = 0.2;
    double SPECULAR_POWER = 32;
    
    // Using the 'Phong reflection model'
	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));
	t_vec3	normal = normalize_vector(minus(intersection_point, cylinder->center));

	// Ambient light contribution
	double ambient_red = AMBIENT_INTENSITY * data->ambient.colour.r;
	double ambient_green = AMBIENT_INTENSITY * data->ambient.colour.g;
	double ambient_blue = AMBIENT_INTENSITY * data->ambient.colour.b;

	// Diffuse light contribution
	t_vec3 light_direction = normalize_vector(minus(data->light.place, intersection_point));
	double diffuse_factor = dot_product(normal, light_direction);
	if (diffuse_factor < 0.0)
		diffuse_factor = 0.0;
	double diffuse_red = DIFFUSE_INTENSITY * diffuse_factor * data->light.colour.r;
	double diffuse_green = DIFFUSE_INTENSITY * diffuse_factor * data->light.colour.g;
	double diffuse_blue = DIFFUSE_INTENSITY * diffuse_factor * data->light.colour.b;
	
	// Specular light contribution
	t_vec3 view_direction = normalize_vector(minus(ray.place, intersection_point));
	t_vec3 reflection_direction = normalize_vector(ft_reflect(light_direction, normal));
	double specular_factor = pow(dot_product(reflection_direction, view_direction), SPECULAR_POWER);
	if (specular_factor < 0.0)
		specular_factor = 0.0;
	double specular_red = SPECULAR_INTENSITY * specular_factor * data->light.colour.r;
	double specular_green= SPECULAR_INTENSITY * specular_factor * data->light.colour.g;
	double specular_blue = SPECULAR_INTENSITY * specular_factor * data->light.colour.b;

	// Combine ambient, diffuse, and specular contributions
	double final_red = ambient_red + diffuse_red + specular_red;
	double final_green = ambient_green + diffuse_green + specular_green;
	double final_blue = ambient_blue + diffuse_blue + specular_blue;
	
	// Clamp final values to [0, 255]
	final_red = fmin(fmax(final_red, cylinder->colour.r), 255);
	final_green = fmin(fmax(final_green, cylinder->colour.g), 255);
	final_blue = fmin(fmax(final_blue, cylinder->colour.b), 255);

	result.r = final_red;
	result.g = final_green;
	result.b = final_blue;
	
	return result;	
	
}
