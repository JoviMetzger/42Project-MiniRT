/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/10 20:38:19 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"


static bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
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
		return (true);
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
				// im missing the cappy plany bit
				// if (intersect_plane(ray, cyl, obj))
				return (check_closest(obj));
			}
		}
	}
	return (false);
}
