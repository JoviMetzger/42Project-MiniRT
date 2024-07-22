/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cals_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 17:46:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/22 21:12:20 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * NOTES
 * 
 * - separate light and obj loop
 * figure out how solve prob in book, how know if point on which obj light or no?
 * 
 * - get order right then add utils back
 */


bool	do_loops(t_data *data)
{
	int	light_i;
	int	obj_i;

	light_i = 0;
	obj_i = 0;
	while (light_i < data->light_i)
	{
		obj_i = 0;
		while (obj_i < data->objs_i)
		{
			if (data->objs[obj_i]->in_light == true)
				obj_i++;
		}

		if (data->light[light_i]->in_light == true)
			return (true);
		light_i++;
	}
	return (false);
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
