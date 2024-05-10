/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/10 20:15:20 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"


static bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->tmp_t = obj->t;
	
	// obj->hit1 = ray->place.y + obj->root1 * ray->vector.y;
	// obj->hit2 = ray->place.y + obj->root2 * ray->vector.y;
	
	// obj->hit1 = ray->place.y + obj->root1 * ray->vector.y;
	// obj->hit2 = ray->place.y + obj->root2 * ray->vector.y;

	// if (obj->hit1 < (cyl->vector.y - obj->height_half) || obj->hit1 > cyl->vector.y + obj->height_half)
	// 	obj->root1 = obj->hit1;
	// 	// obj->hit1 = obj->root1;
	// if (obj->hit2 < (cyl->vector.y - obj->height_half) || obj->hit2 > cyl->vector.y + obj->height_half)
	// 	obj->root2 = obj->hit2;
		// obj->hit2 = obj->root2;

	t_vec3	a;
	t_vec3	b;

	b = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
	a = plus(ray->place, mult_vecdub(ray->vector, obj->t));

	if (dot_product(cyl->vector, minus(a, cyl->center)) <= 0)
		obj->root1 = -1;
	if (dot_product(cyl->vector, minus(a, b)) >= 0)
		obj->root2 = -1;

	obj->tmp_t = fmin(obj->root1, obj->root2);
	// obj->tmp_t = fmin(obj->hit1, obj->hit2);

	if (obj->tmp_t > 0)
	{
		double	denom = dot_product(ray->vector, cyl->vector);
		t_vec3	oc = minus(cyl->center, ray->place);
		if (fabs(denom) > EPSILON)
		{
			obj->tmp_t = dot_product(oc, cyl->vector) / denom;
			if (obj->tmp_t >= obj->height_half)
				return (true);
			else
				return (false);
		}
	}
	return (false);
}

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
{

	obj->radius = cyl->diameter / 2;
	obj->height_half = cyl->height / 2;

	t_vec3	aaa;
	t_vec3	right;
	
	aaa = cross_product(cyl->vector, ray->vector);
	right = minus(ray->place, cyl->center);
	right = cross_product(right, cyl->vector);
	
	obj->a = dot_product(aaa, aaa);
	obj->b = -2.0 * dot_product(aaa, right);
	obj->c = dot_product(right, right) - pow(obj->radius, 2);

	if (quadratic(obj) == true)
	{
		if (obj->t > EPSILON)
		{	
			if (check_caps(obj, cyl, ray) == true)
			{
				obj->t = obj->tmp_t;
				return (check_closest(obj));
			}
		}
	}
	return (false);
}

// bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
// {
// 	t_vec3	c_c;
// 	t_vec3	r_c;

// 	r_c = cross_product(cyl->vector, ray->vector);
// 	c_c = minus(ray->place, cyl->center);
// 	c_c = cross_product(c_c, cyl->vector);
	
// 	obj->radius = cyl->diameter / 2;
// 	obj->height_half = cyl->height / 2;

// 	obj->a = dot_product(r_c, r_c);
// 	obj->b = -2.0 * dot_product(r_c, c_c);
// 	obj->c = dot_product(c_c, c_c) - pow(obj->radius, 2);
// 	if (quadratic(obj) == true)
// 	{
// 		if (obj->t > EPSILON)
// 		{	
// 			if (check_caps(obj, cyl, ray) == true)
// 			{
// 				obj->t = obj->tmp_t;
// 				return (check_closest(obj));
// 			}
// 			else
// 				return (false);
// 				// return (check_closest(obj));	
// 		}
// 	}
// 	return (false);
// }
