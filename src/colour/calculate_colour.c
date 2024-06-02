/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/02 17:09:51 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// static uint32_t get_text_colour(t_objs *obj, t_colour colour, int x, int y)
// {
// 	mlx_texture_t	*text = obj->texture;
// 	uint32_t		colour_ret;

// 	colour.r = text->pixels[(y * text->width + x) * 4];
// 	colour.g = text->pixels[(y * text->width + x) * 4 + 1];
// 	colour.b = text->pixels[(y * text->width + x) * 4 + 2];

// 	printf("pixel = %i\n", text->pixels[(y * text->width + x) * 4]);
// 	printf("colours = %i %i %i\n", colour.r, colour.g, colour.b);

// 	colour_ret = ft_convert_rgb(colour.r, colour.g, colour.b);

// 	return (colour_ret);
// }

// No intersection found, return black
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
 */
uint32_t	ft_calculate_colour(t_data *data, t_hit_data *hit, t_ray ray, int x, int y)
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
			{
				// if (data->objs[i]->texture)
				// 	return (get_text_colour(data->objs[i], colour, x, y));
				// else
					colour = get_colour(data, hit, ray, data->objs[i]);
			}
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
