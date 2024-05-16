/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_window.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:51 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/16 20:36:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"
#include "../../header/parser.h"

// gotta free objects here since error_msg() exits
void ft_open_window(t_data *data)
{
	// Gotta error check this stuff
	mlx_set_setting(MLX_STRETCH_IMAGE, 1); // For stretching image
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1)))
	{
		free_objects(data);
		error_msg("Failed to set up the connection.");
	}
	if (!(data->image = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height)))
	{
		mlx_close_window(data->mlx);
		free_objects(data);
		error_msg("Failed to create a new image.");
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		free_objects(data);
		error_msg("Failed to create a new window.");
	}
}
