/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/02 18:33:44 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/02 18:34:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// int32_t	get_texture(t_data *data, int x, int y)
// {
// 	t_colour	*col;
// 	uint32_t	ret;

// 	col = calloc(1, sizeof(t_colour));

// 	col->r = data->objs[0]->texture->pixels[(y * data->objs[0]->texture->width + x) * data->objs[0]->texture->bytes_per_pixel];
// 	col->g = data->objs[0]->texture->pixels[(y * data->objs[0]->texture->width + x) * data->objs[0]->texture->bytes_per_pixel + 1];
// 	col->b = data->objs[0]->texture->pixels[(y * data->objs[0]->texture->width + x) * data->objs[0]->texture->bytes_per_pixel + 2];
	
// 	ret = ft_convert_rgb(col->r, col->g, col->b);

	
// 	// printf("colours = %i %i %i\n", col.r, col.g, col.b);

// 	return (ret);

// }

// static uint32_t get_text_colour(t_objs *obj, t_colour colour, int x, int y)
// {
// 	mlx_texture_t	*text = obj->texture;
// 	uint32_t		colour_ret;

// 	colour.r = text->pixels[(y * text->width + x) * 4];
// 	colour.g = text->pixels[(y * text->width + x) * 4 + 1];
// 	colour.b = text->pixels[(y * text->width + x) * 4 + 2];

// 	printf("pixel = %i\n", text->pixels[(y * text->width + x) * 4]);

// 	colour_ret = ft_convert_rgb(colour.r, colour.g, colour.b);

// 	return (colour_ret);
// }