/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/11 15:36:27 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	check_roots(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	t_vec3	a;
	t_vec3	b;

	b = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
	a = plus(ray->place, mult_vecdub(ray->vector, obj->t));

	if (obj->root1 > 0)
	{	
		if (dot_product(cyl->vector, minus(a, cyl->center)) <= 0)
			obj->root1 = -1;
		if (dot_product(cyl->vector, minus(a, b)) >= 0)
			obj->root1 = -1;
	}
	if (obj->root2 > 0)
	{	
		if (dot_product(cyl->vector, minus(a, cyl->center)) <= 0)
			obj->root2 = -1;
		if (dot_product(cyl->vector, minus(a, b)) >= 0)
			obj->root2 = -1;
	}
	
	if (obj->root1 < 0 && obj->root2 < 0)
		return (false);
	if ((obj->root2 < obj->root1 && obj->root2 > 0) || (obj->root1 < obj->root2 && obj->root1 <= 0)) 
		obj->t = obj->root2;
	else
		obj->t = obj->root1;

	if (obj->t > 0)
	{
		if (obj->t >= cyl->height)
			return (true);
		// else if (obj->t <= cyl->height && obj->t <= dot_product(ray->vector, cyl->vector))
		// 	return (true);
	}
	return (false);
}

/**
 * not sure if in root check function, find cap or just in intersect cyl
 * also, how find cap? and if cap count what do?
 */

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
{

	t_vec3	vector_cross;
	t_vec3	distance;

	obj->radius = cyl->diameter / 2;
	obj->height_half = cyl->height / 2;
	vector_cross = cross_product(cyl->vector, ray->vector);
	distance = minus(ray->place, cyl->center);
	distance = cross_product(distance, cyl->vector);
	obj->a = dot_product(vector_cross, vector_cross);
	obj->b = -2.0 * dot_product(vector_cross, distance);
	obj->c = dot_product(distance, distance) - pow(obj->radius, 2);
	if (quadratic(obj) == true)
	{
		if (obj->t > EPSILON)
		{	
			if (check_roots(obj, cyl, ray) == true)
			{
				// if the point is the cap....
				// if point is on cyl vector but lesss than/more than height?
				// if (obj->t )
				return (check_closest(obj));
			}
		}
	}
	return (false);
}
