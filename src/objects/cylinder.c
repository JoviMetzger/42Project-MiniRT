/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/16 18:47:16 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->base = mult_vecdub(plus(cyl->center, cyl->vector), -cyl->height_half);
	obj->top = mult_vecdub(plus(cyl->center, cyl->vector), cyl->height_half);

	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = obj->top;
	tmppl.vector = cyl->vector;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = mult_vecdub(ray->vector, obj->t);

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
		obj->hit_pos = mult_vecdub(ray->vector, obj->t);

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
	t_vec3	oc;

	vector_cross = cross_product(cyl->vector, ray->vector);
	oc = minus(ray->place, cyl->center);
	oc = cross_product(oc, cyl->vector);
	obj->a = dot_product(vector_cross, vector_cross);
	obj->b = -2.0 * dot_product(vector_cross, oc);
	obj->c = dot_product(oc, oc) - pow(cyl->radius, 2);
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
		obj->tmp_t = obj->t;
		if (cut_ends(obj, cyl, ray) == true)
		{
			if (check_caps(obj, cyl, ray) == true)
				return (check_closest(obj));
			else
			{
				obj->t = obj->tmp_t;
				return (check_closest(obj));
			}
		}
	}
	return (false);
}
