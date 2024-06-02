/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cyl_caps.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 19:12:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/02 14:24:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	tap_top(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	t_objs	tmppl;
	double	distance;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->top;
	tmppl.vector = cyl->vector;
	if (intersect_cyl_plane(ray, &tmppl, hit) == true)
	{
		hit->hit_pos = plus(ray->place, mult_vecdub(ray->vector, hit->t));
		distance = vec_length(cyl->top, hit->hit_pos);
		if (distance <= cyl->radius / 1.41)
			return (true);
	}
	return (false);
}

bool	boop_bottom(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	t_objs	tmppl;
	double	distance;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->base;
	tmppl.vector = cyl->vector;
	if (intersect_cyl_plane(ray, &tmppl, hit) == true)
	{
		hit->hit_pos = plus(ray->place, mult_vecdub(ray->vector, hit->t));
		distance = vec_length(cyl->base, hit->hit_pos);
		if (distance <= cyl->radius / 1.41)
			return (true);
	}
	return (false);
}
