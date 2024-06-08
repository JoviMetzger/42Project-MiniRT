/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/08 14:23:09 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	cut_ends_hit_bod(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	double	projection;

	hit->to_center = plus(ray->place, mult_vecdub(ray->vector, hit->t));
	hit->from_center = minus(hit->to_center, cyl->center);
	projection = dot_product(hit->from_center, cyl->vector);
	if (fabs(projection) <= cyl->height_half)
		return (true);
	return (false);
}

void	set_points(t_hit_data *hit, t_ray *ray, t_objs *cyl)
{
	hit->vector_cross = cross_product(cyl->vector, ray->vector);
	hit->o_c = minus(cyl->center, ray->place);
	hit->o_c = cross_product(hit->o_c, cyl->vector);
	hit->a = dot_product(hit->vector_cross, hit->vector_cross);
	hit->b = 2.0 * dot_product(hit->vector_cross, hit->o_c);
	hit->c = dot_product(hit->o_c, hit->o_c) - (cyl->radius * cyl->radius);
}

bool	bodyody(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	set_points(hit, ray, cyl);
	if (quadratic(hit) == true)
	{
		if (cut_ends_hit_bod(hit, cyl, ray) == true)
			return (true);
	}
	return (false);
}

void	cyl_normal(t_ray *ray, t_objs *cyl, t_hit_data *hit)
{
	hit->hit_pos = plus(ray->place, mult_vecdub(ray->vector, hit->t));
	hit->to_center = minus(hit->hit_pos, cyl->center);
	cyl->tmp_normal = minus(hit->to_center, mult_vecdub(cyl->vector,
				dot_product(cyl->vector, hit->to_center)));
	cyl->normal = normalize(cyl->tmp_normal);
}

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *hit)
{
	hit->tmp_t = DBL_MAX;
	if (tap_top(hit, cyl, ray) == true)
	{
		if (hit->t < hit->tmp_t)
			hit->tmp_t = hit->t;
	}
	if (boop_bottom(hit, cyl, ray) == true)
	{
		if (hit->t < hit->tmp_t)
			hit->tmp_t = hit->t;
	}
	if (bodyody(hit, cyl, ray) == true)
	{
		if (hit->t < hit->tmp_t)
		{
			hit->tmp_t = hit->t;
			cyl_normal(ray, cyl, hit);
		}
	}
	if (hit->tmp_t != DBL_MAX)
		return (check_closest(hit));
	return (false);
}
