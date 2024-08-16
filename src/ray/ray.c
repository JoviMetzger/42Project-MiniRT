/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:59 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/16 21:59:22 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Helper function to scale a vector by a scalar
static	t_vec3	scale_vector(t_vec3 v, double scalar)
{
	t_vec3	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

// Converts a 'double' into a 'vector'.
static t_vec3	init_ray_pos(double pos_x, double pos_y, double pos_z)
{
	t_vec3	vec;

	vec.x = pos_x;
	vec.y = pos_y;
	vec.z = pos_z;
	return (vec);
}

// Function to initialize the ray direction with camera orientation.
static t_vec3	init_vector(t_screen screen, t_camera camera)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	pixel_direction;

	forward = normalize(camera.vector);
	right = normalize(cross_product(init_ray_pos(0, 1, 0), forward));
	up = cross_product(forward, right);
	pixel_direction = plus(plus(scale_vector(right, -screen.pixel_delta_x),
				scale_vector(up, screen.pixel_delta_y)), forward);
	return (normalize(pixel_direction));
}

/*	STEP 1: Calculate the ray from the “eye” through the pixel
 *
 *	This function calculates a ray for each pixel.
 *	How do set-up the ray:
 *		- 1. Set up width, height and image ratio of the window/image.
 *			 image_ratio = image_height / image_width;
 *		- 2. Calculate the viewport, so what you imaginary camera sees.
 *			 viewport_w = 2 * ((pos_x + 0.5) / image_width) - 1;
 *			 viewport_h = (1 - 2 * ((pos_y + 0.5) / image_height)) * image_ratio;
 *		- 3. Calculate each delta pixel.
 *			 M_PI -> This is a constant representing the value of pi.
 *			 pixel_x = viewport_w * (tan((fov / 2) * (M_PI / 180)));
 *			 pixel_y = viewport_h * (tan((fov / 2) * (M_PI / 180)));
 *		- 4. Initialize the ray vector and the ray place.
 */
t_ray	ft_create_ray(t_data *data, int pos_x, int pos_y)
{
	t_ray		ray;
	t_screen	screen;
	double		img_width;
	double		img_height;

	screen = data->screen;
	img_width = data->width;
	img_height = data->height;
	screen.img_ratio = img_height / img_width;
	screen.viewport_w = 2 * ((pos_x + 0.5) / img_width) - 1;
	screen.viewport_h = (1 - 2 * ((pos_y + 0.5)
				/ img_height)) * screen.img_ratio;
	screen.pixel_delta_x = screen.viewport_w * (tan((data->camera.fov / 2)
				* (M_PI / 180)));
	screen.pixel_delta_y = screen.viewport_h * (tan((data->camera.fov / 2)
				* (M_PI / 180)));
	ray.vector = init_vector(screen, data->camera);
	ray.place = data->camera.place;
	return (ray);
}
