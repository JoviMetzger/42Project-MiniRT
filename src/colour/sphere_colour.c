/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_colour.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/27 15:10:16 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"


t_colour get_sphere_colour(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere)
{
    t_colour result;
    double AMBIENT_INTENSITY = data->ambient.ratio; // (0.2)
    double DIFFUSE_INTENSITY = data->light.ratio;   // (0.7)
    double SPECULAR_INTENSITY = 0.2;
    double SPECULAR_POWER = 50; //32
    
    // Using the 'Phong reflection model'
	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));
	t_vec3	normal = normalize_vector(minus(intersection_point, sphere->center));

	// Ambient light contribution
	double ambient_red = AMBIENT_INTENSITY * data->ambient.colour.r;
	double ambient_green = AMBIENT_INTENSITY * data->ambient.colour.g;
	double ambient_blue = AMBIENT_INTENSITY * data->ambient.colour.b;

	// Diffuse light contribution
	t_vec3 light_direction = normalize_vector(minus(data->light.place, intersection_point));
	double diffuse_factor = dot_product(normal, light_direction);
	if (diffuse_factor < 0.0)
	{
		DIFFUSE_INTENSITY = 0.0;
		SPECULAR_INTENSITY = 0.0;
		diffuse_factor = 0.0;
		ambient_red *= AMBIENT_INTENSITY;
		ambient_green *= AMBIENT_INTENSITY;
		ambient_blue *= AMBIENT_INTENSITY;
	}
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
	
	// Clamp final values to [0, 255]
	final_red = fmin(fmax(final_red, sphere->colour.r), 255);
	final_green = fmin(fmax(final_green, sphere->colour.g), 255);
	final_blue = fmin(fmax(final_blue, sphere->colour.b), 255);

	result.r = final_red;
	result.g = final_green;
	result.b = final_blue;
	
	return result;	
	
}


// // ------------------ for checkerboard IS WORKING ----------------------------------------
// t_colour get_sphere_checkerboard(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere)
// {

// 	// (void)data;
//     double radius = sphere->diameter / 2;
//     double AMBIENT_INTENSITY = data->ambient.ratio; // (0.2)
//     double DIFFUSE_INTENSITY = data->light.ratio;   // (0.6)
//     double SPECULAR_INTENSITY = 0.2;
//     double SPECULAR_POWER = 32;
//     t_colour colour;
    
//     // Using the 'Phong reflection model'
// 	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));

// 	// ===================== Lighting =====================
// 	// ====================================================
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
	

// 	// =================== Checkerboard ===================
// 	// ====================================================
	
// 	t_vec3		sn;
// 	double		x;
// 	double		y;
// 	int NUM_SQUARES = 10; // Number of squares per side

// 	t_vec3 new = sphere->center;
// 	new.x = new.x - radius;
// 	new.y = new.y - radius;

	
// 	sn = minus(new, intersection_point);
// 	x = fabs(sn.x) * NUM_SQUARES;
// 	y = fabs(sn.y) * NUM_SQUARES;

//     // Determine color based on checkerboard pattern
//     if (((fmod(x, radius) <= radius / 2 && fmod(y, radius) <= radius / 2) ||
// 		(fmod(x, radius) > radius / 2 && fmod(y, radius) > radius / 2)))
//     {
// 		// Clamp final values to [0, 255]
// 		colour.r = fmin(fmax(final_red, 0), 255);
// 		colour.g = fmin(fmax(final_green, 0), 255);
// 		colour.b = fmin(fmax(final_blue, 0), 255);
//         // colour.r = 0;
//         // colour.g = 0;
//         // colour.b = 0;
//     }
//     else
//     {
// 		// Clamp final values to [0, 255]
// 		colour.r = fmin(fmax(final_red, 255), 255);
// 		colour.g = fmin(fmax(final_green, 255), 255);
// 		colour.b = fmin(fmax(final_blue, 255), 255);
//         // colour.r = 255;
//         // colour.g = 255;
//         // colour.b = 255;
//     }
    
//     return colour;
// }


// ------------------ for checkerboard IS WORKING ----------------------------------------
// t_colour get_sphere_checkerboard(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere)
// {

// 	(void)data;
//     double radius = sphere->diameter / 2;
// 	int NUM_SQUARES = 3; // Number of squares per side
//     t_colour colour;
    
//     // Using the 'Phong reflection model'
// 	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));

	
// 	t_vec3		s_normal;
// 	double		x;
// 	double		y;
// 	// double		z;

// 	s_normal = minus(intersection_point, sphere->center);	
// 	s_normal.x = s_normal.x - radius;
// 	s_normal.y = s_normal.y - radius;
// 	// s_normal.z = s_normal.z - intersection_point.z - radius;

// 	x = fabs(s_normal.x) * NUM_SQUARES;
// 	y = fabs(s_normal.y) * NUM_SQUARES;
// 	// z = fabs(s_normal.z);

// 	// x *= z;
// 	// y *= z;
//     // Determine color based on checkerboard pattern
//     if (((fmod(x, radius) <= radius / 2 && fmod(y, radius) <= radius / 2) ||
// 		(fmod(x, radius) > radius / 2 && fmod(y, radius) > radius / 2)))
//     {
// 		// Clamp final values to [0, 255]
//         colour.r = 0;
//         colour.g = 0;
//         colour.b = 0;
//     }
//     else
//     {
//         colour.r = 255;
//         colour.g = 255;
//         colour.b = 255;
//     }
    
//     return colour;
// }


void	print_vector(t_vec3 *vec)
{
	printf("x: %f, y: %f, z: %f\n", vec->x, vec->y, vec->z);
}

// ------------------ for checkerboard IS WORKING ----------------------------------------
t_colour get_sphere_checkerboard(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere)
{
    (void)data;
    // double radius = sphere->diameter / 2;
    int NUM_SQUARES = 10; // Number of squares per side
    t_colour colour;
    
    // Using the 'Phong reflection model'
    t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));

    t_vec3 s_normal;
    double x, y, z;

    s_normal = minus(intersection_point, sphere->center);
	s_normal = normalize_vector(s_normal);
    s_normal.x = s_normal.x + 1;
    s_normal.y = s_normal.y + 1;
    s_normal.z = s_normal.z;

	// print_vector(&s_normal);
    // Normalize the coordinates
    // x = fabs(sphere->center.x - s_normal.x) / (radius * 2);
    // y = fabs(sphere->center.y - s_normal.y) / (radius * 2);
    // z = fabs(sphere->center.z - s_normal.z) / (radius * 2);

	x = s_normal.x / 2;
	y = s_normal.y / 2;
	z = s_normal.z / 2;
	
	// printf("x: %f, y: %f, z: %f\n", x, y, z);
	// print_vector(&sphere->center);
	// exit(0);
    // Calculate the square index for each coordinate
    double square_x = x * NUM_SQUARES;
    double square_y = y * NUM_SQUARES;
    // double square_z = z * NUM_SQUARES;

    bool is_black = false;

	if (fmod(square_x, 2) < 1 && fmod(square_y, 2) < 1)
		is_black = true;
	if (fmod(square_x, 2) >= 1 && fmod(square_y, 2) >= 1)
		is_black = true;
    // Determine if the point belongs to a black or white square

    // Set color based on checkerboard pattern
    if (is_black)
    {
        // Set color to black
        colour.r = 25;
        colour.g = 25;
        colour.b = 150;
    }
    else
    {
        // Set color to white
        colour.r = 255;
        colour.g = 255;
        colour.b = 255;
    }

    return colour;
}





// ------- This is for bumpmap NOT WORKING YET -----------------------
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