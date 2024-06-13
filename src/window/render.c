/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:06:08 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/13 13:45:02 by jmetzger      ########   odam.nl         */
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
// void	ft_put_image(t_data *data)
// {
// 	t_hit_data	obj_hit;
// 	uint32_t	colour;
// 	int			y;
// 	int			x;

// 	y = 0;
// 	x = 0;
// 	while (y < data->mlx->height)
// 	{
// 		while (x < data->mlx->width)
// 		{
// 			data->mouse.mouse_map[y][x] = -1;
// 			data->ray = ft_create_ray(data, x ,y);
// 			colour = ft_calculate_colour(data, &obj_hit); // move to a loop where pixels are saved, give put func the pixels here
// 			mlx_put_pixel(data->image, x, y, colour);
// 			data->mouse.mou_x = x;
// 			x++;
// 		}
// 		data->mouse.mou_y = y;
// 		x = 0;
// 		y++;
// 	}
// }

/*	This function is the main loop.
 *		- It loops through each pixel and saves all pixel inforamtion in a struct.
 *		- There are 3 main steps happening:
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
	data->pix_i = 0;
	while (data->pix_i < data->total_pix)
	{
		data->mouse.mouse_map[data->pix[data->pix_i]->y][data->pix[data->pix_i]->x] = -1;
		mlx_put_pixel(data->image, data->pix[data->pix_i]->x, data->pix[data->pix_i]->y, data->pix[data->pix_i]->colour);
		data->mouse.mou_x = data->pix[data->pix_i]->x;
		data->pix_i++;
	}
	// puts("DONEE");
}

// static void	check_pix(t_data *data)
// {
// 	int p = 0;

// 	while (p < data->total_pix)
// 	{
// 	 	printf("pix[%i] = %i %i  ", p, data->pix[p]->x, data->pix[p]->y);
// 		printf("pix colour = %d\n", data->pix[p]->colour);
// 		p++;
// 	}
// }


/*	In this function the Shazam is happening.
 *	- ft_put_image(); 	-> is the loop that goes pixel by pixel and shoots rays.
 *	- mlx_key_hook(); 	-> is for key movement (ESC, Arrow up).
 *	- mlx_mouse_hook(); -> is for mouse movement (selcet objects). 
 */
void	ft_render(t_data *data)
{
	// check_pix(data);
	// exit(0);
	ft_put_image(data);
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data);
	mlx_mouse_hook(data->mlx, ft_handle_mouse_click, data);
}
