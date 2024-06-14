/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 16:33:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/14 19:35:38 by smclacke      ########   odam.nl         */
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

	light = give_light(data);
	return (ft_convert_rgb(data->vars.result.r, data->vars.result.g, data->vars.result.b));
}

bool	in_light(t_data *data, t_ray ray, t_hit_data *hit, int i)
{
	(void) hit;

	
	// (void) data;
	// (void) i;
	// t_ray 		shadow_ray;
	// t_objs		*obj;

	// obj = data->pix[i]->obj;

	// shadow_ray.place = plus(data->vars.intersect_p, mult_vecdub(obj->normal, EPSILON));
	// shadow_ray.vector = data->vars.light_dir; // LATER; colour->curr_light->place
	// ray.place = plus(data->vars.intersect_p, mult_vecdub(obj->normal, EPSILON));
	// ray.vector = data->vars.light_dir; // LATER; colour->curr_light->place


	if (data->pix[i]->hit_b == true) // && is in direct light
		return (true);
	else
		return (false);
}
