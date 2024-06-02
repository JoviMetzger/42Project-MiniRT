/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/02 18:35:05 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// // No intersection found, return black
static uint32_t	get_ret(t_hit_data *hit, t_colour colour)
{
	if (hit->closest_t != DBL_MAX)
		return (ft_convert_rgb(colour.r, colour.g, colour.b));
	else
		return (ft_convert_rgb(0, 0, 0));
}

/** lighting: 
 *	(https://learnopengl.com/Advanced-Lighting/Advanced-Lighting)
 *	(https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model)
 *	(https://en.wikipedia.org/wiki/Phong_reflection_model)
 *
 * 		@todo texture, colour, image... heh?
//  */
uint32_t	ft_calculate_colour(t_data *data, t_hit_data *hit, t_ray ray)
{
	t_colour	colour;
	int			i;

	i = 0;
	hit->closest_t = DBL_MAX;
	bzero(&colour, sizeof(t_colour));
	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_PLANE)
		{
			if (intersect_plane(&ray, data->objs[i], hit))
				colour = get_colour(data, hit, ray, data->objs[i]);
		}
		else if (data->objs[i]->type == E_SPHERE)
		{
			if (intersect_sphere(&ray, data->objs[i], hit))
				colour = get_colour(data, hit, ray, data->objs[i]);
		}
		else if (data->objs[i]->type == E_CYLINDER)
		{
			if (intersect_cylinder(&ray, data->objs[i], hit))
				colour = get_colour(data, hit, ray, data->objs[i]);
		}
		else if (data->objs[i]->type == E_TRIANGLE)
		{
			if (intersect_triangle(&ray, data->objs[i], hit))
				colour = get_colour(data, hit, ray, data->objs[i]);
		}
		i++;
	}
	return (get_ret(hit, colour));
}
