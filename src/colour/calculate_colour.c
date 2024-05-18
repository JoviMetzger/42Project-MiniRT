/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/18 18:36:35 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * 	was attempting this for textures with planes but ... ya know
 * 
* 		// if (data->objs[i]->texture != NULL)
		// {
		// 	data->image = mlx_texture_to_image(data->mlx, data->objs[i]->texture);
		// 	// convert into colour some how...
		// 	if (!data->image)
		// 		return (ft_convert_rgb(0, 0, 0));
		// 	else
		// 		exit(EXIT_SUCCESS);
		// }
		// else
 * 
 */
// t_colour	texture_colour(t_data *data, t_objs *object)
// {
	// data->objs[data->objs_i]->text_img = mlx_texture_to_image(data->mlx, texture);
	// if (!data->objs[data->objs_i]->text_img)
	// 	return (printf("ret 2\n"), 0);
// }

static uint32_t	get_ret(t_obj_data *obj_data, t_colour colour)
{
	if (obj_data->closest_t != DBL_MAX)
		return (ft_convert_rgb(colour.r, colour.g, colour.b));
	else
		return (ft_convert_rgb(0, 0, 0)); // No intersection found, return black
}

/** lighting: 
 *	(https://learnopengl.com/Advanced-Lighting/Advanced-Lighting)
 *	(https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model)
 *	(https://en.wikipedia.org/wiki/Phong_reflection_model)
 *
 * 		@todo texture, colour, image... heh?
 */
uint32_t	ft_calculate_colour(t_data *data, t_obj_data *obj_data, t_ray ray)
{
	t_colour	colour;
	int			i;

	i = 0;
	obj_data->closest_t = DBL_MAX;
	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_SPHERE)
		{
			if (intersect_sphere(&ray, data->objs[i], obj_data))
			{		
				data->objs[i]->i_am = i;
				colour = get_sphere_colour(data, obj_data, ray, data->objs[i]);
				data->mouse.mouse_map[data->mouse.mouse_y][data->mouse.mouse_x] = i; // for the mouse_map, so that we can select obj
			}
		}
		if (data->objs[i]->type == E_PLANE)
		{
			if (intersect_plane(&ray, data->objs[i], obj_data))
			{
				data->objs[i]->i_am = i;
				// colour = get_sphere_colour(data, obj_data, ray, data->objs[i]);
				colour = get_plane_colour(data, obj_data, ray, data->objs[i]);
				data->mouse.mouse_map[data->mouse.mouse_y][data->mouse.mouse_x] = i; // for the mouse_map, so that we can select obj	
				
			}
		}
		else if (data->objs[i]->type == E_CYLINDER)
		{
			if (intersect_cylinder(&ray, data->objs[i], obj_data))
			{
				data->objs[i]->i_am = i;
				// colour = get_sphere_colour(data, obj_data, ray, data->objs[i]);
				// colour = get_cyl_colour(data, obj_data, ray, data->objs[i]);
				data->mouse.mouse_map[data->mouse.mouse_y][data->mouse.mouse_x] = i; // for the mouse_map, so that we can select obj	
				
			}
		}
		i++;
	}
	return (get_ret(obj_data, colour));
}
