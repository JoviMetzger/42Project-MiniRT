/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/29 19:34:01 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// static void ft_get_ret(t_obj_data *obj_data, t_colour colour)
// {
// 	if (obj_data->closest_t != DBL_MAX)
// 		return (ft_convert_rgb(colour.r, colour.g, colour.b));
// 	else
// 		return (ft_convert_rgb(0, 0, 0)); // No intersection found, return black
// }

void new_sphere_pattern(t_data *data, t_objs *obj)
{
	(void)data;
	if (obj->i == 1)
	{
		printf("CHECKERBOARD\n");
		// if (intersect_sphere(&ray, data->objs[data->i_am], obj_data))
		// {		
		// 	ft_get_ret(obj_data, get_sphere_checkerboard(data, obj_data, ray, data->objs[data->i_am]));
		// }
		// colour = get_sphere_checkerboard(data, obj_data, ray, data->objs[data->i_am]);
	}
	else if (obj->i == 2)
	{
		printf("OTHER\n");
		// colour = get_sphere_bumpmap(data, obj_data, ray, data->objs[i]);	// will be moved
	}
	else
		printf("NORMAL\n");
}

void what_obj_me(t_data *data, t_objs *obj)
{
	if (obj->type == 5)
		new_sphere_pattern(data, data->objs[data->i_am]);
	else if (obj->type == 4)
	{
		printf("new_plane_pattern -> NOT WORKING YET\n");
		// new_plane_pattern(data, data->objs[data->i_am]);
	}
	else if (obj->type == 6)
	{
		printf("new_cylinder_pattern -> NOT WORKING YET\n");
		// new_cylinder_pattern(data, data->objs[data->i_am]);
	}
}


// Handle key commands
void ft_key_action(mlx_key_data_t keydata, t_data *data)
{
	(void)keydata;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE)) // ESC key
		mlx_close_window(data->mlx);
	if (data->mouse.selected == true && mlx_is_key_down(data->mlx, MLX_KEY_UP)) // ARROW up -> for different obj colour options
	{
		data->objs[data->i_am]->i++;
		if (data->objs[data->i_am]->i > 2)
			data->objs[data->i_am]->i = 0;
			
		// printf("data->i_am: %d\n", data->i_am);
		// printf("data->i: %d\n", data->objs[data->i_am]->i);
		// printf("data->im: %d\n", data->objs[data->i_am]->i_am);
		what_obj_me(data, data->objs[data->i_am]);

	}
}

// NOTE: I think this could be better !!!!!!
// Handle mouse click
static void	highlight_object(t_data *data, int16_t num)
{
	uint32_t	x;
	uint32_t	y;
	int16_t 	i;
	
	i = 0;
	y = 0;
	data->i_am = num;
	// printf("i_am: %d\n", data->objs[num]->i_am);
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
			printf("VinnyMove\n"); // If you select something thats NOT an object -> in memory of Vincent -> NO, he ain't dead, he just figured this out and I stole the idea.
		else
			highlight_object(data, data->mouse.mouse_map[y][x]); //is an object
	}
}
