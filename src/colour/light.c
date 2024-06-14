/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 16:33:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/14 20:19:48 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

t_colour give_light(t_data *data)
{
	add_light(&data->vars, data->ray);
	data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
	data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
	data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));
	return (data->vars.result);
}

uint32_t	get_light(t_data *data)
{
	t_colour	light;
	uint32_t	result;

	light = give_light(data);
	result = ft_convert_rgb(data->vars.result.r,
		data->vars.result.g, data->vars.result.b);
	return (result);
}

bool	in_light(t_data *data, t_hit_data *hit, int i)
{
	(void) hit;

	if (data->pix[i]->hit_b == true) // && is in direct light
		return (true);
	else
		return (false);
}
