/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_vec.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 22:27:40 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/19 16:09:14 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

void	vec_camera(t_data *data, double x, double y, double z)
{
	data->camera.vector.x = x;
	data->camera.vector.y = y;
	data->camera.vector.z = z;
}

void	vec_pl(t_data *data, double x, double y, double z)
{
	data->objects.plane.vector.x = x;
	data->objects.plane.vector.y = y;
	data->objects.plane.vector.z = z;
}

void	vec_cy(t_data *data, double x, double y, double z)
{
	data->objects.cylinder.vector.x = x;
	data->objects.cylinder.vector.y = y;
	data->objects.cylinder.vector.z = z;
}
