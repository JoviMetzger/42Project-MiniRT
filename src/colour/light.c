/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 16:33:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/14 18:43:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

uint32_t give_light(t_data *data)
{
	add_light(&data->vars, data->ray);
	data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
	data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
	data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));
	return (ft_convert_rgb(data->vars.result.r, data->vars.result.g, data->vars.result.b));
}

bool	in_light(t_data *data, int i)
{
	t_ray 		shadow_ray;
	// t_colour	light;
	t_objs		*obj;

	obj = data->pix[i]->obj;
	// printf("obj = %p\n", obj);
	// exit(0);

	printf("inter p = %f\n", data->vars.intersect_p.x);
	printf("normal = %f\n", obj->normal.x);
	exit(0);
	shadow_ray.place = plus(data->vars.intersect_p, mult_vecdub(obj->normal, EPSILON));
	shadow_ray.vector = data->vars.light_dir; // LATER; colour->curr_light->place

	// if pixel in direct light
	return (true);
	// else
	// return (false);
}
