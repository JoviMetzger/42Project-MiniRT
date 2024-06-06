/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/06 21:30:49 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/*	This function checks which object is closer to the camera, 
 *	other wise objects will overlap and won't be dispalyed realistic.
 *		- If no intersection is found, it will return black.
 */
static uint32_t	get_ret(t_obj_hit *obj_hit, t_colour colour)
{
	if (obj_hit->closest_t != DBL_MAX)
		return (ft_convert_rgb(colour.r, colour.g, colour.b));
	else
		return (ft_convert_rgb(0, 0, 0));
}

/*	This function applies colour to each hit object.
 *		- It loops through all the objects and checks 
 *		  if it has an intersect point (if a obj gets hit).
 *			- If it does have one it applies colour to it get_colour();
 *		- The result of that will be send back to mlx_put_pixel().
 *		- data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = i; 
 *		  is for the mouse_map, so that we can select object.
 */
uint32_t	ft_calculate_colour(t_data *data, t_obj_hit *obj_hit, t_ray ray)
{
	t_colour	colour;
	int			i;

	i = 0;
	obj_hit->closest_t = DBL_MAX;
	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_SPHERE)
		{
			if (intersect_sphere(&ray, data->objs[i], obj_hit))
			{
				data->objs[i]->i_am = i;
				colour = get_colour(data, obj_hit, ray, data->objs[i]);
				data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = i;
			}
		}
		if (data->objs[i]->type == E_PLANE)
		{
			if (intersect_plane(&ray, data->objs[i], obj_hit))
			{
				data->objs[i]->i_am = i;
				colour = get_colour(data, obj_hit, ray, data->objs[i]);
				data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = i;
			}
		}
		else if (data->objs[i]->type == E_CYLINDER)
		{
			if (intersect_cylinder(&ray, data->objs[i], obj_hit))
			{
				data->objs[i]->i_am = i;
				colour = get_colour(data, obj_hit, ray, data->objs[i]);
				data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = i;
			}
		}
		i++;
	}
	return (get_ret(obj_hit, colour));
}
