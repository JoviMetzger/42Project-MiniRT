/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_colour.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 15:44:57 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/22 14:53:37 by smclacke      ########   odam.nl         */
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

/**
 * @todo add comments/description here
 */
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


/**
 * @todo add comments/description here
 */
// t_colour get_plane_colour(t_data *data, t_hit_data *hit_data, t_ray ray, t_objs *plane)
// {
//     t_colour result;
//     double AMBIENT_INTENSITY = data->ambient.ratio; // (0.2)
//     double DIFFUSE_INTENSITY = data->light.ratio;   // (0.7)
//     double SPECULAR_INTENSITY = 0.2;
//     double SPECULAR_POWER = 50; //32
    
//     // Using the 'Phong reflection model'
// 	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, hit_data->t));
// 	t_vec3	normal = normalize_vector(minus(intersection_point, plane->center));

// 	// Ambient light contribution
// 	double ambient_red = AMBIENT_INTENSITY * data->ambient.colour.r;
// 	double ambient_green = AMBIENT_INTENSITY * data->ambient.colour.g;
// 	double ambient_blue = AMBIENT_INTENSITY * data->ambient.colour.b;

// 	// Diffuse light contribution
// 	t_vec3 light_direction = normalize_vector(minus(data->light.place, intersection_point));
// 	double diffuse_factor = dot_product(normal, light_direction);
// 	if (diffuse_factor < 0.0)
// 	{
// 		DIFFUSE_INTENSITY = 0.0;
// 		SPECULAR_INTENSITY = 0.0;
// 		diffuse_factor = 0.0;
// 		ambient_red *= AMBIENT_INTENSITY;
// 		ambient_green *= AMBIENT_INTENSITY;
// 		ambient_blue *= AMBIENT_INTENSITY;
// 	}
// 	double diffuse_red = DIFFUSE_INTENSITY * diffuse_factor * data->light.colour.r;
// 	double diffuse_green = DIFFUSE_INTENSITY * diffuse_factor * data->light.colour.g;
// 	double diffuse_blue = DIFFUSE_INTENSITY * diffuse_factor * data->light.colour.b;
	
// 	// Specular light contribution 
// 	t_vec3 view_direction = normalize_vector(minus(ray.place, intersection_point));
// 	t_vec3 reflection_direction = normalize_vector(ft_reflect(light_direction, normal));
// 	double specular_factor = pow(dot_product(reflection_direction, view_direction), SPECULAR_POWER);
// 	if (specular_factor < 0.0)
// 		specular_factor = 0.0;
// 	double specular_red = SPECULAR_INTENSITY * specular_factor * data->ambient.colour.r;
// 	double specular_green= SPECULAR_INTENSITY * specular_factor * data->ambient.colour.g;
// 	double specular_blue = SPECULAR_INTENSITY * specular_factor * data->ambient.colour.b;

// 	// Combine ambient, diffuse, and specular contributions
// 	double final_red = ambient_red + diffuse_red + specular_red;
// 	double final_green = ambient_green + diffuse_green + specular_green;
// 	double final_blue = ambient_blue + diffuse_blue + specular_blue;
	
// 	// Clamp final values to [0, 255]
// 	 result.r = result.r * plane->colour.r / 255;
// 	result.g = result.g* plane->colour.g / 255;
// 	result.b = result.b* plane->colour.b / 255;

// 	result.r = final_red;
// 	result.g = final_green;
// 	result.b = final_blue;

// 	return result;
	
// }

// t_colour get_plane_colour(t_data *data, t_hit_data *hit_data, t_ray ray, t_objs *plane) 
// {
//     t_colour result;
//     t_vec3 intersection_point;
//     t_vec3 normal;
//     t_ray shadow_ray;
//     t_vec3 reflection_direction;
//     t_vec3 view_direction;

//     double AMBIENT_INTENSITY = data->ambient.ratio;
//     double SPECULAR_INTENSITY = 0.2;
//     double SPECULAR_POWER = 32;

//     // Using the 'Phong reflection model'
//     intersection_point = plus(ray.place, mult_vecdub(ray.vector, hit_data->t));
//     normal = normalize_vector(minus(intersection_point, plane->center));

//     // Ambient light contribution
//     double ambient_red = AMBIENT_INTENSITY * data->ambient.colour.r;
//     double ambient_green = AMBIENT_INTENSITY * data->ambient.colour.g;
//     double ambient_blue = AMBIENT_INTENSITY * data->ambient.colour.b;

//     // Initialize result color with ambient light contribution
//     result.r = ambient_red;
//     result.g = ambient_green;
//     result.b = ambient_blue;

// 	int i = 0;
//     while (i < data->lights_i) 
// 	{
//         t_lightS *current_light = data->lightS[i];

//         // Shadow ray
//         t_vec3 light_direction = normalize_vector(minus(current_light->place, intersection_point));
//         shadow_ray.place = plus(intersection_point, mult_vecdub(normal, EPSILON)); // Add small offset to avoid self-intersection
//         shadow_ray.vector = light_direction;

//         bool in_shadow = false;
// 		int j = 0;
//         while (j < data->objs_i) 
// 		{
//             if (intersect_plane(&shadow_ray, data->objs[j], hit_data) || intersect_sphere(&shadow_ray, data->objs[j], hit_data) || intersect_cylinder(&shadow_ray, data->objs[j], hit_data)) 
// 			{
//                 in_shadow = true;
//                 break;
//             }
// 			j++;
//         }

//         if (!in_shadow) 
// 		{
//             // Diffuse light contribution
//             double diffuse_factor = dot_product(normal, light_direction);
//             if (diffuse_factor < 0.0) 
//                 diffuse_factor = 0.0;
//             double diffuse_red = current_light->ratio * diffuse_factor * current_light->colour.r;
//             double diffuse_green = current_light->ratio * diffuse_factor * current_light->colour.g;
//             double diffuse_blue = current_light->ratio * diffuse_factor * current_light->colour.b;

//             // Specular light contribution
//             view_direction = normalize_vector(minus(ray.place, intersection_point));
//             reflection_direction = normalize_vector(ft_reflect(light_direction, normal));
//             double specular_factor = pow(dot_product(reflection_direction, view_direction), SPECULAR_POWER);
//             if (specular_factor < 0.0) 
//                 specular_factor = 0.0;
//             double specular_red = SPECULAR_INTENSITY * specular_factor * current_light->colour.r;
//             double specular_green = SPECULAR_INTENSITY * specular_factor * current_light->colour.g;
//             double specular_blue = SPECULAR_INTENSITY * specular_factor * current_light->colour.b;

//             // Add the contributions from this light to the result
//             result.r += diffuse_red + specular_red;
//             result.g += diffuse_green + specular_green;
//             result.b += diffuse_blue + specular_blue;
//         }
// 		i++;
//     }

//     // Clamp final values to [0, 255] and apply the object's base color
//     result.r = fmin(result.r * plane->colour.r / 255, 255.0);
//     result.g = fmin(result.g * plane->colour.g / 255, 255.0);
//     result.b = fmin(result.b * plane->colour.b / 255, 255.0);

//     return result;        
// }