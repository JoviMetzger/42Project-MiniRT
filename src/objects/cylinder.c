/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/16 17:35:48 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
// {
// 	t_vec3 cap[2];
// 	t_vec3 hit[2];
// 	double hit1 = 0;
// 	double hit2 = 0;
// 	double denom = dot_product(ray->vector, cyl->vector);
// 	if (denom == 0 || fabs(denom) < 0)
// 		return (false);

// 	// obj->top = minus(ray->place, plus(cyl->center, mult_vecdub(cyl->vector, cyl->height)));
// 	// obj->base = minus(ray->place, plus(cyl->center, mult_vecdub(cyl->vector, -cyl->height)));
	
// 	obj->base = mult_vecdub(plus(cyl->center, cyl->vector), -cyl->height / 2);
// 	obj->top = mult_vecdub(plus(cyl->center, cyl->vector), cyl->height / 2);
	
// 	double dist1 = -dot_product(obj->top, cyl->vector) / denom;
// 	double dist2 = -dot_product(obj->base, cyl->vector) / denom;

// 	if (dist1 < 0 && dist2 < 0)
// 		return (false);

// 	if (dist1 > 0)
// 	{
// 		hit[0] = mult_vecdub(ray->vector, dist1);
// 		cap[0] = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
// 		hit1 = (fabs(vec_length(hit[0], cap[0])) <= cyl->radius);
// 		obj->t = hit1;
// 	}
// 	if (dist2 > 0)
// 	{
// 		hit[1] = mult_vecdub(ray->vector, dist2);
// 		cap[1] = plus(cyl->center, mult_vecdub(cyl->vector, -cyl->height));
// 		hit2 = (fabs(vec_length(hit[1], cap[1])) <= cyl->radius);
// 		obj->t = hit2;
// 	}
// 	if (!hit1 && !hit2)
// 		return (false);
// 	if ((hit1 && hit2 && dist2 < dist1) || !hit1)
// 	{
// 		obj->t = hit2;
// 	}
// 	else
// 		obj->t = hit1;
// 	return (true);
// }

// makes most sense but doesn't work hehe
bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->base = mult_vecdub(plus(cyl->center, cyl->vector), -cyl->height / 2);
	obj->top = mult_vecdub(plus(cyl->center, cyl->vector), cyl->height / 2);

	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = obj->top;
	tmppl.vector = cyl->vector;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		// obj->hit_pos = plus(ray->place, mult_vecdub(ray->vector, obj->t));
		// obj->hit_pos = mult_vecdub(ray->vector, obj->t);
		
		obj->hit_pos = plus(ray->vector, (mult_vecdub(ray->vector, obj->t)));
		double distance = vec_length(obj->hit_pos, obj->top);
		if (distance <= cyl->radius)
		{	
			obj->t = distance;
			return (true);
		}
	}
	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = obj->base;
	tmppl.vector = cyl->vector;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = plus(ray->place, mult_vecdub(ray->vector, obj->t));
		// obj->hit_pos = mult_vecdub(ray->vector, obj->t);
		
		// obj->hit_pos = plus(ray->vector, (mult_vecdub(ray->vector, obj->t)));
		double distance = vec_length(obj->hit_pos, obj->base);
		if (distance <= cyl->radius)
		{
			obj->t = distance;
			return (true);
		}
	}
	return (false);
}

bool	cut_ends(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->cut[0] = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
	obj->cut[1] = plus(ray->place, mult_vecdub(ray->vector, obj->t));
	if (obj->root1 > 0)
	{
		if (dot_product(cyl->vector, minus(obj->cut[1], cyl->center)) <= 0
			|| dot_product(cyl->vector, minus(obj->cut[1], obj->cut[0])) >= 0)
				obj->root1 = -1;
	}
	if (obj->root2 > 0)
	{
		if (dot_product(cyl->vector, minus(obj->cut[1], cyl->center)) <= 0
			|| dot_product(cyl->vector, minus(obj->cut[1], obj->cut[0])) >= 0)
			obj->root2 = -1;
	}
	if ((obj->root2 < obj->root1 && obj->root2 > 0)
		|| (obj->root1 < obj->root2 && obj->root1 <= 0)) 
		obj->t = obj->root2;
	else
		obj->t = obj->root1;
	if (obj->t > 0 && obj->t >= cyl->height)
			return (true);
	return (false);
}

static void	set_points(t_obj_data *obj, t_ray *ray, t_objs *cyl)
{
	t_vec3	vector_cross;
	t_vec3	to_cyl_center;

	vector_cross = cross_product(cyl->vector, ray->vector);
	to_cyl_center = minus(ray->place, cyl->center);
	to_cyl_center = cross_product(to_cyl_center, cyl->vector);
	obj->a = dot_product(vector_cross, vector_cross);
	obj->b = -2.0 * dot_product(vector_cross, to_cyl_center);
	obj->c = dot_product(to_cyl_center, to_cyl_center) - pow(cyl->radius, 2);
}

/**
 * after checking roots, save t in tmp, check if body or cap, if body, use og t, otherwise
 * if cap, use updated t 
	// when how what where normalize?
	// cyl->center = normalize_vector(cyl->center);
	// ray->vector = normalize_vector(ray->vector);
 */
bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
{
	set_points(obj, ray, cyl);
	if (quadratic(obj) == true)
	{
		if (cut_ends(obj, cyl, ray) == true)
		{
			if (check_caps(obj, cyl, ray) == true)
				return (check_closest(obj));
			else
				return (check_closest(obj));
		}
	}
	return (false);
}
