/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_coord.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 20:43:45 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/25 13:31:34 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

void	coord_light(t_data *data, double x, double y, double z)
{
	data->light.place.x = x;
	data->light.place.y = y;
	data->light.place.z = z;
}

void	coord_camera(t_data *data, double x, double y, double z)
{
	data->camera.place.x = x;
	data->camera.place.y = y;
	data->camera.place.z = z;
}

void	coord_other(t_data *data, double x, double y, double z)
{
	data->objects[data->objects->index].center.x = x;
	data->objects[data->objects->index].center.y = y;
	data->objects[data->objects->index].center.z = z;
}
