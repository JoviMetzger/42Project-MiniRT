#include "../header/miniRT.h"

t_ray ft_create_ray(t_data *data, int x, int y)
{

    // t_ray ray;
    t_screen screen = data->screen;
    
    // 1. Calculate the ray from the “eye” through the pixel,
    // give the screen struct it information;

    screen.viewport_w = 2 * ((x + 0.5) / (double)data->mlx->width) - 1;
    screen.viewport_h = 1 + 2 * ((y + 0.5) / (double)data->mlx->height);
   
    // Formula: image_ratio = width/height 
    screen.img_ratio = (double)data->mlx->width / (double)data->mlx->height;
    
    // - M_PI: This is a constant representing the value of pi.
    // - tan(): This is the tangent function.
    // - fov: field of view
    // Formula:
    //  vector_x = (2 * ((pixel_x + 0.5) / viewport_width) - 1) * ((double)viewport_width / viewport_height) * (tan((fov / 2) * (M_PI / 180)));
    //  vector_y = (1 - 2 * ((pixel_y + 0.5) / viewport_height)) * (tan((fov / 2) * (M_PI / 180)));
    screen.pixel_x = ?;
    screen.pixel_y = ?;

    // 2. Determine which objects the ray intersects, and
    // // give the ray struct it information
    // // need first screen info before we can calculate the ray info
    ray.place = ;
    ray.vector = ;
    return (ray); // return the ray struct
}



// // ------------------- SOME TESTING ---------------------------
// static uint32_t	pythagoras(t_data *data, double x, double y)
// {
// 	double	mid_x = (double)data->mlx->width / 2;
// 	double	mid_y = (double)data->mlx->height / 2;
// 	double	a_len;
// 	double	b_len;

// 	a_len = fabs(x - mid_x);
// 	b_len = fabs(y - mid_y);
// 	return ((uint32_t)sqrt(a_len * a_len + b_len * b_len));
// }

// #define RADIUS 450

// void ft_testing(t_data *data, uint32_t x, uint32_t y)
// {
//     if (pythagoras(data, (double)x, (double)y) <= RADIUS)
//         mlx_put_pixel(data->image, x, y, ft_pixel(10, 0, 255));
//     else 
//         mlx_put_pixel(data->image, x, y, ft_pixel(0, 0, 0));
// }
// // ------------------------------------------------------------