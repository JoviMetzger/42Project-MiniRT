/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_colour.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/11 17:48:48 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"


// t_colour get_sphere_colour(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere)
// {
//     t_colour result;
//     double AMBIENT_INTENSITY = data->ambient.ratio; // (0.2)
//     double DIFFUSE_INTENSITY = data->light.ratio;   // (0.6)
//     double SPECULAR_INTENSITY = 0.2;
//     double SPECULAR_POWER = 32;
    
//     // Using the 'Phong reflection model'
// 	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));
// 	t_vec3	normal = normalize_vector(minus(intersection_point, sphere->center));

// 	// Ambient light contribution
// 	double ambient_red = AMBIENT_INTENSITY * data->ambient.colour.r;
// 	double ambient_green = AMBIENT_INTENSITY * data->ambient.colour.g;
// 	double ambient_blue = AMBIENT_INTENSITY * data->ambient.colour.b;

// 	// Diffuse light contribution
// 	t_vec3 light_direction = normalize_vector(minus(data->light.place, intersection_point));
// 	double diffuse_factor = dot_product(normal, light_direction);
// 	if (diffuse_factor < 0.0)
// 		diffuse_factor = 0.0;
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
// 	final_red = fmin(fmax(final_red, sphere->colour.r), 255);
// 	final_green = fmin(fmax(final_green, sphere->colour.g), 255);
// 	final_blue = fmin(fmax(final_blue, sphere->colour.b), 255);

// 	result.r = final_red;
// 	result.g = final_green;
// 	result.b = final_blue;
	
// 	return result;	
	
// }


// ------------------ for checkerboard IS WORKING ----------------------------------------
t_colour get_sphere_checherboard(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere)
{

	// (void)data;
    double radius = sphere->diameter / 2;
    double AMBIENT_INTENSITY = data->ambient.ratio; // (0.2)
    double DIFFUSE_INTENSITY = data->light.ratio;   // (0.6)
    double SPECULAR_INTENSITY = 0.2;
    double SPECULAR_POWER = 32;
    t_colour colour;
    
    // Using the 'Phong reflection model'
	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));

	// ===================== Lighting =====================
	// ====================================================
	t_vec3	normal = normalize_vector(minus(intersection_point, sphere->center));

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
	double specular_red = SPECULAR_INTENSITY * specular_factor * data->ambient.colour.r;
	double specular_green= SPECULAR_INTENSITY * specular_factor * data->ambient.colour.g;
	double specular_blue = SPECULAR_INTENSITY * specular_factor * data->ambient.colour.b;

	// Combine ambient, diffuse, and specular contributions
	double final_red = ambient_red + diffuse_red + specular_red;
	double final_green = ambient_green + diffuse_green + specular_green;
	double final_blue = ambient_blue + diffuse_blue + specular_blue;
	

	// =================== Checkerboard ===================
	// ====================================================
	
    // Calculate spherical coordinates from intersection point
    double phi = atan2(intersection_point.z, intersection_point.x);
    double theta = acos(intersection_point.y / radius);

    // Map spherical coordinates to UV coordinates
    double u = (phi + M_PI) / (2 * M_PI); // Normalize phi to [0, 1]
    double v = 1.0 - (theta / M_PI);     // Normalize theta to [0, 1] and flip vertically

    // Define the size of squares in UV space
    double square_size_u = 0.003; // Adjust as needed
    double square_size_v = 0.05; // Adjust as needed

    // Determine the checkerboard pattern based on UV coordinates
    bool is_black = ((int)(u / square_size_u) + (int)(v / square_size_v)) % 2 == 0;

    // Determine color based on checkerboard pattern
    if (is_black)
    {
		// Clamp final values to [0, 255]
		colour.r = fmin(fmax(final_red, 0), 255);
		colour.g = fmin(fmax(final_green, 0), 255);
		colour.b = fmin(fmax(final_blue, 0), 255);
        // colour.r = 0;
        // colour.g = 0;
        // colour.b = 0;
    }
    else
    {
		// Clamp final values to [0, 255]
		colour.r = fmin(fmax(final_red, 255), 255);
		colour.g = fmin(fmax(final_green, 255), 255);
		colour.b = fmin(fmax(final_blue, 255), 255);
        // colour.r = 255;
        // colour.g = 255;
        // colour.b = 255;
    }
    
    return colour;
}



// ------- This is for bumpmap NOT WORKING YET -----------------------

// double texture_sample_bump(double u, double v) 
// {
//     // Sample the bump map texture at the given texture coordinates (u, v)
//     // Return the intensity of the bump map at that point

// 	get_map();
    
//     // Example implementation:
//     int texture_width = bump_map_texture->width;
//     int texture_height = bump_map_texture->height;
    
//     // Map UV coordinates to texture pixel coordinates
//     int x = (int)(u * texture_width);
//     int y = (int)(v * texture_height);
    
//     // Clamp pixel coordinates to texture bounds
//     x = fmin(fmax(x, 0), texture_width - 1);
//     y = fmin(fmax(y, 0), texture_height - 1);
    
//     // Sample bump map intensity at the specified pixel
//     double bump_intensity = bump_map_texture->pixels[y * texture_width + x];
    
//     // Return the sampled bump intensity
//     return bump_intensity;
// }



// t_colour get_sphere_bumpmap(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere)
// {
// 	int BUMP_SCALE = 10;
// 	double DIFFUSE_INTENSITY = data->light.ratio;   // (0.6)
// 	t_colour colour;
	
// 	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));
	
// 	// Original normal calculation
// 	t_vec3 original_normal = normalize_vector(minus(intersection_point, sphere->center));
	
// 	// Sample bump map texture
// 	double bump_intensity = texture_sample_bump(intersection_point.x, intersection_point.z);
	
// 	// Perturb the normal based on bump map
// 	t_vec3 perturbed_normal = original_normal;
// 	perturbed_normal.x += bump_intensity * BUMP_SCALE; // Adjust normal based on bump intensity
// 	perturbed_normal.y += bump_intensity * BUMP_SCALE; // Adjust normal based on bump intensity
// 	perturbed_normal.z += bump_intensity * BUMP_SCALE; // Adjust normal based on bump intensity
// 	perturbed_normal = normalize_vector(perturbed_normal);
	
// 	// Perform shading using perturbed normal
// 	// You can use the perturbed normal in your lighting calculations
	
// 	// Example: Compute color based on diffuse lighting with perturbed normal
// 	t_vec3 light_direction = normalize_vector(minus(data->light.place, intersection_point));
// 	double diffuse_factor = dot_product(perturbed_normal, light_direction);
// 	double diffuse_red = DIFFUSE_INTENSITY * diffuse_factor * 255;
// 	double diffuse_green = DIFFUSE_INTENSITY * diffuse_factor * 255;
// 	double diffuse_blue = DIFFUSE_INTENSITY * diffuse_factor * 255;
	
// 	// Clamp final values to [0, 255]
// 	diffuse_red = fmin(fmax(diffuse_red, 0), 255);
// 	diffuse_green = fmin(fmax(diffuse_green, 0), 255);
// 	diffuse_blue = fmin(fmax(diffuse_blue, 0), 255);

// 	colour.r = diffuse_red;
// 	colour.g = diffuse_green;
// 	colour.b = diffuse_blue;
	
// 	return colour;
// }