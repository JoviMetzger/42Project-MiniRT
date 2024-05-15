/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/15 20:50:33 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
// {
// 	// (void) obj;
// 	double	t;


// 	// bottom
// 	t = (cyl->center.y - ray->place.y) / ray->vector.y;
// 	if (t > 0)
// 	{
// 		t_vec3 inter_pnt = {ray->place.x + t * ray->vector.x, ray->place.y + t * ray->vector.y, ray->place.z + t * ray->vector.z};
// 		if (inter_pnt.x >= cyl->center.x - cyl->radius && inter_pnt.x <= cyl->center.x + cyl->radius &&
// 			inter_pnt.z >= cyl->center.z - cyl->radius && inter_pnt.z <= cyl->center.z + cyl->radius)
// 			{
// 				obj->t = t;
// 				return (true);
// 			}
// 	}
// 	// top
// 	t = (cyl->center.y + cyl->height - ray->place.y) / ray->vector.y;
// 	if (t > 0)
// 	{
// 		t_vec3 inter_pnt2 = {ray->place.x + t * ray->vector.x, ray->place.y + t * ray->vector.y, ray->place.z + t * ray->vector.z};
// 		if (inter_pnt2.x >= cyl->center.x - cyl->radius && inter_pnt2.x <= cyl->center.x + cyl->radius &&
// 			inter_pnt2.z >= cyl->center.z - cyl->radius && inter_pnt2.z <= cyl->center.z + cyl->radius)	
// 			{
// 				obj->t = t;
// 				return (true);
// 			}
// 	}
// 	return (false);
// }

bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	// cyl->vector = normalize_vector(cyl->vector);
	// ray->vector = normalize_vector(ray->vector);
	// obj->base = plus(cyl->center, mult_vecdub(cyl->vector, -cyl->height / 2));
	// obj->top = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height / 2));
	obj->base = mult_vecdub(plus(cyl->center, cyl->vector), -cyl->height / 2);
	obj->top = mult_vecdub(plus(cyl->center, cyl->vector), cyl->height / 2);

	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = obj->top;
	tmppl.vector = cyl->vector;
	double tmp = obj->t;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = plus(ray->place, mult_vecdub(ray->vector, obj->t));
		if (vec_length(obj->hit_pos, obj->top) <= cyl->radius)
				return (true);
	}
	obj->t = tmp;
	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = obj->base;
	tmppl.vector = cyl->vector;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = plus(ray->place, mult_vecdub(ray->vector, obj->t));
		if (vec_length(obj->hit_pos, obj->base) <= cyl->radius)
		{
			if (obj->t <= cyl->height) 
				return (true);
		}
	}
	return (false);
}

bool	cut_ends(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->cut[0] = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
	obj->cut[1] = plus(ray->place, mult_vecdub(ray->vector, obj->t));	
	if ((obj->root1 > 0) && (dot_product(cyl->vector, minus(obj->cut[1], cyl->center)) <= 0
		|| dot_product(cyl->vector, minus(obj->cut[1], obj->cut[0])) >= 0))
		obj->root1 = -1;	
	if ((obj->root2 > 0) && (dot_product(cyl->vector, minus(obj->cut[1], cyl->center)) <= 0
		|| dot_product(cyl->vector, minus(obj->cut[1], obj->cut[0])) >= 0))
		obj->root2 = -1;
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

	vector_cross = cross_product(cyl->vector, ray->vector);
	to_cyl_center = minus(ray->place, cyl->center);
	to_cyl_center = cross_product(to_cyl_center, cyl->vector);
	obj->a = dot_product(vector_cross, vector_cross);
	obj->b = -2.0 * dot_product(vector_cross, to_cyl_center);
	obj->c = dot_product(to_cyl_center, to_cyl_center) - pow(cyl->radius, 2);
}

/**
 * after checking roots, save t in tmp, check if body or cap, if body, use og t, otherwise
 * if cap, use updated t 
 */
bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
{
	// when how what where normalize?
	// cyl->center = normalize_vector(cyl->center);
	// ray->vector = normalize_vector(ray->vector);

	obj->tmp_t = 0;
	set_points(obj, ray, cyl);
	if (quadratic(obj) == true)
	{
		if (obj->t > EPSILON)
		{
			if (cut_ends(obj, cyl, ray) == true)
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
