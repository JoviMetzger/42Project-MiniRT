/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/08 14:52:31 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	intersect_cyl_plane(t_ray *ray, t_objs *cyl_plane, t_hit_data *hit)
{
	double	denom;

	denom = dot_product(ray->vector, cyl_plane->vector);
	if (fabs(denom) > EPSILON)
	{
		hit->o_c = minus(cyl_plane->center, ray->place);
		hit->t = dot_product(hit->o_c, cyl_plane->vector) / denom;
		if (hit->t >= EPSILON)
		{
			if (denom < 0)
				cyl_plane->normal = mult_vecdub(cyl_plane->vector, -1);
			return (true);
		}
	}
	return (false);
}

/**
 * if t is negative, no intersection found
 * 
 * 			t = -X|V / D|V
 * 
 * 			x = ray origin - center point of a shape
 *			v = plane normal
 * 			d = ray direction
 */
bool	intersect_plane(t_ray *ray, t_objs *plane, t_hit_data *hit)
{
	double	denom;

	denom = dot_product(ray->vector, plane->vector);
	if (fabs(denom) > EPSILON)
	{
		hit->o_c = minus(plane->center, ray->place);
		hit->t = dot_product(hit->o_c, plane->vector) / denom;
		if (hit->t >= EPSILON)
		{
			if (denom < 0)
				plane->normal = mult_vecdub(plane->vector, -1);
			return (check_closest(hit));
		}
	}
	return (false);
}
