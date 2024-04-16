/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:59 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/16 21:20:28 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// 
// 1. Calculate the ray from the “eye” through the pixel,
// image_ratio = image_height / image_width
// ---
//  viewport_w = 2 * ((pos_x + 0.5) / image_width) - 1;
//  viewport_h = (1 - 2 * ((pos_y + 0.5) / image_height)) * image_ratio;
// ---
// M_PI: This is a constant representing the value of pi.
// pixel_x = viewport_w * (tan((fov / 2) * (M_PI / 180)));
// pixel_y = viewport_h * (tan((fov / 2) * (M_PI / 180)));
t_ray ft_create_ray(t_data *data, int pos_x, int pos_y)
{
    t_ray ray;
    t_screen screen = data->screen;

    double img_width = data->mlx->width;
    double img_height = data->mlx->height;
    screen.img_ratio = img_height / img_width;

    screen.viewport_w = 2 * ((pos_x + 0.5) / img_width) - 1;
    screen.viewport_h = (1 - 2 * ((pos_y + 0.5) / img_height)) * screen.img_ratio;
    
    screen.pixel_delta_x = screen.viewport_w * (tan((data->camera.fov / 2) * (M_PI / 180)));
    screen.pixel_delta_y = screen.viewport_h * (tan((data->camera.fov / 2) * (M_PI / 180)));

    ray.vector = init_vector(screen);
    ray.place = data->camera.place;

    return (ray);
}
