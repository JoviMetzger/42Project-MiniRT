/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_rgb.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 17:53:33 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/25 15:08:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

void	rgb_obj(t_data *data, int r, int g, int b)
{
	data->objs[data->objs->i].colour.r = r;
	data->objs[data->objs->i].colour.g = g;
	data->objs[data->objs->i].colour.b = b;
}

void	rgb_light(t_data *data, int r, int g, int b)
{
	data->light.colour.r = r;
	data->light.colour.g = g;
	data->light.colour.b = b;
}

void	rgb_ambient(t_data *data, int r, int g, int b)
{
	data->ambient.colour.r = r;
	data->ambient.colour.g = g;
	data->ambient.colour.b = b;
}
