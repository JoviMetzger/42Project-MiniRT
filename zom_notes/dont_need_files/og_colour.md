<<<<<<< HEAD
t_colour get_cyl_colour(t_data *data, t_hit_data *hit_data, t_ray ray, t_objs *cylinder)
=======
<<<<<<< HEAD:zom_notes/dont_need_files/og_colour.md
<<<<<<< HEAD
t_colour get_cyl_colour(t_data *data, t_hit_data *obj_hit, t_ray ray, t_objs *cylinder)
=======
t_colour get_cyl_colour(t_data *data, t_hit_data *hit_data, t_ray ray, t_objs *cylinder)
>>>>>>> parser
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_colour.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 15:45:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/17 14:52:48 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * @todo norm 
 */
<<<<<<< HEAD
// t_colour get_cyl_colour(t_data *data, t_hit_data *obj_hit, t_ray ray, t_objs *cylinder)
=======
// t_colour get_cyl_colour(t_data *data, t_hit_data *hit_data, t_ray ray, t_objs *cylinder)
>>>>>>> parser
// {
//     t_colour result;
//     double AMBIENT_INTENSITY = data->ambient.ratio; // (0.2)
//     double DIFFUSE_INTENSITY = data->light.ratio;   // (0.6)
//     double SPECULAR_INTENSITY = 0.2;
//     double SPECULAR_POWER = 32;
    
//     // Using the 'Phong reflection model'
<<<<<<< HEAD
// 	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_hit->t));
// 	t_vec3	normal = normalize(minus(intersection_point, cylinder->center));
=======
// 	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, hit_data->t));
// 	t_vec3	normal = normalize(minus(intersection_point, cylinder->center));
>>>>>>> parser

// 	// Ambient light contribution
// 	double ambient_red = AMBIENT_INTENSITY * data->ambient.colour.r;
// 	double ambient_green = AMBIENT_INTENSITY * data->ambient.colour.g;
// 	double ambient_blue = AMBIENT_INTENSITY * data->ambient.colour.b;

// 	// Diffuse light contribution
// 	t_vec3 light_direction = normalize(minus(data->light.place, intersection_point));
// 	double diffuse_factor = dot_product(normal, light_direction);
// 	if (diffuse_factor < 0.0)
// 		diffuse_factor = 0.0;
// 	double diffuse_red = DIFFUSE_INTENSITY * diffuse_factor * data->light.colour.r;
// 	double diffuse_green = DIFFUSE_INTENSITY * diffuse_factor * data->light.colour.g;
// 	double diffuse_blue = DIFFUSE_INTENSITY * diffuse_factor * data->light.colour.b;
	
// 	// Specular light contribution
// 	t_vec3 view_direction = normalize(minus(ray.place, intersection_point));
// 	t_vec3 reflection_direction = normalize(ft_reflect(light_direction, normal));
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
// 	final_red = fmin(fmax(final_red, cylinder->colour.r), 255);
// 	final_green = fmin(fmax(final_green, cylinder->colour.g), 255);
// 	final_blue = fmin(fmax(final_blue, cylinder->colour.b), 255);

// 	result.r = final_red;
// 	result.g = final_green;
// 	result.b = final_blue;
	
// 	return result;	
	
// }

<<<<<<< HEAD
t_colour get_cyl_colour(t_data *data, t_hit_data *obj_hit, t_ray ray, t_objs *cylinder) 
=======
t_colour get_cyl_colour(t_data *data, t_hit_data *hit_data, t_ray ray, t_objs *cylinder) 
>>>>>>> parser
>>>>>>> putPixel:src/colour/cylinder_colour.c
>>>>>>> main
{
    t_colour result;
    t_vec3 intersection_point;
    t_vec3 normal;
    t_ray shadow_ray;
    t_vec3 reflection_direction;
    t_vec3 view_direction;

    double AMBIENT_INTENSITY = data->ambient.ratio;
    double SPECULAR_INTENSITY = 0.2;
    double SPECULAR_POWER = 32;

    // Using the 'Phong reflection model'
<<<<<<< HEAD
    intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_hit->t));
    normal = normalize(minus(intersection_point, cylinder->center));
=======
<<<<<<< HEAD
	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, hit_data->t));
	t_vec3	normal = normalize(minus(intersection_point, cylinder->center));
=======
    intersection_point = plus(ray.place, mult_vecdub(ray.vector, hit_data->t));
    normal = normalize(minus(intersection_point, cylinder->center));
>>>>>>> main
>>>>>>> parser

    // Ambient light contribution
    double ambient_red = AMBIENT_INTENSITY * data->ambient.colour.r;
    double ambient_green = AMBIENT_INTENSITY * data->ambient.colour.g;
    double ambient_blue = AMBIENT_INTENSITY * data->ambient.colour.b;

    // Initialize result color with ambient light contribution
    result.r = ambient_red;
    result.g = ambient_green;
    result.b = ambient_blue;

	int i = 0;
    while (i < data->light_i) 
	{
        t_light *current_light = data->light[i];

<<<<<<< HEAD:zom_notes/dont_need_files/og_colour.md
	result.r = final_red;
	result.g = final_green;
	result.b = final_blue;
	
	return result;	
	
}
=======
        // Shadow ray
        t_vec3 light_direction = normalize(minus(current_light->place, intersection_point));
        shadow_ray.place = plus(intersection_point, mult_vecdub(normal, EPSILON)); // Add small offset to avoid self-intersection
        shadow_ray.vector = light_direction;

        bool in_shadow = false;
		int j = 0;
        while (j < data->objs_i) 
		{
<<<<<<< HEAD
            if (intersect_sphere(&shadow_ray, data->objs[j], obj_hit) || intersect_plane(&shadow_ray, data->objs[j], obj_hit) || intersect_cylinder(&shadow_ray, data->objs[j], obj_hit)) 
=======
            if (intersect_sphere(&shadow_ray, data->objs[j], hit_data) || intersect_plane(&shadow_ray, data->objs[j], hit_data) || intersect_cylinder(&shadow_ray, data->objs[j], hit_data)) 
>>>>>>> parser
			{
                in_shadow = true;
                break;
            }
			j++;
        }

        if (!in_shadow) 
		{
            // Diffuse light contribution
            double diffuse_factor = dot_product(normal, light_direction);
            if (diffuse_factor < 0.0) 
                diffuse_factor = 0.0;
            double diffuse_red = current_light->ratio * diffuse_factor * current_light->colour.r;
            double diffuse_green = current_light->ratio * diffuse_factor * current_light->colour.g;
            double diffuse_blue = current_light->ratio * diffuse_factor * current_light->colour.b;

            // Specular light contribution
            view_direction = normalize(minus(ray.place, intersection_point));
            reflection_direction = normalize(ft_reflect(light_direction, normal));
            double specular_factor = pow(dot_product(reflection_direction, view_direction), SPECULAR_POWER);
            if (specular_factor < 0.0) 
                specular_factor = 0.0;
            double specular_red = SPECULAR_INTENSITY * specular_factor * current_light->colour.r;
            double specular_green = SPECULAR_INTENSITY * specular_factor * current_light->colour.g;
            double specular_blue = SPECULAR_INTENSITY * specular_factor * current_light->colour.b;

            // Add the contributions from this light to the result
            result.r += diffuse_red + specular_red;
            result.g += diffuse_green + specular_green;
            result.b += diffuse_blue + specular_blue;
        }
		i++;
    }

    // Clamp final values to [0, 255] and apply the object's base color
    result.r = fmin(result.r * cylinder->colour.r / 255, 255.0);
    result.g = fmin(result.g * cylinder->colour.g / 255, 255.0);
    result.b = fmin(result.b * cylinder->colour.b / 255, 255.0);

    return result;    
}
>>>>>>> putPixel:src/colour/cylinder_colour.c
