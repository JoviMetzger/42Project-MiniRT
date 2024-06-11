/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 16:33:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/11 16:44:32 by smclacke      ########   odam.nl         */
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

// check_shadow
bool check_light(t_data *data, t_objs *obj, t_hit_data *hit)
{
	(void) hit;
	t_ray	shadow_ray;
	data->is_shadow = 0;
	obj->has_shadow = 0;

	shadow_ray.place = plus(data->vars.intersect_p, mult_vecdub(obj->normal, EPSILON));
	shadow_ray.vector = data->vars.light_dir; // LATER; colour->curr_light->place

	// int j = -1;
	// while (++j < data->objs_i)
	// {
	// 	// if ray does not hit directly - false
	// 	if (intersect_sphere(&shadow_ray, data->objs[j], hit)
	// 		|| intersect_plane(&shadow_ray, data->objs[j], hit)
	// 		|| intersect_cylinder(&shadow_ray, data->objs[j], hit)
	// 		|| intersect_triangle(&shadow_ray, data->objs[j], hit))
	// 		{
	// 			// printf("false\n");
	// 			return (false);
	// 		}
	// }
	return (true);
}