/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_colour.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/17 18:56:47 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Initializing the t_colour_vars struct.
static t_colour_vars init_colour(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere)
{
	t_colour_vars	colour;
	colour.ambient_ratio = data->ambient.ratio;
	colour.specular_intensity = 0.2;
	colour.specular_power = 32;

    // Using the 'Phong reflection model'
    colour.intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));
    colour.normal = normalize_vector(minus(colour.intersection_point, sphere->center));

    // Ambient light contribution
    colour.ambient_red = colour.ambient_ratio * data->ambient.colour.r;
    colour.ambient_green = colour.ambient_ratio * data->ambient.colour.g;
    colour.ambient_blue = colour.ambient_ratio * data->ambient.colour.b;

    // Initialize result color with ambient light contribution
    colour.result.r = colour.ambient_red;
    colour.result.g = colour.ambient_green;
    colour.result.b = colour.ambient_blue;
	return colour;
}

static void diffuse_light(t_colour_vars *colour)
{
	colour->diffuse_factor = dot_product(colour->normal, colour->light_direction);
	if (colour->diffuse_factor < 0.0) 
		colour->diffuse_factor = 0.0;
	colour->diffuse_red = colour->current_light->ratio * colour->diffuse_factor * colour->current_light->colour.r;
	colour->diffuse_green = colour->current_light->ratio * colour->diffuse_factor * colour->current_light->colour.g;
	colour->diffuse_blue = colour->current_light->ratio * colour->diffuse_factor * colour->current_light->colour.b;
}

static void specular_light(t_colour_vars *colour, t_ray ray)
{
	colour->view_direction = normalize_vector(minus(ray.place, colour->intersection_point));
	colour->reflection_direction = normalize_vector(ft_reflect(colour->light_direction, colour->normal));
	colour->specular_factor = pow(dot_product(colour->reflection_direction, colour->view_direction), colour->specular_power);
	if (colour->specular_factor < 0.0) 
		colour->specular_factor = 0.0;
	colour->specular_red = colour->specular_intensity * colour->specular_factor * colour->current_light->colour.r;
	colour->specular_green = colour->specular_intensity * colour->specular_factor * colour->current_light->colour.g;
	colour->specular_blue = colour->specular_intensity * colour->specular_factor * colour->current_light->colour.b;
}

// calculation of the light_ray and if it hits a object, it should not gp trough the object, so that it gives a shadow
static void shadow_calculation(t_data *data, t_colour_vars *colour, t_ray ray, t_obj_data *obj_data)
{
	t_ray	shadow_ray;
	bool 	in_shadow;
	int 	i;
	
	in_shadow = false;
	i = 0;

	// Shadow ray
	colour->light_direction = normalize_vector(minus(colour->current_light->place, colour->intersection_point));
	shadow_ray.place = plus(colour->intersection_point, mult_vecdub(colour->normal, EPSILON)); // Add small offset to avoid self-intersection

	// check if the light_ray hits an object
	while (++i < data->objs_i) 
	{
		if (intersect_sphere(&shadow_ray, data->objs[i], obj_data) 
			|| intersect_plane(&shadow_ray, data->objs[i], obj_data) 
			|| intersect_cylinder(&shadow_ray, data->objs[i], obj_data)) 
			in_shadow = true;
	}
	if (!in_shadow) 
	{
		diffuse_light(colour);		 // Diffuse light contribution
		specular_light(colour, ray); // Specular light contribution

		// Add the contributions from this light to the colour.result
		colour->result.r += colour->diffuse_red + colour->specular_red;
		colour->result.g += colour->diffuse_green + colour->specular_green;
		colour->result.b += colour->diffuse_blue + colour->specular_blue;
	}
}

// Function to check if a point is shadowed by any object in the scene
t_colour get_sphere_colour(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere) 
{
	t_colour_vars	colour;
	int 			i;
	
	colour = init_colour(data, obj_data, ray, sphere);
	i = 0;
    while (i < data->lights_i) 
	{
		colour.current_light = data->lightS[i];
		shadow_calculation(data, &colour, ray, obj_data);
		i++;
    }

    // Clamp final values to [0, 255] and apply the object's base color
    colour.result.r = fmin(colour.result.r * sphere->colour.r / 255, 255.0);
    colour.result.g = fmin(colour.result.g * sphere->colour.g / 255, 255.0);
    colour.result.b = fmin(colour.result.b * sphere->colour.b / 255, 255.0);

    return colour.result;    
}



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

// // ------------------ for checkerboard IS WORKING ----------------------------------------
// t_colour get_sphere_checkerboard(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere)
// {
//     (void)data;
//     // double radius = sphere->diameter / 2;
//     int NUM_SQUARES = 10; // Number of squares per side
//     t_colour colour;
    
//     // Using the 'Phong reflection model'
//     t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));

//     t_vec3 s_normal;
//     double x, y, z;

//     s_normal = minus(intersection_point, sphere->center);
// 	s_normal = normalize_vector(s_normal);
//     s_normal.x = s_normal.x + 1;
//     s_normal.y = s_normal.y + 1;
//     s_normal.z = s_normal.z;

// 	// print_vector(&s_normal);
//     // Normalize the coordinates
//     // x = fabs(sphere->center.x - s_normal.x) / (radius * 2);
//     // y = fabs(sphere->center.y - s_normal.y) / (radius * 2);
//     // z = fabs(sphere->center.z - s_normal.z) / (radius * 2);

// 	x = s_normal.x / 2;
// 	y = s_normal.y / 2;
// 	z = s_normal.z / 2;
	
// 	// printf("x: %f, y: %f, z: %f\n", x, y, z);
// 	// print_vector(&sphere->center);
// 	// exit(0);
//     // Calculate the square index for each coordinate
//     double square_x = x * NUM_SQUARES;
//     double square_y = y * NUM_SQUARES;
//     // double square_z = z * NUM_SQUARES;

//     bool is_black = false;

// 	if (fmod(square_x, 2) < 1 && fmod(square_y, 2) < 1)
// 		is_black = true;
// 	if (fmod(square_x, 2) >= 1 && fmod(square_y, 2) >= 1)
// 		is_black = true;
//     // Determine if the point belongs to a black or white square

//     // Set color based on checkerboard pattern
//     if (is_black)
//     {
//         // Set color to black
//         colour.r = 25;
//         colour.g = 25;
//         colour.b = 150;
//     }
//     else
//     {
//         // Set color to white
//         colour.r = 255;
//         colour.g = 255;
//         colour.b = 255;
//     }

//     return colour;
// }

// Initializing the t_colour_vars struct.
t_colour_vars C_init_colour(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere)
{
	t_colour_vars	colour;
	colour.ambient_ratio = data->ambient.ratio;
	colour.specular_intensity = 0.2;
	colour.specular_power = 32;

    // Using the 'Phong reflection model'
    colour.intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));
    colour.normal = normalize_vector(minus(colour.intersection_point, sphere->center));

    // Ambient light contribution
    colour.ambient_red = colour.ambient_ratio * data->ambient.colour.r;
    colour.ambient_green = colour.ambient_ratio * data->ambient.colour.g;
    colour.ambient_blue = colour.ambient_ratio * data->ambient.colour.b;

    // Initialize result color with ambient light contribution
    colour.result.r = colour.ambient_red;
    colour.result.g = colour.ambient_green;
    colour.result.b = colour.ambient_blue;
	return colour;
}

void C_diffuse_light(t_colour_vars *colour)
{
	colour->diffuse_factor = dot_product(colour->normal, colour->light_direction);
	if (colour->diffuse_factor < 0.0) 
		colour->diffuse_factor = 0.0;
	colour->diffuse_red = colour->current_light->ratio * colour->diffuse_factor * colour->current_light->colour.r;
	colour->diffuse_green = colour->current_light->ratio * colour->diffuse_factor * colour->current_light->colour.g;
	colour->diffuse_blue = colour->current_light->ratio * colour->diffuse_factor * colour->current_light->colour.b;
}

void C_specular_light(t_colour_vars *colour, t_ray ray)
{
	colour->view_direction = normalize_vector(minus(ray.place, colour->intersection_point));
	colour->reflection_direction = normalize_vector(ft_reflect(colour->light_direction, colour->normal));
	colour->specular_factor = pow(dot_product(colour->reflection_direction, colour->view_direction), colour->specular_power);
	if (colour->specular_factor < 0.0) 
		colour->specular_factor = 0.0;
	colour->specular_red = colour->specular_intensity * colour->specular_factor * colour->current_light->colour.r;
	colour->specular_green = colour->specular_intensity * colour->specular_factor * colour->current_light->colour.g;
	colour->specular_blue = colour->specular_intensity * colour->specular_factor * colour->current_light->colour.b;
}

// calculation of the light_ray and if it hits a object, it should not gp trough the object, so that it gives a shadow
void C_shadow_calculation(t_data *data, t_colour_vars *colour, t_ray ray, t_obj_data *obj_data)
{
	t_ray	shadow_ray;
	bool 	in_shadow;
	int 	i;
	
	in_shadow = false;
	i = 0;

	// Shadow ray
	colour->light_direction = normalize_vector(minus(colour->current_light->place, colour->intersection_point));
	shadow_ray.place = plus(colour->intersection_point, mult_vecdub(colour->normal, EPSILON)); // Add small offset to avoid self-intersection

	// check if the light_ray hits an object
	while (++i < data->objs_i) 
	{
		if (intersect_sphere(&shadow_ray, data->objs[i], obj_data) 
			|| intersect_plane(&shadow_ray, data->objs[i], obj_data) 
			|| intersect_cylinder(&shadow_ray, data->objs[i], obj_data)) 
			in_shadow = true;
	}
	if (!in_shadow) 
	{
		C_diffuse_light(colour);		 // Diffuse light contribution
		C_specular_light(colour, ray); // Specular light contribution

		// Add the contributions from this light to the colour.result
		colour->result.r += colour->diffuse_red + colour->specular_red;
		colour->result.g += colour->diffuse_green + colour->specular_green;
		colour->result.b += colour->diffuse_blue + colour->specular_blue;
	}
}

// Function to check if a point is shadowed by any object in the scene
t_colour C_get_sphere_colour(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere) 
{
	t_colour_vars	colour;
	int 			i;
	
	colour = init_colour(data, obj_data, ray, sphere);
	i = 0;
    while (i < data->lights_i) 
	{
		colour.current_light = data->lightS[i];
		shadow_calculation(data, &colour, ray, obj_data);
		i++;
    }

    // Clamp final values to [0, 255] and apply the object's base color
    colour.result.r = fmin(colour.result.r * sphere->colour.r / 255, 255.0);
    colour.result.g = fmin(colour.result.g * sphere->colour.g / 255, 255.0);
    colour.result.b = fmin(colour.result.b * sphere->colour.b / 255, 255.0);

    return colour.result;    
}

t_colour get_sphere_checkerboard(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere)
{
    (void)data;
    int NUM_SQUARES = 10; // Number of squares per side
    t_colour colour;
    t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));
    t_vec3 s_normal = normalize_vector(minus(intersection_point, sphere->center));
	colour = C_get_sphere_colour(data, obj_data, ray, sphere);
    
    // Convert Cartesian to spherical coordinates
    double theta = atan2(s_normal.z, s_normal.x); // Angle in the x-y plane
    double phi = acos(s_normal.y);                // Angle from the positive z-axis
    
    // Normalize theta and phi to [0, 1]
    double u = (theta + M_PI) / (2 * M_PI); // Theta ranges from -pi to pi
    double v = phi / M_PI;                  // Phi ranges from 0 to pi
    
    // Scale coordinates by number of squares
    double square_u = u * NUM_SQUARES;
    double square_v = v * NUM_SQUARES;
    
    // Determine color based on checkerboard pattern
    bool is_black = ((int)floor(square_u) % 2 == (int)floor(square_v) % 2);
    
    if (is_black) 
	{
        colour.r += 0;
        colour.g += 0;
        colour.b += 0;
    } 
	else 
	{
        colour.r += 255;
        colour.g += 255;
        colour.b += 255;
    }
    
    return colour;
}