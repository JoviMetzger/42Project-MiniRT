/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/14 18:21:36 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	t_vec3	hit[2];
	t_vec3	cap[2];
	t_vec3	og_pnt[2];
	double dist1;
	double dist2;
	double hit1 = 0;
	double hit2 = 0;
	double	denom;
	// (void) obj;

	denom = dot_product(ray->vector, cyl->vector);
	if (denom == 0 || fabs(denom) < 0)
		return (false);
	
	obj->hit1 = cyl->height;
	obj->hit2 = -cyl->height;
	og_pnt[0] = minus(ray->place, plus(cyl->center, mult_vecdub(cyl->vector, obj->hit1)));
	og_pnt[1] = minus(ray->place, plus(cyl->center, mult_vecdub(cyl->vector, obj->hit2)));
	
	dist1 = -dot_product(og_pnt[0], cyl->vector) / denom;
	dist2 = -dot_product(og_pnt[1], cyl->vector) / denom;

	if (dist1 < 0 && dist2 < 0)
		return (false);
	
	if (dist1 >= 0)
	{
		hit[0] = mult_vecdub(ray->vector, dist1);
		cap[0] = plus(cyl->center, mult_vecdub(cyl->vector, obj->hit1));
		hit1 =(fabs(distance(hit[0], cap[0])) <= obj->radius);
		obj->t = hit1;
	}
	if (dist2 >= 0)
	{
		hit[1] = mult_vecdub(ray->vector, dist2);
		cap[1] = plus(cyl->center, mult_vecdub(cyl->vector, obj->hit2));
		hit2 =(fabs(distance(hit[1], cap[1])) <= obj->radius);
		obj->t = hit2;
	}
	if (!hit1 && !hit2)
		return (false);
	if ((hit1 && hit2 && dist2 < dist1) || !hit1)
	{
		// dist1 = dist2;
		// obj->hit1 = obj->hit2;
		obj->t =  obj->hit2;
	}
	return (true);

}

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

static void	set_points(t_obj_data *obj, t_ray *ray, t_objs *cyl)
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
			if (check_roots(obj, cyl, ray) == true)
			{
				obj->tmp_t = obj->t;
				if (check_caps(obj, cyl, ray) == true)
				{
					// printf("yeah cap\n");
					// exit(EXIT_SUCCESS);
					return (check_closest(obj));
				}
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
