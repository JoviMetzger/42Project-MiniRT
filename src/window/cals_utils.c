/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cals_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 17:46:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/22 17:54:18 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

t_ray	init_light_ray(t_data *data, int i, int light_i)
{
	t_vec3	inter_p;
	t_vec3	light_dir;

	inter_p = mult_vecdub(data->pix[i]->og_ray.vector, data->pix[i]->hit_t);
	light_dir = plus(data->light[light_i]->place, inter_p);
	data->pix[i]->light_ray.place = inter_p;
	data->pix[i]->light_ray.vector = light_dir;
	return (data->pix[i]->light_ray);
}

bool	does_intersect(t_ray *ray, t_objs *obj, t_hit_data *hit_2)
{
	if (intersect_sphere(ray, obj, hit_2)
		|| intersect_triangle(ray, obj, hit_2)
		|| intersect_cylinder(ray, obj, hit_2)
		|| intersect_plane(ray, obj, hit_2))
			return (true);
	return (false);
}
