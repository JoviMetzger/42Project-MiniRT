/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_vec.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 22:27:40 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/16 16:45:10 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

void	vec_camera(t_data *data, double x, double y, double z)
{
	data->camera.vector.x = x;
	data->camera.vector.y = y;
	data->camera.vector.z = z;
	normalize(data->camera.vector);
}

void	vec_obj(t_data *data, double x, double y, double z)
{
	data->objs[data->objs_i]->vector.x = x;
	data->objs[data->objs_i]->vector.y = y;
	data->objs[data->objs_i]->vector.z = z;
	normalize(data->objs[data->objs_i]->vector);
}
