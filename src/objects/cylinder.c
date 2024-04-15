/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/15 22:16:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj_data)
{
	t_vec3	c_c;
	t_vec3	r_c;
	t_vec3	m;
	t_vec3	n;
	t_vec3	o;
	double	product;
	double	radius;

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
			
// m = dot(ray->direction * scalar + (cyl->center - camera->origin), cyl->orientation);

// update obj_data->t here somewhere for the caps but still don't fully understand that...
			m = mult_vecdub(ray->vector, obj_data->t);
			n = minus(cyl->center, ray->place);
			o = plus(m, n);
			product = dot_product(o, cyl->vector);
			if (fabs(product) <= cyl->height)
				return (true);
		}
	}
	return (false);
}

