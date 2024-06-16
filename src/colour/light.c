/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 16:33:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/16 15:46:48 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

t_colour give_light(t_data *data, t_objs *obj)
{
	add_light(data, &data->vars, data->ray, obj);
	return (data->vars.result);
}

uint32_t	get_light(t_data *data, t_objs *obj)
{
	t_colour	light;

	light = give_light(data, obj);
	return (ft_convert_rgb(light.r, light.g, light.b));
}
