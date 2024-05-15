/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/15 16:17:14 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**

	cylinder's center at (-3, 0, -20) and height 3, 

	Base Vector:

	the base vector should be (x=0, y=-1.5, z=10.5) relative to the cylinder's center.
	Adding this to the center coordinates gives (x=-3, y=-1.5, z=-9.5), 
	which matches with your provided coordinates.

	Top Vector:

	the top vector should be (x=0, y=1.5, z=-10.5) relative 
	to the cylinder's center.
	Adding this to the center coordinates gives (x=-3, y=1.5, z=-30.5), 
	which matches with your provided coordinates.

*/

bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->base = mult_vecdub(minus(cyl->vector, cyl->center), (cyl->height / 2));
	obj->top = mult_vecdub(plus(cyl->vector, cyl->center), (cyl->height / 2));

	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = obj->top;
	tmppl.vector = cyl->vector;
	double tmp = obj->t;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = plus(ray->place, mult_vecdub(ray->vector, obj->t));
		if (vec_length(obj->hit_pos, obj->top) <= cyl->radius)
		{
			if (obj->t > 0) 
				return (true);
		}
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
			if (obj->t > 0) 
				return (true);
		}
	}
	return (false);
}

// #Identifier     #Coordinates        #3D vector      #Diameter       #Height
// cy              -7,-1,-20           0.0,0.0,1.0         4               8
// e = -6.599499, 0.959489, -7.602938 | f = -7.000000, -1.000000, -12.000000
// e = -6.599499, 0.959489, -7.602938 | f = -7.000000, -1.000000, -12.000000
	// printf("e = %f, %f, %f | f = %f, %f, %f\n", obj->e.x, obj->e.y, obj->e.z, obj->f.x, obj->f.y, obj->f.z);
	// exit(EXIT_SUCCESS);
bool	cut_ends(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->cut[0] = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
	obj->cut[1] = plus(ray->place, mult_vecdub(ray->vector, obj->t));
	if (obj->root1 > 0)
	{	
		if (dot_product(cyl->vector, minus(obj->cut[1], cyl->center)) <= 0
			|| dot_product(cyl->vector, minus(obj->cut[1], obj->cut[0])) >= 0)
			obj->root1 = -1;
	}
	if (obj->root2 > 0)
	{	
		if (dot_product(cyl->vector, minus(obj->cut[1], cyl->center)) <= 0
			|| dot_product(cyl->vector, minus(obj->cut[1], obj->cut[0])) >= 0)
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
