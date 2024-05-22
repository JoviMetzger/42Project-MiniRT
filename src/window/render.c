/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:06:08 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/22 14:19:26 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

void ft_put_image(t_data *data)
{
	t_ray			ray;
	t_hit_data		hit_data;
	uint32_t		colour;
	int y = 0;
	int x = 0;

	while (x < data->mlx->width)
	{
		while (y < data->mlx->height)
		{ 
			ray = ft_create_ray(data, x ,y);
			colour = ft_calculate_colour(data, &hit_data, ray);
			y++;
		}
		y = 0;
		x++;
	}
}

// 1. Calculate the ray from the “eye” through the pixel,	 -> ft_create_ray();
// 2. Determine which objects the ray intersects,			 -> ft_create_intersecttions();
// 3. Compute a color for the closest intersection point.	 -> ft_calculate_colour();
// void ft_put_image(t_data *data)
// {
// 	t_ray		ray;
// 	t_hit_data	hit_data;
// 	uint32_t	colour;
// 	int y = 0;
// 	int x = 0;

// 	while (y < data->mlx->height)
// 	{
// 		while (x < data->mlx->width)
// 		{ 
// 			// data->mouse.mouse_map[y][x] = -1;
// 			ray = ft_create_ray(data, x ,y);		
// 			colour = ft_calculate_colour(data, &hit_data, ray);
// 			mlx_put_pixel(data->image, x, y, colour);
// 			// data->mouse.mouse_x = x;
// 			x++;
// 		}
// 		x = 0;
// 		// data->mouse.mouse_y = y;
// 		y++;
// 	}
// }

static void	ft_resize(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->mlx->width = width;
	data->mlx->height = height;
}

void ft_render(t_data *data)
{

	ft_put_image(data); // Shazam(MATH)
	
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data); // movement aka ESC
	// mlx_loop_hook(data->mlx, ft_handle_mouse_move, data); // Mouse move event
    // mlx_mouse_hook(data->mlx, (mlx_mousefunc) handle_mouse_click, data); // Mouse click event
    mlx_resize_hook(data->mlx, &ft_resize, (void *)data); // resize window
    // mlx_resize_hook(data->mlx, (mlx_resizefunc)ft_resize, data); // resize window
    // mlx_mouse_hook(data->mlx, ft_handle_mouse_click, data); // Mouse click event // NOT working   
}
