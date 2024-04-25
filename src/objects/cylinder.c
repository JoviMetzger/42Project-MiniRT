/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/25 19:09:46 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * 	the old capping shizzle
 *
	double	t1 = ray->place.y + obj_data->root1 * ray->vector.y;
	double	t2 = ray->place.y + obj_data->root2 * ray->vector.y;
	if (t1 < (cyl->vector.y - height_half) || t1 > cyl->vector.y + height_half)
		obj_data->root1 = INFINITY;
	if (t2 < (cyl->vector.y - height_half) || t2 > cyl->vector.y + height_half)
		obj_data->root2 = INFINITY;
	
	obj_data->t = fmin(obj_data->root1, obj_data->root2);
	if (obj_data->t > 0)
		return (true); 
 */

// IF CYLINDER HIEGHT = 0, INFINITY CYLINDER WOOOOO
bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj_data)
{
	t_vec3	c_c;
	t_vec3	r_c;
	// t_vec3	m;
	// t_vec3	n;
	// t_vec3	o;
	// double	product;
	double	radius;
	double	height_half = cyl->height / 2;

	r_c = cross_product(cyl->vector, ray->vector);
	c_c = minus(ray->place, cyl->center);
	c_c = cross_product(c_c, cyl->vector);
	radius = cyl->diameter / 2;	
	
	obj_data->a = dot_product(r_c, r_c);
	obj_data->b = 2.0 * dot_product(r_c, c_c);
	obj_data->c = dot_product(c_c, c_c) - pow(radius, 2);

	if (quadratic(obj_data) == true)
	{
		if (obj_data->t > EPSILON && check_closest(obj_data) == true)
		{
			double	t1 = ray->place.y + obj_data->root1 * ray->vector.y;
			double	t2 = ray->place.y + obj_data->root2 * ray->vector.y;
			if (t1 < (cyl->vector.y - height_half) || t1 > cyl->vector.y + height_half)
				obj_data->root1 = INFINITY;
			if (t2 < (cyl->vector.y - height_half) || t2 > cyl->vector.y + height_half)
				obj_data->root2 = INFINITY;
			obj_data->t = fmin(obj_data->root1, obj_data->root2);
			// using infinity here messes with the colour
			 // good colour with t > 0
			// if (obj_data->t > 0)
			if (obj_data->t == INFINITY)
				return (true);
			// else if (obj_data->t > 0) // capppyyy time
			// {
			// 	// solve_capps;
			// 	return (true);
			// }
			if (obj_data->t < 0) //- no intersection
				return (false);
		}
	}

// --------------------------------------------------------------------- //		
			
// // m = dot(ray->direction * scalar + (cyl->center - camera->origin), cyl->orientation);

// // update obj_data->t here somewhere for the caps but still don't fully understand that...
// 			m = mult_vecdub(ray->vector, obj_data->t);
// 			n = minus(cyl->center, ray->place);
// 			o = plus(m, n);
// 			product = dot_product(o, cyl->vector);
// 			if (fabs(product) <= cyl->height)
// 				return (true);
	return (false);
}

