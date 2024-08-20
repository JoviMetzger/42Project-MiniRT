/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window_mouse.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/16 20:34:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/*	This function sets/gives all needed inforamtion to mlx_put_pixel().
 *	Needed 	mlx_new_image() struct, current position(x, y) and colour of pixel.
 *		- Colour {255, 255, 255} is for white higlight.
 *		- Colour {0} is for black highlight.
 */
static void	set_pixel(t_data *data, uint32_t x, uint32_t y, uint32_t colour)
{
	mlx_put_pixel(data->mouse.highlight_img, x, y, colour);
}

/*	This function removes the highlight around the object.
 *		- It loops through the window, and puts everywhere no colour.
 *		  So the previous white line will get overwritten.
 */
static void	remove_highlight(t_data *data)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	data->mouse.selected = false;
	while (y < data->mouse.window_h)
	{
		x = 0;
		while (x < data->mouse.window_w)
		{
			set_pixel(data, x, y, 0);
			x++;
		}
		y++;
	}
}

/*	This function draws the highlight around the object.
 *		- It loops through the window, and if it incounters an object
 *		  on the mouse_map, 1 pixls after it draws a white pixel. 
 *		  So the white line is offset by 2 pixels.
 *		  Offset inner pixels of the object instead of the outer pixel.
 */
static void	draw_highlight(t_data *data, int16_t num)
{
	uint32_t	x;
	uint32_t	y;

	y = -1;
	data->mouse.selected = true;
	while (++y < data->mouse.window_h)
	{
		x = -1;
		while (++x < data->mouse.window_w)
		{
			if (data->mouse.mouse_map[y][x] == num)
			{
				if ((x < data->mouse.window_w - 2
						&& data->mouse.mouse_map[y][x + 1] != num)
					|| (x > 0 && data->mouse.mouse_map[y][x - 1] != num)
					|| (y < data->mouse.window_h - 2
						&& data->mouse.mouse_map[y + 1][x] != num)
					|| (y > 0 && data->mouse.mouse_map[y - 1][x] != num)
					|| (x == 0 || x == data->mouse.window_w - 2)
					|| (y == 0 || y == data->mouse.window_h - 2))
					set_pixel(data, x + 1, y, ft_convert_rgb(255, 255, 255));
			}
		}
	}
}

/*	This function highlight or removes the highlight on the object.
 *	(Highlight = white line around the object):
 *		- We are using mlx_image_to_window() to put a image (white line)
 *		  ontop of the original image. 
 *		  It loads faster, because we don't loop everything again.
 */
static void	highlight_object(t_data *data, int16_t num)
{
	data->i_am = num;
	if (!data->mouse.selected)
		draw_highlight(data, num);
	else
		remove_highlight(data);
	mlx_image_to_window(data->mlx, data->mouse.highlight_img, 0, 0);
}

/*	This function handels mouse clicks
 *	So if a mouse click is used:
 *	  - Find posistion of mouse.
 *	  - If the mouse map is -1 at that position. So no object has been selected.
 *	  - Else if the mouse map is NOT -1 at that position. highlight the object.
 *
 * 	Quick explanation how the mouse map works.
 *	  - There is a 2D mouse_map[y][x].
 *	  - While we looping through every pixel, we fill in this map.
 *	  - If no object is at that position fill in -1.
 *	  - If there is an object give it a number.
 * 			Example:
 * 					Sphere1 = 0;
 * 					Sphere2 = 1;
 * 					Plane	= 2;
 * 
 *	 		mouse_map:
 *						-1 -1 -1 -1 -1
 *						-1 -1  0 -1 -1
 * 						-1  0  0  0 -1
 * 						 0  0  0  0  0
 * 						-1  0  0  0 -1
 *						-1 -1  0 -1 -1
 *						-1 -1 -1 -1 -1	
 */
void	ft_handle_mouse_click(mouse_key_t key, action_t act, modifier_key_t m, void *_data)
{
	t_data		*data;
	int32_t		x;
	int32_t		y;

	(void)m;
	data = (t_data *)_data;
	if (key == MLX_MOUSE_BUTTON_LEFT && act == MLX_RELEASE)
	{
		mlx_get_mouse_pos(data->mlx, &x, &y);
		if ((uint32_t)x >= 0 && (uint32_t)x < data->mouse.window_w
			&& (uint32_t)y >= 0 && (uint32_t)y < data->mouse.window_h)
		{
			if (data->mouse.mouse_map[y][x] == -1)
				printf("No object here/n");
			else
				highlight_object(data, data->mouse.mouse_map[y][x]);
		}
	}
}
