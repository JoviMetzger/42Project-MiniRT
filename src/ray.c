/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:59 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 16:06:01 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/miniRT.h"

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
// 2. Determine which objects the ray intersects, and
// // give the ray struct it information
// // need first screen info before we can calculate the ray info
t_ray ft_create_ray(t_data *data, int pos_x, int pos_y)
{
    t_ray ray;
    // t_ray lightray;
    t_screen screen = data->screen;

    double img_width = data->mlx->width;
    double img_height = data->mlx->height;
    screen.img_ratio = img_width / img_height;

    screen.viewport_w = 2 * ((pos_x + 0.5) / img_width) - 1;
    screen.viewport_h = 1 - 2 * ((pos_y + 0.5) / img_height);
    
    // screen.total_pixel_num = img_height * img_height; // might not need this
    
    screen.pixel_delata_x = screen.viewport_w * screen.img_ratio * (tan((data->camera.FOV / 2) * (M_PI / 180)));
    screen.pixel_delata_y = screen.viewport_h * (tan((data->camera.FOV / 2) * (M_PI / 180)));

    // store the rays in a 'matrix' -> basiclly ctreating 'fake' rays so we can hit the opjects
    store_ray_matrix(data);

    ray.vector = init_vector(data, screen);
    ray.place = data->camera.place;  // ray.place = {data->camera.place.x, data->camera.place.y, data->camera.place.z};

    // Don't know if this can be done here or if this should be done when we init and calculate the colour.
    // In my mind it makes sense to keep all the ray stuff together, but I am open for moving it ;D
    // ft_create_lightray(data, &lightray); // Init & creating the lightray -> Still need TO CREATE THIS!!!!!

    return (ray); // return the ray struct
}
