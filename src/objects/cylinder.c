/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/11 17:05:40 by smclacke      ########   odam.nl         */
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
	}
	return (false);
}

/**
 * 				t_vec3 hit = plus(ray->place, mult_vecdub(ray->vector, obj->t));
				t_vec3 ctp = minus(hit, cyl->center);
				t_vec3 normal = minus(ctp, mult_vecdub(cyl->vector, dot_product(cyl->vector, ctp)));
				normalize_vector(normal);
				if (dot_product(normal, ray->vector) > EPSILON)
					normal = mult_vecdub(normal, -1);
				cyl->center = normal;
 * 

 * not sure if in root check function, find cap or just in intersect cyl
 * also, how find cap? and if cap count what do?
 */

// double			solve_plane(t_p3 o, t_p3 d, t_p3 plane_p, t_p3 plane_nv)
// {
// 	double	x;
// 	double	denom;

// 	denom = dot(plane_nv, d);
// 	if (denom == 0)
// 		return (INFINITY);
// 	x = (dot(plane_nv, vsubstract(plane_p, o))) / denom;
// 	return (x > 0 ? x : INFINITY);
// }

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

static bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
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
		pnt1 = plus(ray->place, mult_vecdub(ray->vector, hit1));
		pnt2 = plus(ray->place, mult_vecdub(ray->vector, hit2));
		if ((hit1 < INFINITY && distance(pnt1, cyl->center) <= obj->radius) 
			&& (hit2 < INFINITY && distance(pnt2, cent2) <= obj->radius))
		{
			if (hit1 < hit2) // more or less?
				obj->t = hit1;
			else
				obj->t = hit2;
			return (true);
		}
		else if (hit1 < INFINITY && distance(pnt1, cyl->center) <= obj->radius)
		{
			obj->t = hit1;
			return (true);
		}
		else if (hit2 < INFINITY && distance(pnt2, cent2) <= obj->radius)
		{
			// printf("this hit\n");
			// exit(EXIT_FAILURE);
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
				else
				{
					obj->t = obj->tmp_t;
					return (check_closest(obj));
				}
			}
		}
	}
	return (false);
}
