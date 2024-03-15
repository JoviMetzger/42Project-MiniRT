/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_rgb.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 17:53:33 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 20:50:27 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

void	rgb_pl(t_data *data, int r, int g, int b)
{
	data->objects.plane.colour.r = r; 
	data->objects.plane.colour.g = g; 
	data->objects.plane.colour.b = b;
}

void	rgb_sp(t_data *data, int r, int g, int b)
{
	data->objects.sphere.colour.r = r; 
	data->objects.sphere.colour.g = g; 
	data->objects.sphere.colour.b = b;
}

void	rgb_cy(t_data *data, int r, int g, int b)
{
	data->objects.cylinder.colour.r = r; 
	data->objects.cylinder.colour.g = g; 
	data->objects.cylinder.colour.b = b;
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
