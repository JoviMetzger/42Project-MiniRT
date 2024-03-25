/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_vec.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 22:27:40 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/25 13:33:57 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

void	vec_camera(t_data *data, double x, double y, double z)
{
	data->camera.vector.x = x;
	data->camera.vector.y = y;
	data->camera.vector.z = z;
}

void	vec_other(t_data *data, double x, double y, double z)
{
	data->objects[data->objects->index].vector.x = x;
	data->objects[data->objects->index].vector.y = y;
	data->objects[data->objects->index].vector.z = z;
}
