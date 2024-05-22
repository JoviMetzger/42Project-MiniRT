/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_colour.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/22 14:53:37 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// // Initializing the t_colour_vars struct.
// static t_colour_vars init_colour(t_data *data, t_hit_data *hit_data, t_ray ray, t_objs *sphere)
// {
// 	t_colour_vars	colour;
// 	colour.ambient_ratio = data->ambient.ratio;
// 	colour.specular_intensity = 0.2;
// 	colour.specular_power = 32;

//     // Using the 'Phong reflection model'
//     colour.intersection_point = plus(ray.place, mult_vecdub(ray.vector, hit_data->t));
//     colour.normal = normalize_vector(minus(colour.intersection_point, sphere->center));

//     // Ambient light contribution
//     colour.ambient_red = colour.ambient_ratio * data->ambient.colour.r;
//     colour.ambient_green = colour.ambient_ratio * data->ambient.colour.g;
//     colour.ambient_blue = colour.ambient_ratio * data->ambient.colour.b;

//     // Initialize result color with ambient light contribution
//     colour.result.r = colour.ambient_red;
//     colour.result.g = colour.ambient_green;
//     colour.result.b = colour.ambient_blue;
// 	return colour;
// }

// static void diffuse_light(t_colour_vars *colour)
// {
// 	colour->diffuse_factor = dot_product(colour->normal, colour->light_direction);
// 	if (colour->diffuse_factor < 0.0) 
// 		colour->diffuse_factor = 0.0;
// 	colour->diffuse_red = colour->current_light->ratio * colour->diffuse_factor * colour->current_light->colour.r;
// 	colour->diffuse_green = colour->current_light->ratio * colour->diffuse_factor * colour->current_light->colour.g;
// 	colour->diffuse_blue = colour->current_light->ratio * colour->diffuse_factor * colour->current_light->colour.b;
// }

// static void specular_light(t_colour_vars *colour, t_ray ray)
// {
// 	colour->view_direction = normalize_vector(minus(ray.place, colour->intersection_point));
// 	colour->reflection_direction = normalize_vector(ft_reflect(colour->light_direction, colour->normal));
// 	colour->specular_factor = pow(dot_product(colour->reflection_direction, colour->view_direction), colour->specular_power);
// 	if (colour->specular_factor < 0.0) 
// 		colour->specular_factor = 0.0;
// 	colour->specular_red = colour->specular_intensity * colour->specular_factor * colour->current_light->colour.r;
// 	colour->specular_green = colour->specular_intensity * colour->specular_factor * colour->current_light->colour.g;
// 	colour->specular_blue = colour->specular_intensity * colour->specular_factor * colour->current_light->colour.b;
// }

// // calculation of the light_ray and if it hits a object, it should not gp trough the object, so that it gives a shadow
// static void shadow_calculation(t_data *data, t_colour_vars *colour, t_ray ray, t_hit_data *hit_data)
// {
// 	t_ray	shadow_ray;
// 	bool 	in_shadow;
// 	int 	i;
	
// 	in_shadow = false;
// 	i = 0;

// 	// Shadow ray
// 	colour->light_direction = normalize_vector(minus(colour->current_light->place, colour->intersection_point));
// 	shadow_ray.place = plus(colour->intersection_point, mult_vecdub(colour->normal, EPSILON)); // Add small offset to avoid self-intersection

// 	// check if the light_ray hits an object
// 	while (++i < data->objs_i) 
// 	{
// 		if (intersect_sphere(&shadow_ray, data->objs[i], hit_data) 
// 			|| intersect_plane(&shadow_ray, data->objs[i], hit_data) 
// 			|| intersect_cylinder(&shadow_ray, data->objs[i], hit_data)) 
// 			in_shadow = true;
// 	}
// 	if (!in_shadow) 
// 	{
// 		diffuse_light(colour);		 // Diffuse light contribution
// 		specular_light(colour, ray); // Specular light contribution

// 		// Add the contributions from this light to the colour.result
// 		colour->result.r += colour->diffuse_red + colour->specular_red;
// 		colour->result.g += colour->diffuse_green + colour->specular_green;
// 		colour->result.b += colour->diffuse_blue + colour->specular_blue;
// 	}
// }

// // Function to check if a point is shadowed by any object in the scene
// t_colour get_sphere_colour(t_data *data, t_hit_data *hit_data, t_ray ray, t_objs *sphere) 
// {
// 	t_colour_vars	colour;
// 	t_colour 		checkerboard_colour;
// 	t_colour		base;
// 	int 			i;
	
// 	colour = init_colour(data, hit_data, ray, sphere);
//     colour.intersection_point = plus(ray.place, mult_vecdub(ray.vector, hit_data->t));
//     colour.normal = normalize_vector(minus(colour.intersection_point, sphere->center));
// 	i = -1;
    
//     // Calculate the checkerboard pattern color
// 	if (sphere->what_pattern == 1)	
// 	{
// 		checkerboard_colour = get_checkerboard_colour(colour.normal);
// 		base = checkerboard_colour;
// 	}
// 	else
// 		base = sphere->colour;
	
// 	// Go through all the different lights
//     while (++i < data->lights_i) 
// 	{
// 		colour.current_light = data->lightS[i];
// 		shadow_calculation(data, &colour, ray, hit_data);
//     }

//     // Clamp final values to [0, 255] and apply the object's base color
//     colour.result.r = fmin(colour.result.r * base.r / 255, 255.0);
//     colour.result.g = fmin(colour.result.g * base.g / 255, 255.0);
//     colour.result.b = fmin(colour.result.b * base.b / 255, 255.0);

//     return (colour.result);    
// }



// // ------------------ for checkerboard IS WORKING ----------------------------------------
// t_colour get_checkerboard_colour(t_vec3 normal)
// {
//     int num_squares;
//     t_colour colour;
// 	bool is_black;
	    
// 	num_squares = 10;
//     double theta = atan2(normal.z, normal.x); 	// Angle in the x-z plane
//     double phi = acos(normal.y);                // Angle from the positive y-axis
    
//     // Normalize theta and phi to [0, 1]
//     double u = (theta + M_PI) / (2 * M_PI); // Theta ranges from -pi to pi
//     double v = phi / M_PI;                  // Phi ranges from 0 to pi
    
//     // Scale coordinates by number of squares
//     double square_u = u * num_squares;
//     double square_v = v * num_squares;
    
//     // Determine color based on checkerboard pattern
//     is_black = ((int)floor(square_u) % 2 == (int)floor(square_v) % 2);
    
//     if (is_black) 
// 	{
//         colour.r = 0;
//         colour.g = 0;
//         colour.b = 0;
//     } 
// 	else 
// 	{
//         colour.r = 255;
//         colour.g = 255;
//         colour.b = 255;
//     }
    
//     return colour;
// }

