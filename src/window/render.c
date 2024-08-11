/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:06:08 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/11 19:34:13 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/*	Bit shifts the ints r,g,b, 
 *	so that the correct colour is displayed into mlx_put_pixel();
 */
int32_t	ft_convert_rgb(int32_t r, int32_t g, int32_t b)
{
	int32_t	a;

	a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}

/*	This function loops through all pixels and prints it on the screen.  
 */
void	ft_put_image(t_data *data)
{
	data->pix_i = 0;
	while (data->pix_i < data->total_pix)
	{
		mlx_put_pixel(data->image, data->pix[data->pix_i]->x,
			data->pix[data->pix_i]->y, data->pix[data->pix_i]->colour);
		data->pix_i++;
	}
	puts("DONEE"); // dont forget to remove...
}

/*	In this function renders and executes keys/mouse movement.
 *	- ft_put_image(); 	-> prints the pixel.
 *	- mlx_key_hook(); 	-> is for key movement (ESC, Arrow up).
 *	- mlx_mouse_hook(); -> is for mouse movement (selcet objects). 
 */
void	ft_render(t_data *data)
{
	ft_put_image(data);
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data);
	mlx_mouse_hook(data->mlx, ft_handle_mouse_click, data);
}
