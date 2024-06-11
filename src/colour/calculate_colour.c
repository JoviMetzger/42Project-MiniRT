/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/11 17:46:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/*	This function checks which object is closer to the camera, 
 *	other wise objects will overlap and won't be dispalyed realistic.
 *		- If no intersection is found, it will return black.
 */
static uint32_t	get_ret(t_data *data, t_hit_data *hit, t_objs *obj)
{
	t_colour	colour;
	uint32_t	ambient_light;
	t_colour	light;

	if (hit->closest_t != DBL_MAX)
	{
		colour = get_colour(data, hit, obj);
		ambient_light = ft_convert_rgb(colour.r, colour.g, colour.b);
		if (check_light(data, obj, hit) == true)
		{
			light = give_light(data);
			return (ft_convert_rgb(light.r, light.g, light.b));
		}
		else
			return (ambient_light);
	}
	else
		return (ft_convert_rgb(0, 0, 0));
}

/*	This function applies colour to each hit object.
 *		- It applies get_colour() to the correct type;
 *		- The result of that will be send back to mlx_put_pixel().
 *		- data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = i; 
 *		  is for the mouse_map, so that we can select object.
 */
static t_objs	*update_obj(t_data *data, int obj_i)
{
	data->objs[obj_i]->i_am = obj_i;
	data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = obj_i;
	return (data->objs[obj_i]);
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
	int		i;
	t_objs	*tmp_obj;

	i = 0;
	hit->closest_t = DBL_MAX;
	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_SPHERE
			&& intersect_sphere(&data->ray, data->objs[i], hit))
			tmp_obj = update_obj(data, i);
		else if (data->objs[i]->type == E_PLANE
			&& intersect_plane(&data->ray, data->objs[i], hit))
			tmp_obj = update_obj(data, i);
		else if (data->objs[i]->type == E_CYLINDER
			&& intersect_cylinder(&data->ray, data->objs[i], hit))
			tmp_obj = update_obj(data, i);
		else if (data->objs[i]->type == E_TRIANGLE	
			&& intersect_triangle(&data->ray, data->objs[i], hit))
			tmp_obj = update_obj(data, i);
		i++;
	}
	return (get_ret(data, hit, tmp_obj));
}
  