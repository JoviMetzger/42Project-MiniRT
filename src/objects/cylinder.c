/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/01 14:52:18 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj_data)
{
	t_vec3	c_c;
	t_vec3	r_c;
	double	radius;
	double	height_half = cyl->height / 2;

	r_c = cross_product(cyl->vector, ray->vector);
	c_c = minus(ray->place, cyl->center);
	// c_c = cross_product(c_c, cyl->vector);
	radius = cyl->diameter / 2;	
	
	obj_data->a = dot_product(r_c, r_c);
	obj_data->b = -2.0 * dot_product(r_c, c_c);
	obj_data->c = dot_product(c_c, c_c) - pow(radius, 2);

	if (quadratic(obj_data) == true)
	{
		if (obj_data->t > EPSILON && check_closest(obj_data) == true)
		{
			double	hit1 = 0;
			double	hit2 = 0;
			double	t1 = ray->place.y + obj_data->root1 * ray->vector.y;
			double	t2 = ray->place.y + obj_data->root2 * ray->vector.y;
			if (t1 < (cyl->vector.y - height_half) || t1 > cyl->vector.y + height_half)
				hit1 = obj_data->root1;
				// obj_data->root1 = INFINITY;
			if (t2 < (cyl->vector.y - height_half) || t2 > cyl->vector.y + height_half)
				hit2 = obj_data->root2;
				// obj_data->t = obj_data->root2;
				// obj_data->root2 = INFINITY;
			obj_data->t = fmin(hit1, hit2);
			if (obj_data->t > 0)
			{
				// printf("here\n");
				// exit(EXIT_SUCCESS);
				// solve_capps
				double	denom = dot_product(ray->vector, cyl->vector);
				if (fabs(denom) > EPSILON)
				{
					t_vec3	oc = minus(ray->place, cyl->center);
					obj_data->t = -dot_product(oc, cyl->vector) / denom;
					if (obj_data->t >= cyl->height)
						return (check_closest(obj_data));
				}
				return (false);
			}
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





/**
 * 
 * with comments and print statements....
 * 
 * 
 * bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj_data)
{
	t_vec3	c_c;
	t_vec3	r_c;
	double	radius;
	double	height_half = cyl->height / 2;

	r_c = cross_product(cyl->vector, ray->vector);
	c_c = minus(ray->place, cyl->center);
	c_c = cross_product(c_c, cyl->vector);
	radius = cyl->diameter / 2;	
	
	obj_data->a = dot_product(r_c, r_c);
	obj_data->b = -2.0 * dot_product(r_c, c_c);
	obj_data->c = dot_product(c_c, c_c) - pow(radius, 2);

	if (quadratic(obj_data) == true)
	{
		if (obj_data->t > EPSILON && check_closest(obj_data) == true)
		{
			double	t1 = ray->place.y + obj_data->root1 * ray->vector.y;
			double	t2 = ray->place.y + obj_data->root2 * ray->vector.y;
			if (t1 < (cyl->vector.y - height_half) || t1 > cyl->vector.y + height_half)
				obj_data->t = obj_data->root1;
				// obj_data->root1 = INFINITY;
			else if (t2 < (cyl->vector.y - height_half) || t2 > cyl->vector.y + height_half)
				obj_data->t = obj_data->root2;
				// obj_data->root2 = INFINITY;
			// printf("root1 = %f | root2 = %f\n", obj_data->root1, obj_data->root2);
			// exit(EXIT_SUCCESS);
			// obj_data->t = fmin(obj_data->root1, obj_data->root2);
			// printf("t = %f\n", obj_data->t);
			// exit(EXIT_SUCCESS);
			// if (obj_data->t == INFINITY || obj_data->t == 0)
			// 	return (true);
			if (obj_data->t > 0)
			{
				// printf("here\n");
				// exit(EXIT_SUCCESS);
				// solve_capps
				double	denom = dot_product(ray->vector, cyl->vector);
				if (fabs(denom) > EPSILON)
				{
					t_vec3	oc = minus(ray->place, cyl->center);
					obj_data->t = -dot_product(oc, cyl->vector) / denom;
					if (obj_data->t >= EPSILON)
						return (check_closest(obj_data));
				}
				return (false);
			}
			else if (obj_data->t < 0) //- no intersection
				return (false);
		}
	}
 * 
 */