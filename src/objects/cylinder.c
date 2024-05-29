/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/29 17:15:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

//                                           ^ ^
//  1.41, not quite perfect but good enough  0_0

bool	tap_top(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	cyl->top = minus(cyl->center, mult_vecdub(cyl->vector, cyl->height_half / 2));

	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->top;
	tmppl.vector = cyl->vector;
	if (intersect_cyl_plane(ray, &tmppl, hit) == true)
	{
		hit->hit_pos = plus(ray->place, mult_vecdub(ray->vector, hit->t));
		double distance = vec_length(cyl->top, hit->hit_pos);

		if (distance <= cyl->radius / 1.41)
			return (true);
	}
	return (false);
}

bool	boop_bottom(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	cyl->base = minus(cyl->center, mult_vecdub(cyl->vector, -(cyl->height_half / 2)));

	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->base;
	tmppl.vector = cyl->vector;
	if (intersect_cyl_plane(ray, &tmppl, hit) == true)
	{
		hit->hit_pos = plus(ray->place, mult_vecdub(ray->vector, hit->t));
		double distance = vec_length(cyl->base, hit->hit_pos);

		if (distance <= cyl->radius / 1.41)
			return (true);
	}
	return (false);
}

bool	cut_ends_hit_bod(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	hit->to_center = plus(minus(ray->place, cyl->center), mult_vecdub(ray->vector, hit->t));
	if (fabs(dot_product(hit->to_center, cyl->vector)) <= cyl->height_half)
			return (true);
	return (false);
}

void	set_points(t_hit_data *hit, t_ray *ray, t_objs *cyl)
{
	t_vec3	vector_cross;
	// t_vec3	o_c;

	vector_cross = cross_product(cyl->vector, ray->vector);
	hit->o_c = minus(cyl->center, ray->place);
	hit->o_c = cross_product(hit->o_c, cyl->vector);
	hit->a = dot_product(vector_cross, vector_cross);
	hit->b = 2.0 * dot_product(vector_cross, hit->o_c);
	hit->c = dot_product(hit->o_c, hit->o_c) - pow(cyl->radius, 2);
}

void	cyl_normal(t_ray *ray, t_objs *cyl, t_hit_data *hit)
{
	hit->hit_pos = mult_vecdub(ray->vector, hit->t);
	hit->to_center = minus(hit->hit_pos, cyl->center);
	hit->pnt = plus(cyl->center, mult_vecdub(cyl->vector, dot_product(hit->to_center, cyl->vector)));
	cyl->normal = normalize_vector(hit->pnt);
}

bool	bodyody(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	set_points(hit, ray, cyl);
	if (quadratic(hit) == true)
	{
		if (cut_ends_hit_bod( hit, cyl, ray) == true)
		{
			// cyl->normal = normalize_vector(minus(hit->hit_pos, cyl->center));
			return (true);
		}
	}
	return (false);
}

// if intersect one of these things, save t, update per 'thing' if newest 'thing' closest
// i.e. if we hit the top and bottom cap, one of them will be closer so if it's the bottom,
// tmp is updated with bottom t, else tmp stays as it is for top
bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *hit)
{
	double	tmp;
	
	tmp = DBL_MAX;
	if (tap_top(hit, cyl, ray) == true)
	{
		if (hit->t < tmp)
			tmp = hit->t;
	}
	if (boop_bottom(hit, cyl, ray) == true)
	{
		if (hit->t < tmp)
			tmp = hit->t;
	}
	if (bodyody(hit, cyl, ray) == true)
	{
		if (hit->t < tmp)
			tmp = hit->t;
	}
	if (tmp != DBL_MAX)
		return (check_closest(hit));
	return (false);
}
