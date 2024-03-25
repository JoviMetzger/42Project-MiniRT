/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_info.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 22:26:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/25 13:33:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

void	add_vec(t_data *data, double x, double y, double z)
{
	if (data->type == 3)
		vec_camera(data, x, y, z);
	else if (data->type == 4 || data->type == 6)
		vec_other(data, x, y, z);
}

void	add_coord(t_data *data, double x, double y, double z)
{
	if (data->type == 3)
		coord_camera(data, x, y, z);
	else if (data->type == 2)
		coord_light(data, x, y, z);
	else if (data->type == 4 || data->type == 5 || data->type == 6)
		coord_other(data, x, y, z);
}

void	add_rgb(t_data *data, int r, int g, int b)
{
	if (data->type == 1)
		rgb_ambient(data, r, g, b);
	else if (data->type == 2)
		rgb_light(data, r, g, b);
	else if (data->type == 4 || data->type == 5 || data->type == 6)
		rgb_other(data, r, g, b);
}
