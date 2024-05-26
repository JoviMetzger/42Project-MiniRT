/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/26 22:12:59 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// / 1.41999999
bool	tap_top(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	cyl->top = minus(cyl->center, mult_vecdub(cyl->vector, cyl->height_half / 2));

	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->top;
	tmppl.vector = cyl->vector;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = plus(ray->place, mult_vecdub(ray->vector, obj->t));
		double distance = vec_length(cyl->top, obj->hit_pos);

		if (distance <= cyl->radius / 1.41999999)
			return (true);
	}
	return (false);
}

// need to figure out what vector addition im missing to get plane on top for bottom cap
// i.e. test vector...
bool	boop_bottom(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
 	// t_vec3 test = {0, 2.1, 0};
 	// t_vec3 test = {-0.5, 1, 0};
 	// t_vec3 test = {0, 0, 0};
	// cyl->base = plus(test, plus(cyl->center, mult_vecdub(ray->vector, -(cyl->height_half/ 2))));
	// cyl->base = plus(cyl->center, plus(cyl->vector, mult_vecdub(ray->vector, -(cyl->height_half / 2))));
	// cyl->base = plus(division_vec_dub(cyl->vector, 2), plus(cyl->center, mult_vecdub(ray->vector, -(cyl->height_half / 2))));
	// cyl->base = plus(division_vec_dub(cyl->vector, cyl->height_half), plus(cyl->center, mult_vecdub(ray->vector, -(cyl->height_half / 2))));
	cyl->base = minus(cyl->center, mult_vecdub(cyl->vector, -(cyl->height_half / 2)));
	// cyl->base = plus(division_vec_dub(cyl->vector, cyl->height_half), plus(cyl->center, mult_vecdub(ray->vector, -(cyl->height_half / 2))));
// 3 = -0.75
// 6 = -1.5
	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->base;
	tmppl.vector = cyl->vector;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = plus(ray->place, mult_vecdub(ray->vector, obj->t));
		double distance = vec_length(obj->hit_pos, cyl->base);

		if (distance <= cyl->radius / 1.41)
			return (true);
	}
	return (false);
}

// hit cylinder body check
// ray->vector * t + ray->place - cyl->center
bool	cut_ends_hit_bod(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->to_center = plus(minus(ray->place, cyl->center), mult_vecdub(ray->vector, obj->t));
	if (fabs(dot_product(obj->to_center, cyl->vector)) <= cyl->height_half)
			return (true);
	return (false);
}

void	set_points(t_hit_data *obj, t_ray *ray, t_objs *cyl)
{
	t_vec3	vector_cross;
	t_vec3	oc;

	vector_cross = cross_product(cyl->vector, ray->vector);
	oc = minus(cyl->center, ray->place);
	oc = cross_product(oc, cyl->vector);
	obj->a = dot_product(vector_cross, vector_cross);
	obj->b = 2.0 * dot_product(vector_cross, oc);
	obj->c = dot_product(oc, oc) - pow(cyl->radius, 2);
}

bool	intersect_caps(t_ray *ray, t_objs *cyl, t_hit_data *obj)
{
	if (tap_top(obj, cyl, ray) == true)
		return (true);
	if (boop_bottom(obj, cyl, ray) == true)
		return (true);
	return (false);
}

bool	intersect_body(t_ray *ray, t_objs *cyl, t_hit_data *obj)
{
	set_points(obj, ray, cyl);
	if (quadratic(obj) == true)
	{
		if (cut_ends_hit_bod( obj, cyl, ray) == true)
			return (check_closest(obj));
	}
	return (false);
}
