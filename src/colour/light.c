/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 16:33:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/14 21:12:52 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

t_colour give_light(t_data *data)
{
	add_light(data->vars, data->ray);
	data->vars->result.r = fmin(255, fmax(0, data->vars->result.r));
	data->vars->result.g = fmin(255, fmax(0, data->vars->result.g));
	data->vars->result.b = fmin(255, fmax(0, data->vars->result.b));
	return (data->vars->result);
}

// 			light = give_light(data);
// 			return (ft_convert_rgb(light.r, light.g, light.b));

uint32_t	get_light(t_data *data)
{
	t_colour	light;

	light = give_light(data);
	return (ft_convert_rgb(light.r, light.g, light.b));
}


// shadow_ray.place = plus(data->vars.intersect_p, mult_vecdub(obj->normal, EPSILON));
// shadow_ray.vector = data->vars.light_dir; // LATER; colour->curr_light->place

bool	in_light(t_data *data, t_hit_data *hit, int i)
{
	(void) hit;

	if (data->pix[i]->hit_b == true && data->pix[i]->hit_t != DBL_MAX) // && is in direct light
		return (true);
	else
		return (false);
}
