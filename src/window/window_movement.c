/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/23 17:13:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Handle key commands
void ft_key_action(mlx_key_data_t keydata, t_data *data)
{
	(void)keydata;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

// Handle mouse click
// static void	highlight_object(t_data *data, int16_t num)
// {
// 	uint32_t	x;
// 	uint32_t	y;

// 	y = 0;
// 	while (y < data->mouse.window_h)
// 	{
// 		x = 0;
// 		while (x < data->mouse.window_w)
// 		{
// 			if (data->mouse.mouse_map[y][x] != num)
// 			{
// 				if (x < data->mouse.window_w - 2 && data->mouse.mouse_map[y][x + 2] == num)
// 				{
// 					data->mouse.mouse_map[y][x] = -2;
// 					mlx_put_pixel(data->image, x, y, 0xFFFFFFFF);
// 				}
// 				if (x > 1 && data->mouse.mouse_map[y][x - 2] == num)
// 				{
// 					data->mouse.mouse_map[y][x] = -2;
// 					mlx_put_pixel(data->image, x, y, 0xFFFFFFFF);
// 				}
// 				if (y < data->mouse.window_h - 2 && data->mouse.mouse_map[y + 2][x] == num)
// 				{
// 					data->mouse.mouse_map[y][x] = -2;
// 					mlx_put_pixel(data->image, x, y, 0xFFFFFFFF);
// 				}
// 				if (y > 1 && data->mouse.mouse_map[y - 2][x] == num)
// 				{
// 					data->mouse.mouse_map[y][x] = -2;
// 					mlx_put_pixel(data->image, x, y, 0xFFFFFFFF);
// 				}
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }


// void  ft_handle_mouse_click(mouse_key_t key, action_t act, modifier_key_t m, void *p) 
// {
// 	t_data		*data;
// 	static int16_t	selected = -1;
// 	int32_t		x;
// 	int32_t		y;

// 	(void)m;
// 	data = (t_data *)p;
// 	if (key == MLX_MOUSE_BUTTON_LEFT && act == MLX_RELEASE)
// 	{
// 		mlx_get_mouse_pos(data->mlx, &x, &y);
// 		if (data->mouse.mouse_map[y][x] != -1 && data->mouse.mouse_map[y][x] != selected)
// 		{
// 			if (selected != -1)
// 				ft_put_image(data);
// 			selected = data->mouse.mouse_map[y][x];
// 			highlight_object(data, selected);
// 		}
// 		else
// 		{
// 			ft_put_image(data);
// 			selected = -1;
// 		}
// 	}
// }
