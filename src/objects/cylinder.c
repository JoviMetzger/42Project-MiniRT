/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/17 18:30:16 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Cut of the ends, else there will be a infinite cylinder
// static bool	cut_ends(t_hit_data *hit, t_objs *cyl, t_ray *ray, t_vec3 ca)
// {
// 	t_vec3	hit_to_c;
// 	t_vec3	hit_to_ca;	
// 	double	distance_along_axis;

// 	hit->hit_pos = plus(ray->place, mult_vecdub(ray->vector, hit->root1));
// 	hit_to_c = minus(hit->hit_pos, cyl->center);
// 	distance_along_axis = dot_product(hit_to_c, ca);
// 	if (distance_along_axis <= -cyl->height / 2.0
// 		|| distance_along_axis >= cyl->height / 2.0)
// 		return (false);
// 	hit_to_ca = mult_vecdub(ca, distance_along_axis);
// 	cyl->normal = normalize(minus(hit_to_c, hit_to_ca));
// 	return (true);
// }

// // Helper function for the quadratic math stuff 
// static bool	quadratic(t_hit_data *hit, t_objs *cyl)
// {
// 	double	temp;
// 	(void) cyl;

// 	hit->d = hit->b * hit->b - hit->a * (hit->c - (cyl->radius * cyl->radius));
// 	if (hit->d < 0.0)
// 		return (false);
// 	hit->root1 = (-hit->b - sqrt(hit->d)) / hit->a;
// 	hit->root2 = (-hit->b + sqrt(hit->d)) / hit->a;
// 	if (hit->root1 > hit->root2)
// 	{
// 		temp = hit->root1;
// 		hit->root1 = hit->root2;
// 		hit->root2 = temp;
// 	}
// 	if (hit->root1 < 0)
// 		hit->root1 = hit->root2;
// 	if (hit->root1 < 0)
// 		return (false);
// 	return (true);
// }

// // calculating the body
// static bool	bodyody(t_hit_data *hit, t_objs *cyl, t_ray *ray)
// {
// 	t_vec3	normalized_vector;

// 	normalized_vector = normalize(cyl->vector);
// 	hit->o_c = minus(ray->place, cyl->center);
// 	hit->a_a = minus(ray->vector, mult_vecdub(normalized_vector,
// 				dot_product(normalized_vector, ray->vector)));
// 	hit->b_b = minus(hit->o_c, mult_vecdub(normalized_vector,
// 				dot_product(normalized_vector, hit->o_c)));
// 	hit->a = dot_product(hit->a_a, hit->a_a);
// 	hit->b = dot_product(hit->a_a, hit->b_b);
// 	hit->c = dot_product(hit->b_b, hit->b_b);
// 	if (quadratic(hit, cyl) == true)
// 		hit->t = hit->root1;
// 	return (cut_ends(hit, cyl, ray, normalized_vector));
// }

// bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *hit)
// {
// 	hit->tmp_t = DBL_MAX;
// 	if (bodyody(hit, cyl, ray) == true)
// 	{
// 		if (hit->t < hit->tmp_t)
// 			hit->tmp_t = hit->t;
// 	}
// 	if (intersect_caps(ray, cyl, hit) == true)
// 	{
// 		if (hit->t < hit->tmp_t)
// 			hit->tmp_t = hit->t;
// 	}
// 	if (hit->tmp_t != DBL_MAX)
// 	{
// 		cyl->obj_t = hit->tmp_t;
// 		hit->t = hit->tmp_t;
// 		cyl->hit_pos = plus(ray->place, mult_vecdub(ray->vector, cyl->obj_t));
// 		return (true);
// 	}
// 	return (false);
// }

// bool	cylinder(t_ray *ray, t_objs *cyl, t_hit_data *hit)
// {
// 	if (intersect_cylinder(ray, cyl, hit))
// 		return (check_closest(hit));
// 	return (false);
// }

// Cut of the ends, else there will be a infinite cylinder
static bool	cut_ends_hit_bod(t_hit_data *hit, t_objs *cyl, t_ray *ray,
	t_vec3 ca)
{
	t_vec3	hit_to_c;
	t_vec3	hit_to_ca;
	double	distance_along_axis;

	hit->hit_pos = plus(ray->place, mult_vecdub(ray->vector, hit->root1));
	hit_to_c = minus(hit->hit_pos, cyl->center);
	distance_along_axis = dot_product(hit_to_c, ca);
	if (distance_along_axis <= -cyl->height / 2.0
		|| distance_along_axis >= cyl->height / 2.0)
		return (false);
	hit_to_ca = mult_vecdub(ca, distance_along_axis);
	cyl->normal = normalize(minus(hit_to_c, hit_to_ca));
	return (true);
}

// calculating the body
static bool	bodyody(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	hit->o_c = minus(ray->place, cyl->center);
	hit->a_a = minus(ray->vector, mult_vecdub(normalize(cyl->vector),
				dot_product(normalize(cyl->vector), ray->vector)));
	hit->b_b = minus(hit->o_c, mult_vecdub(normalize(cyl->vector),
				dot_product(normalize(cyl->vector), hit->o_c)));
	hit->a = dot_product(hit->a_a, hit->a_a);
	hit->b = dot_product(hit->a_a, hit->b_b);
	hit->c = dot_product(hit->b_b, hit->b_b);
	hit->d = hit->b * hit->b - hit->a * (hit->c - (cyl->radius * cyl->radius));
	if (hit->d < 0.0)
		return (false);
	hit->root1 = (-hit->b - sqrt(hit->d)) / hit->a;
	hit->root2 = (-hit->b + sqrt(hit->d)) / hit->a;
	if (hit->root1 > hit->root2)
	{
		hit->temp = hit->root1;
		hit->root1 = hit->root2;
		hit->root2 = hit->temp;
	}
	if (hit->root1 < 0)
		hit->root1 = hit->root2;
	if (hit->root1 < 0)
		return (false);
	hit->t = hit->root1;
	return (cut_ends_hit_bod(hit, cyl, ray, normalize(cyl->vector)));
}

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *hit)
{
	hit->tmp_t = DBL_MAX;
	if (bodyody(hit, cyl, ray) == true)
	{
		if (hit->t < hit->tmp_t)
			hit->tmp_t = hit->t;
	}
	if (intersect_caps(ray, cyl, hit) == true)
	{
		if (hit->t < hit->tmp_t)
			hit->tmp_t = hit->t;
	}
	if (hit->tmp_t != DBL_MAX)
	{
		cyl->obj_t = hit->tmp_t;
		hit->t = hit->tmp_t;
		cyl->hit_pos = plus(ray->place, mult_vecdub(ray->vector, cyl->obj_t));
		return (true);
	}
	return (false);
}

bool	cylinder(t_ray *ray, t_objs *cyl, t_hit_data *hit)
{
	if (intersect_cylinder(ray, cyl, hit))
		return (check_closest(hit));
	return (false);
}
