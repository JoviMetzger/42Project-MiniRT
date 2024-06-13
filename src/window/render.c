/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:06:08 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/10 15:40:24 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/*	Bit shifts the ints rg,b, 
 *	so that the correct colour is displayed into mlx_put_pixel();
 */
int32_t	ft_convert_rgb(int32_t r, int32_t g, int32_t b)
{
	int32_t	a;

	a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}

/*	This function is the main loop.
 *		- It loops through each pixel and takes these steps for each pixel.
 *		- STEPS:
 *			- 1. Calculate the ray from the “eye” through the pixel, 
 *				 -> ft_create_ray();
 *			- 2. Determine which objects the ray intersects,		 
 *				 -> ft_calculate_colour();
 *			- 3. Compute a color for the closest intersection point. 
 *				 -> get_colour();
 *		- It aswell updates all necessary varabils.  
 */
void	ft_put_image(t_data *data)
{
	t_hit_data	obj_hit;
	uint32_t	colour;
	int			y;
	int			x;

	y = 0;
	x = 0;
	while (y < data->mlx->height)
	{
		while (x < data->mlx->width)
		{
			data->mouse.mouse_map[y][x] = -1;
			data->ray = ft_create_ray(data, x, y);
			colour = ft_calculate_colour(data, &obj_hit);
			mlx_put_pixel(data->image, x, y, colour);
			data->mouse.mou_x = x;
			x++;
		}
		data->mouse.mou_y = y;
		x = 0;
		y++;
	}
}

/*	In this function the Shazam is happening.
 *	- ft_put_image(); 	-> is the loop that goes pixel by pixel and shoots rays.
 *	- mlx_key_hook(); 	-> is for key movement (ESC, Arrow up).
 *	- mlx_mouse_hook(); -> is for mouse movement (selcet objects). 
 */
void	ft_render(t_data *data)
{
	ft_put_image(data);
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data);
	mlx_mouse_hook(data->mlx, ft_handle_mouse_click, data);
}
