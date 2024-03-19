/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_coord.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 20:43:45 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/19 14:58:12 by smclacke      ########   odam.nl         */
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

void	coord_pl(t_data *data, double x, double y, double z)
{
	data->objects.plane.center.x = x; 
	data->objects.plane.center.y = y; 
	data->objects.plane.center.z = z;
}

void	coord_sp(t_data *data, double x, double y, double z)
{
	data->objects.sphere.center.x = x; 
	data->objects.sphere.center.y = y; 
	data->objects.sphere.center.z = z;
}

void	coord_cy(t_data *data, double x, double y, double z)
{
	data->objects.cylinder.center.x = x; 
	data->objects.cylinder.center.y = y; 
	data->objects.cylinder.center.z = z;
}
