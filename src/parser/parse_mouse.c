/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mouse.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/08 13:04:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/08 13:04:22 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

void	init_mouse_map(t_data *data)
{
	int16_t		**map;
	uint32_t	i;

	i = 0;
	data->mouse.window_h = HEIGHT;
	data->mouse.window_w = WIDTH;
	data->mouse.selected = false;
	if (data->mouse.mouse_map != NULL)
		error_msg("map failure");
	map = map_malloc((data->mouse.window_h + 1) * sizeof(int16_t *));
	data->mouse.mouse_map = map;
	while (i < data->mouse.window_h)
	{
		map[i] = map_malloc(data->mouse.window_w * sizeof(int16_t));
		i++;
	}
	map[i] = NULL;
	data->mouse.mouse_map = map;
}
