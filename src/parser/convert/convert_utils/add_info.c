/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_info.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 22:26:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/15 15:15:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

void	coord_tri(t_data *data, double x, double y, double z)
{
	if (data->objs[data->objs_i]->point_flag == 0)
	{
		data->objs[data->objs_i]->point[0].x = x;
		data->objs[data->objs_i]->point[0].y = y;
		data->objs[data->objs_i]->point[0].z = z;
	}
	else if (data->objs[data->objs_i]->point_flag == 1)
	{
		data->objs[data->objs_i]->point[1].x = x;
		data->objs[data->objs_i]->point[1].y = y;
		data->objs[data->objs_i]->point[1].z = z;
	}
	else if (data->objs[data->objs_i]->point_flag == 2)
	{
		data->objs[data->objs_i]->point[2].x = x;
		data->objs[data->objs_i]->point[2].y = y;
		data->objs[data->objs_i]->point[2].z = z;
	}
}

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
	else if (data->type == E_TRIANGLE)
		coord_tri(data, x, y, z);
}

void	add_rgb(t_data *data, int r, int g, int b)
{
	if (data->type == E_AMBIENT)
		rgb_ambient(data, r, g, b);
	else if (data->type == E_LIGHT)
		rgb_light(data, r, g, b);
	else if (data->type == E_PLANE || data->type == E_SPHERE
		|| data->type == E_CYLINDER || data->type == E_TRIANGLE)
		rgb_obj(data, r, g, b);
}
