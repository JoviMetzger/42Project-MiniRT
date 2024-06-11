/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 16:33:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/11 21:00:11 by smclacke      ########   odam.nl         */
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
	 */
bool check_light(t_data *data, t_objs *obj, t_hit_data *hit)
{
	(void) hit;
	t_ray	shadow_ray;

	shadow_ray.place = plus(data->vars.intersect_p, mult_vecdub(obj->normal, EPSILON));
	shadow_ray.vector = data->vars.light_dir; // LATER; colour->curr_light->place

	/**
	 * if in the vector of the ray, another object is closer/infront of from the 'ray view'...
	 * each obj has there own intersect distance stored
	 */
	// int	j = -1;
	// while (++j < data->objs_i)
	// {
	// 	printf("distance - %f\n", data->objs[j]->distance);
	// 	printf("t - %f\n", data->objs[j]->obj_t);
	// 	exit(0);
	// 	if (data->objs[j]->distance < hit->t)
	// 		return (false);
	// }
	
	// if ()
		// return (true);
	// return (false);
	return (true);
}





// old stuff from above func	
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
	// return (true);
	// return (false);
