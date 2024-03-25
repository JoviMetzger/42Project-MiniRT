/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_info.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 22:26:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/25 15:27:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

void	add_vec(t_data *data, double x, double y, double z)
{
	if (data->type == E_CAMERA)
		vec_camera(data, x, y, z);
	else if (data->type == E_PLANE || data->type == E_CYLINDER)
		vec_obj(data, x, y, z);
}

void	add_coord(t_data *data, double x, double y, double z)
{
	if (data->type == E_CAMERA)
		coord_camera(data, x, y, z);
	else if (data->type == E_LIGHT)
		coord_light(data, x, y, z);
	else if (data->type == E_PLANE || data->type == E_SPHERE
		|| data->type == E_CYLINDER)
		coord_obj(data, x, y, z);
}

void	add_rgb(t_data *data, int r, int g, int b)
{
	if (data->type == E_AMBIENT)
		rgb_ambient(data, r, g, b);
	else if (data->type == E_LIGHT)
		rgb_light(data, r, g, b);
	else if (data->type == E_PLANE || data->type == E_SPHERE
		|| data->type == E_CYLINDER)
		rgb_obj(data, r, g, b);
}
