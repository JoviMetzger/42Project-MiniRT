/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:06:08 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/22 21:06:39 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// 1. Calculate the ray from the “eye” through the pixel,	 -> ft_create_ray();
// 2. Determine which objects the ray intersects, and
// 3. Compute a color for the closest intersection point.	 -> ft_calculate_colour();
void ft_put_image(t_data *data)
{
	t_ray ray;
	t_obj_data obj_data; // maybe we don't need this. -> can add "a,b,c,d,root1,root2,t" in objs struct
	uint32_t colour;
	int y = 0;
	int x = 0;

	while (y < data->mlx->height)
	{
		while (x < data->mlx->width)
		{ 
			data->mouse.mouse_map[y][x] = -1;
			ray = ft_create_ray(data, x ,y);		
			colour = ft_calculate_colour(data, &obj_data, ray);
			mlx_put_pixel(data->image, x, y, colour);
			data->mouse.mouse_x = x;
			x++;
		}
		x = 0;
		data->mouse.mouse_y = y;
		y++;
	}
}

void ft_render(t_data *data)
{
	ft_put_image(data); // Shazam(MATH)
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data); // movement aka ESC
    mlx_mouse_hook(data->mlx, ft_handle_mouse_click, data); // Mouse click event // NOT working   
}
