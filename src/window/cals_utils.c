/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cals_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 17:46:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/23 17:06:13 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	does_intersect(t_ray *ray, t_objs *obj, t_hit_data *hit_2)
{
	if (intersect_sphere(ray, obj, hit_2)
		|| intersect_triangle(ray, obj, hit_2)
		|| intersect_cylinder(ray, obj, hit_2)
		|| intersect_plane(ray, obj, hit_2))
			return (true);
	return (false);
}
