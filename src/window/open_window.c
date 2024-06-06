/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_window.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:51 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/06 15:37:47 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"
#include "../../header/parser.h"

//	This function does the correct error handling 
//	for that specific allocation that vent wrong.
//		- num 1 -> data->mlx = mlx_init(); error handeling.
//		- num 2 -> data->image = mlx_new_image(); error handeling.
//		- num 3 -> data->mouse.highlight_img = mlx_new_image(); error handeling.
//		- num 4 -> data->mlx = mlx_image_to_window(); error handeling.
static void	ft_error_handler(int num, t_data *data)
{
	if (num == 1)
	{
		free_objects(data);
		error_msg("Failed to set up the connection.");
	}
	if (num == 2)
	{
		mlx_close_window(data->mlx);
		free_objects(data);
		error_msg("Failed to create a new image.");
	}
	if (num == 3)
	{
		mlx_close_window(data->mlx);
		error_msg("Failed to create a new image.");
	}
	if (num == 4)
	{
		mlx_close_window(data->mlx);
		free_objects(data);
		error_msg("Failed to create a new window.");
	}
}

//	Initializes the window and everything else from MLX.
//		- mlx_set_setting(MLX_STRETCH_IMAGE, 1); Is for stretching img/window.
//		- If something goes wrong with the initializing it will be freed, 
//		  aswell at the structs that got already allocated. 
//		  And a error message will be displayed.
void	ft_open_window(t_data *data)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	data->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1);
	if (!data->mlx)
	{
		ft_error_handler(1, data);
	}
	data->image = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	if (!data->image)
	{
		ft_error_handler(2, data);
	}
	data->mouse.highlight_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->mouse.highlight_img == NULL)
	{
		ft_error_handler(3, data);
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		ft_error_handler(4, data);
	}
}
