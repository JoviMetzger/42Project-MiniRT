/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/10 19:59:51 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

static void	check_hit(double root, t_objs *cyl, t_ray *ray, t_obj_data *obj)
{
	t_vec3	a;
	t_vec3	b;

	b = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
	a = plus(ray->place, mult_vecdub(ray->vector, obj->t));

	if (dot_product(cyl->vector, minus(a, cyl->center)) <= 0)
		root = -1;
	if (dot_product(cyl->vector, minus(a, b)) >= 0)
		root = -1;
}	

static t_vec3 good_norm(t_vec3 normal, t_ray *ray)
{
	if (dot_product(normal, ray->vector) > EPSILON)
		normal = mult_vecdub(normal, -1);
	return (normal);
}

static t_vec3 cyl_norm(t_vec3 hit, t_ray *ray, t_objs *cyl)
{
	t_vec3 ctp;
	t_vec3 normal;

	ctp = minus(hit, cyl->center);
	normal = minus(ctp, mult_vecdub(cyl->vector, dot_product(cyl->vector, ctp)));
	normalize_vector(normal);
	return (good_norm(normal, ray));
}

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
{
	t_vec3	aaa;
	t_vec3	right;

	aaa = minus(ray->vector, mult_vecdub(cyl->vector, dot_product(ray->vector, cyl->vector)));
	obj->a = dot_product(aaa, aaa);
	
	right = minus(minus(ray->place, cyl->center), mult_vecdub(cyl->vector, dot_product(minus(ray->place, cyl->center), cyl->vector)));
	obj->b = 2.0 * dot_product(aaa, right);
	
	obj->c = dot_product(right, right) - (obj->radius * obj->radius);

	if (quadratic(obj) == false)
		return (false);
	if (obj->root1 > 0)
		check_hit(obj->root1, cyl, ray, obj);
	if (obj->root2 > 0)
		check_hit(obj->root2, cyl, ray, obj);
	if (obj->root1 < 0 && obj->root2 < 0)
		return (false);
	if ((obj->root2 < obj->root1 && obj->root2 > 0) || (obj->root1 < obj->root2 && obj->root1 <= 0)) 
		obj->t = obj->root2;
	else
		obj->t = obj->root1;
	t_vec3 hit = plus(ray->place, mult_vecdub(ray->vector, obj->t));
	cyl->center = cyl_norm(hit, ray, cyl);
	return (check_closest(obj));
}
