/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/14 16:13:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	check_roots(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->f = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
	obj->e = plus(ray->place, mult_vecdub(ray->vector, obj->t));
	if (obj->root1 > 0)
	{	
		if (dot_product(cyl->vector, minus(obj->e, cyl->center)) <= 0
			|| dot_product(cyl->vector, minus(obj->e, obj->f)) >= 0)
			obj->root1 = -1;
	}
	if (obj->root2 > 0)
	{	
		if (dot_product(cyl->vector, minus(obj->e, cyl->center)) <= 0
			|| dot_product(cyl->vector, minus(obj->e, obj->f)) >= 0)
			obj->root2 = -1;
	}
	if (obj->root1 < 0 && obj->root2 < 0)
		return (false);
	if ((obj->root2 < obj->root1 && obj->root2 > 0)
		|| (obj->root1 < obj->root2 && obj->root1 <= 0)) 
		obj->t = obj->root2;
	else
		obj->t = obj->root1;
	if (obj->t > 0 && obj->t >= cyl->height)
			return (true);
	return (false);
}

double	plane_cyl(t_ray *ray, t_vec3 center, t_vec3 vector)
{
	double	x;
	double	denom;

	denom = dot_product(vector, ray->vector);
	if (denom == 0)
		return (INFINITY);
	x = -dot_product(vector, minus(ray->place, center)) / denom; // min?
	return (x > 0 ? x : INFINITY);
}

bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	(void) obj;
	double hit1;
	double hit2;
	t_vec3 pnt1;
	t_vec3 pnt2;
	t_vec3 cent2;

	cent2 = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));

	hit1 = plane_cyl(ray, cyl->center, cyl->vector);
	hit2 = plane_cyl(ray, cent2, cyl->vector);
	if (hit1 < INFINITY || hit2 < INFINITY)
	{
		pnt2 = plus(mult_vecdub(ray->vector, hit2), ray->place);
		pnt1 = plus(mult_vecdub(ray->vector, hit1), ray->place);
		if (hit1 < INFINITY && distance(pnt1, cyl->center) <= obj->radius)
		{
			obj->t = hit1;
			return (true);
		}
		else if (hit2 < INFINITY && distance(pnt2, cent2) <= obj->radius)
		{
			obj->t = hit2;
			return (true);
		}
		return (false);
	}
	return (false);
}

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
				obj->tmp_t = obj->t;
				if (check_caps(obj, cyl, ray) == true)
					return (check_closest(obj));
					
				else // if no cap, no cyl... remove this after testing
				{
					// return (false);
					obj->t = obj->tmp_t;
					return (check_closest(obj));
				}
					// return (check_closest(obj));
			}
		}
	}
	return (false);
}

