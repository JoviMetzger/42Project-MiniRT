/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/27 18:40:38 by smclacke      ########   odam.nl         */
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

static uint32_t	get_ret(t_hit_data *hit_data, t_colour colour)
{
	if (hit_data->closest_t != DBL_MAX)
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
uint32_t	ft_calculate_colour(t_data *data, t_hit_data *hit_data, t_ray ray)
{
	t_colour	colour;
	int			i;

	i = 0;
	hit_data->closest_t = DBL_MAX;
	bzero(&colour, sizeof(t_colour));
	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_PLANE)
		{
			if (intersect_plane(&ray, data->objs[i], hit_data))
				colour = get_colour(data, hit_data, ray, data->objs[i]);
		}
		else if (data->objs[i]->type == E_SPHERE)
		{
			if (intersect_sphere(&ray, data->objs[i], hit_data))
				colour = get_colour(data, hit_data, ray, data->objs[i]);
		}
		else if (data->objs[i]->type == E_CYLINDER)
		{
			if (intersect_cylinder(&ray, data->objs[i], hit_data))
				colour = get_colour(data, hit_data, ray, data->objs[i]);
		}
		// else if (data->objs[i]->type == E_TRIANGLE)
		// {
		// 	if (intersect_triangle(&ray, data->objs[i], hit_data))
		// 		colour = get_colour(data, hit_data, ray, data->objs[i]);
		// }
		i++;
	}
	return (get_ret(hit_data, colour));
}
