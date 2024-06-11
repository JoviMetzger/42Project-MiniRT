/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 16:33:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/11 21:14:47 by smclacke      ########   odam.nl         */
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

// check_shadow !! light!
	/**
	 * if does not hit object directly, false - leave ambient
	 *  else true - give light
	 * 
	 * just check the pixel (+ obj) we know we've hit
	 * if closest then definitely right obj, just maybe shadow
	 * 
	 * 	obj_t = 20.325558
	 *	hit pos = 2.968122
		sphere distance = 15.115867

		sphere - 15.115867
		hit pos = 2.968122
		sphere distance = 15.115867

		hit_pos and t same, so just use t

		wanted to compare obj_t to other objs but obvs dont have the obj_t yet...
	 */
bool check_light(t_data *data, t_objs *obj, t_hit_data *hit)
{
	(void) hit;
	t_ray	shadow_ray;

	shadow_ray.place = plus(data->vars.intersect_p, mult_vecdub(obj->normal, EPSILON));
	shadow_ray.vector = data->vars.light_dir; // LATER; colour->curr_light->place

	// int	j = 0;
	// while (j < data->objs_i)
	// {
	// 	// make a calc for the other objs (only the bit i need), then compare...
	// 	// if obj is infront = z vector and center point compare to current hit obj
	// 	// 
	// 	if (data->objs[j]->obj_t < hit->t)
	// 		return (false);
	// 	j++;
	// }
	return (true);
}
