/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/06 13:01:33 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	cut_ends_hit_bod(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	hit->to_center = plus(minus(ray->place, cyl->center),
			mult_vecdub(ray->vector, hit->t));
	if (fabs(dot_product(hit->to_center, cyl->vector)) <= cyl->height_half)
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
	hit->c = dot_product(hit->o_c, hit->o_c) - pow(cyl->radius, 2);
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
	cyl->normal = minus(hit->to_center,
			mult_vecdub(normalize_vector(cyl->vector),
				dot_product(normalize_vector(cyl->vector), hit->to_center)));
}

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *hit)
{
	hit->tmp_t = DBL_MAX;
	cyl->cyl_flag = 0;
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
			cyl->cyl_flag = 2;
		}
	}
	if (hit->tmp_t != DBL_MAX)
	{
		if (cyl->cyl_flag == 2)
			cyl_normal(ray, cyl, hit);
		else
		{
			cyl->normal = normalize_vector(cyl->vector);
			if (cyl->cyl_denom < 0)
				cyl->normal = mult_vecdub(cyl->vector, -1);
		}
		return (check_closest(hit));
	}
	return (false);
}
