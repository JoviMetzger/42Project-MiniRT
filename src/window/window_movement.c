/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/25 15:36:13 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Handle key commands
void ft_key_action(mlx_key_data_t keydata, t_data *data)
{
	(void)keydata;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (data->mouse.selected == true && mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		// printf("What am I: %d\n", data->mouse.loop_obj_colour);	
		data->mouse.loop_obj_colour = true;
		ft_put_image(data);
		printf("UP\n");
	}
}

// Handle mouse click
static void	highlight_object(t_data *data, int16_t num)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	if (data->mouse.selected == false)
	{
		data->mouse.selected = true;
		while (y < data->mouse.window_h)
		{
			x = 0;
			while (x < data->mouse.window_w)
			{
				if (data->mouse.mouse_map[y][x] != num)
				{
					if (x < data->mouse.window_w - 2 && data->mouse.mouse_map[y][x + 2] == num)
						mlx_put_pixel(data->mouse.highlight_img, x, y, ft_convert_rgb(255, 255, 255));
					if (x > 1 && data->mouse.mouse_map[y][x - 2] == num)
						mlx_put_pixel(data->mouse.highlight_img, x, y, ft_convert_rgb(255, 255, 255));
					if (y < data->mouse.window_h - 2 && data->mouse.mouse_map[y + 2][x] == num)
						mlx_put_pixel(data->mouse.highlight_img, x, y, ft_convert_rgb(255, 255, 255));
					if (y > 1 && data->mouse.mouse_map[y - 2][x] == num)
						mlx_put_pixel(data->mouse.highlight_img, x, y, ft_convert_rgb(255, 255, 255));
				}
				x++;
			}
			y++;
		}
	}
	else
	{
		data->mouse.selected = false;
		while (y < data->mouse.window_h)
		{
			x = 0;
			while (x < data->mouse.window_w)
			{
				mlx_put_pixel(data->mouse.highlight_img, x, y, 0);
				x++;
			}
			y++;
		}
	}
	mlx_image_to_window(data->mlx, data->mouse.highlight_img, 0, 0);
}

void  ft_handle_mouse_click(mouse_key_t key, action_t act, modifier_key_t m, void *_data) 
{
	t_data		*data;
	int32_t		x;
	int32_t		y;

	(void)m;
	data = (t_data *)_data;
	if (key == MLX_MOUSE_BUTTON_LEFT && act == MLX_RELEASE)
	{
		mlx_get_mouse_pos(data->mlx, &x, &y);
		if (data->mouse.mouse_map[y][x] == -1)
			printf("VinnyMove #Github Soepgroente\n");
		else
			highlight_object(data, data->mouse.mouse_map[y][x]);
	}
}
