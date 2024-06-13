/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_rgb.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 17:53:33 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/13 13:41:16 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

void	rgb_obj(t_data *data, int r, int g, int b)
{
	data->objs[data->objs_i]->colour.r = r;
	data->objs[data->objs_i]->colour.g = g;
	data->objs[data->objs_i]->colour.b = b;
}

void	rgb_light(t_data *data, int r, int g, int b)
{
	data->light[data->light_i]->colour.r = r;
	data->light[data->light_i]->colour.g = g;
	data->light[data->light_i]->colour.b = b;
}

void	rgb_ambient(t_data *data, int r, int g, int b)
{
	data->ambient.colour.r = r;
	data->ambient.colour.g = g;
	data->ambient.colour.b = b;
}