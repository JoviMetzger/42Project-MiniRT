/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:59 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/27 13:55:02 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// 
// 1. Calculate the ray from the “eye” through the pixel,
// image_ratio = image_width / image_height 
// ---
//  viewport_w = 2 * ((pos_x + 0.5) / image_width) - 1;
//  viewport_h = 1 - 2 * ((pos_y + 0.5) / image_height);
// ---
// M_PI: This is a constant representing the value of pi.
// pixel_x = viewport_w * image_ratio * (tan((fov / 2) * (M_PI / 180)));
// pixel_y = viewport_h * (tan((fov / 2) * (M_PI / 180)));
// ---
// need first screen info before we can calculate the ray info
t_ray ft_create_ray(t_data *data, int pos_x, int pos_y)
{
    t_ray ray;
    t_screen screen = data->screen;

    double img_width = data->mlx->width;
    double img_height = data->mlx->height;
    screen.img_ratio = img_width / img_height;

    screen.viewport_w = 2 * ((pos_x + 0.5) / img_width) - 1;
    screen.viewport_h = 1 - 2 * ((pos_y + 0.5) / img_height);
    
    screen.pixel_delata_x = screen.viewport_w * screen.img_ratio * (tan((data->camera.FOV / 2) * (M_PI / 180)));
    screen.pixel_delata_y = screen.viewport_h * (tan((data->camera.FOV / 2) * (M_PI / 180)));

    // Using a 4x4 matrix to represent the transformation from camera space to world space.
    store_ray_matrix(data);

    ray.vector = init_vector(data, screen);
    ray.place = data->camera.place;

    return (ray);
}
