#include "../header/miniRT.h"

t_ray ft_create_ray(t_data *data, int pos_x, int pos_y)
{
    t_ray ray;
    t_screen screen = data->screen;

    double img_width = data->mlx->width;
    double img_height = data->mlx->height;
    // 1. Calculate the ray from the “eye” through the pixel,
    // give the screen struct it information;

    // image_ratio = window_width / window_height 
    screen.img_ratio = img_width / img_height;

    //  viewport_w = 2 * ((pos_x + 0.5) / window_width) - 1;
    //  viewport_h = 1 - 2 * ((pos_y + 0.5) / window_height);
    screen.viewport_w = 2 * ((pos_x + 0.5) / img_width) - 1;
    screen.viewport_h = 1 - 2 * ((pos_y + 0.5) / img_height);
    
    screen.total_pixel_num = img_height * img_height; // might not need this
    
    // M_PI: This is a constant representing the value of pi.
    // pixel_x = viewport_w * image_ratio * tan((fov / 2) * (M_PI / 180));
    // pixel_y = viewport_h * (tan((fov / 2) * (M_PI / 180)));
    screen.pixel_delata_x = screen.viewport_w * screen.img_ratio * tan((data->camera.FOV / 2) * (M_PI / 180));
    screen.pixel_delata_y = screen.viewport_h * tan((data->camera.FOV / 2) * (M_PI / 180));

    // store the rays in a 'matrix' -> basiclly ctreating 'fake' rays so we can hit the opjects
    store_ray_matrix(data);
    // 2. Determine which objects the ray intersects, and
    // // give the ray struct it information
    // // need first screen info before we can calculate the ray info
    ray.place = data->camera.place;  // ray.place = {data->camera.place.x, data->camera.place.y, data->camera.place.z};
    ray.vector = init_vector(data, screen);
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