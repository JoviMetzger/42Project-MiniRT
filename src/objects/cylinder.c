/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/23 23:38:55 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	tap_top(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	cyl->top = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height_half));

	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->top;
	tmppl.vector = cyl->vector;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = plus(ray->place, mult_vecdub(ray->vector, obj->t));
		double distance = vec_length(cyl->top, obj->hit_pos);

		if (distance <= cyl->radius)
			return (true);
	}
	return (false);
}

bool	boop_bottom(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	cyl->base = plus(cyl->center, mult_vecdub(ray->vector, -cyl->height_half));

	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->base;
	tmppl.vector = cyl->vector;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = plus(ray->place, mult_vecdub(ray->vector, obj->t));
		double distance = vec_length(cyl->base, obj->hit_pos);

		if (distance <= cyl->radius)
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

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *obj)
{
	set_points(obj, ray, cyl);
	if (quadratic(obj) == true)
	{
		obj->tmp_t = obj->t;
		if (cut_ends_hit_bod( obj, cyl, ray) == true)
			return (check_closest(obj));
		obj->t = obj->tmp_t;
		if (tap_top(obj, cyl, ray) == true)
			return (check_closest(obj));
		obj->t = obj->tmp_t;
		if (boop_bottom(obj, cyl, ray) == true)
			return (check_closest(obj));
	}
	return (false);
}
