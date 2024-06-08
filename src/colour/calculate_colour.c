/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/08 14:05:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/*	This function checks which object is closer to the camera, 
 *	other wise objects will overlap and won't be dispalyed realistic.
 *		- If no intersection is found, it will return black.
 */
static uint32_t	get_ret(t_hit_data *hit, t_colour colour)
{
	if (hit->closest_t != DBL_MAX)
		return (ft_convert_rgb(colour.r, colour.g, colour.b));
	else
		return (ft_convert_rgb(0, 0, 0));
}

/*	This function applies colour to each hit object.
 *		- It applies get_colour() to the correct type;
 *		- The result of that will be send back to mlx_put_pixel().
 *		- data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = i; 
 *		  is for the mouse_map, so that we can select object.
 */
static t_colour	do_stuff(t_type type, t_data *data, t_hit_data *hit, int i)
{
	if (type == E_SPHERE)
	{
		data->objs[i]->i_am = i;
		data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = i;
		return (get_colour(data, hit, data->ray, data->objs[i]));
	}
	else if (type == E_PLANE)
	{
		data->objs[i]->i_am = i;
		data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = i;
		return (get_colour(data, hit, data->ray, data->objs[i]));
	}
	else
	{
		data->objs[i]->i_am = i;
		data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = i;
		return (get_colour(data, hit, data->ray, data->objs[i]));
	}
}

/*	STEP 2. Determine which objects the ray intersects
 *	
 *	This function applies colour to each hit object.
 *		- It loops through all the objects and checks 
 *		  if it has an intersect point (if a obj gets hit).
 *			- If it does have a hit point it executs do_stuff();
 *			  (Becuse the function was too long)
 */
uint32_t	ft_calculate_colour(t_data *data, t_hit_data *hit)
{
	t_colour	colour;
	int			i;

	i = 0;
	hit->closest_t = DBL_MAX;
	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_SPHERE
			&& intersect_sphere(&data->ray, data->objs[i], hit))
		{
			colour = do_stuff(E_SPHERE, data, hit, i);
		}
		if (data->objs[i]->type == E_PLANE
			&& intersect_plane(&data->ray, data->objs[i], hit))
		{
			colour = do_stuff(E_PLANE, data, hit, i);
		}
		if (data->objs[i]->type == E_CYLINDER
			&& intersect_cylinder(&data->ray, data->objs[i], hit))
		{
			colour = do_stuff(E_CYLINDER, data, hit, i);
		}
		i++;
	}
	return (get_ret(hit, colour));
}
