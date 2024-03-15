/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_vec.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 22:27:40 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 22:32:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

void	vec_camera(t_data *data, int x, int y, int z)
{
	data->camera.vector.x = x; 
	data->camera.vector.y = y; 
	data->camera.vector.z = z;
}

void	vec_pl(t_data *data, int x, int y, int z)
{
	data->objects.plane.vector.x = x; 
	data->objects.plane.vector.y = y; 
	data->objects.plane.vector.z = z;
}

void	vec_cy(t_data *data, int x, int y, int z)
{
	data->objects.cylinder.vector.x = x; 
	data->objects.cylinder.vector.y = y; 
	data->objects.cylinder.vector.z = z;
}
