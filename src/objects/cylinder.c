/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/14 21:13:19 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = obj->top;
	tmppl.vector = cyl->vector;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		if (vec_length(obj->hit_pos, obj->top) <= obj->radius)
			return (true);
	}
	
	// do same for base...
	// ft_bzero(&tmppl, sizeof(t_objs));
	// tmppl.center = obj->base;
	// tmppl.vector = cyl->vector;
	// if (intersect_plane(ray, &tmppl, obj) == true)
	// {
	// 	if (vec_length(obj->top, obj->hit_pos) <= obj->radius)
	// 		return (true);
	// }
	return (false);
}

bool	cut_chop(t_obj_data *obj, t_objs *cyl, t_ray *ray)
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

static void	set_points(t_obj_data *obj, t_ray *ray, t_objs *cyl)
{
	t_vec3	vector_cross;
	t_vec3	to_cyl_center;

	obj->radius = cyl->diameter / 2;
	obj->height_half = cyl->height / 2;
	vector_cross = cross_product(cyl->vector, ray->vector);
	to_cyl_center = minus(ray->place, cyl->center);
	to_cyl_center = cross_product(to_cyl_center, cyl->vector);
	obj->a = dot_product(vector_cross, vector_cross);
	obj->b = -2.0 * dot_product(vector_cross, to_cyl_center);
	obj->c = dot_product(to_cyl_center, to_cyl_center) - pow(obj->radius, 2);

//------//

	obj->base = mult_vecdub(minus(cyl->center, cyl->vector), cyl->height / 2);
	obj->top = mult_vecdub(plus(cyl->center, cyl->vector), cyl->height / 2);
	
	obj->denom = dot_product(ray->vector, cyl->vector);
	obj->distance = dot_product(obj->top, cyl->vector) / obj->denom;
	obj->hit_pos = plus(ray->place, mult_vecdub(ray->vector, obj->distance));

	obj->normal = normalize_vector(cyl->vector);

}

/**
 * after checking roots, save t in tmp, check if body or cap, if body, use og t, otherwise
 * if cap, use updated t 
 */
bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
{
	set_points(obj, ray, cyl);
	if (quadratic(obj) == true)
	{
		if (obj->t > EPSILON)
		{	
			if (cut_chop(obj, cyl, ray) == true)
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
