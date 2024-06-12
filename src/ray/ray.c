/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:59 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/12 17:04:57 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

//	Assign pixels to the position of the ray-vector .
static t_vec3	init_ray_pos(double pos_x, double pos_y, double pos_z)
{
	t_vec3	vec;

	vec.x = pos_x;
	vec.y = pos_y;
	vec.z = pos_z;
	return (vec);
}

//	Altough we need the ray-vector, 
//	we assign x,y,z the pixel_x-y-z as the ray-vector;
static t_vec3	init_vector(t_screen screen)
{
	return (normalize(init_ray_pos(screen.pixel_delta_x,
				screen.pixel_delta_y, -1)));
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
	img_width = data->width; // change from data->mlx-> since not init window yet
	img_height = data->height;
	screen.img_ratio = img_height / img_width;
	screen.viewport_w = 2 * ((pos_x + 0.5) / img_width) - 1;
	screen.viewport_h = (1 - 2 * ((pos_y + 0.5)
				/ img_height)) * screen.img_ratio;
	screen.pixel_delta_x = screen.viewport_w * (tan((data->camera.fov / 2)
				* (M_PI / 180)));
	screen.pixel_delta_y = screen.viewport_h * (tan((data->camera.fov / 2)
				* (M_PI / 180)));
	ray.vector = init_vector(screen);
	ray.place = data->camera.place;
	return (ray);
}
