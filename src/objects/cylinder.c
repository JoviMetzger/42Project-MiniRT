/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/22 22:56:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// checking more than zero for if behind
		

bool	check_caps(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	t_objs	tmppl;
	bool	truth_or_dare = false;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->top;
	tmppl.vector = cyl->vector;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = mult_vecdub(ray->vector, obj->t);
	
		double distance = vec_length(cyl->top, obj->hit_pos);

		if (distance <= cyl->radius && obj->t > 0 && distance > 0)
		{
			puts("top");
			// cyl->normal = normalize_vector(cyl->vector);
			truth_or_dare = true;
		}
	}
	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->base;
	tmppl.vector = mult_vecdub(cyl->vector, -1);
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = mult_vecdub(ray->vector, obj->t);
		// printf("hit = %f %f %f\n", obj->hit_pos.x, obj->hit_pos.y, obj->hit_pos.z);
		double distance = vec_length(cyl->base, obj->hit_pos);

		// printf("radius = %f\n", cyl->radius);
		// printf("t = %f\n", obj->t);
		// printf("distance = %f\n", distance);
		// exit(EXIT_SUCCESS);
		if (distance <= cyl->radius && obj->t > 0 && distance > 0)
		{
			// puts("bottom");
			// cyl->normal = normalize_vector(mult_vecdub(cyl->vector, -1)); // yes? for opposite 
			truth_or_dare = true;
		}
	}
	return (truth_or_dare);
}


// ray->vector * t + ray->place - cyl->center
bool	cut_ends(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->to_center = plus(minus(ray->place, cyl->center), mult_vecdub(ray->vector, obj->t));
	if (fabs(dot_product(obj->to_center, cyl->vector)) <= cyl->height_half)
		return (true);
	return (false);
}

static void	set_points(t_hit_data *obj, t_ray *ray, t_objs *cyl)
{
	t_vec3	vector_cross;
	t_vec3	oc;

	vector_cross = cross_product(cyl->vector, ray->vector);
	oc = minus(ray->place, cyl->center);
	oc = cross_product(oc, ray->vector);
	obj->a = dot_product(vector_cross, vector_cross);
	obj->b = 2.0 * dot_product(vector_cross, oc);
	obj->c = dot_product(oc, oc) - pow(cyl->radius, 2);
}

/**
	// FOR BODY
	// The cylinder normal vector starts at the centerline of the 
	// cylinder at the same z-height of the point where the ray 
	// intersects the cylinder, ends at the radial point of intersection. 
	// Normalize it and you have your unit normal vector.
	
		to center = hit point minus cyl center
		new point = cyl center plus prod(to cent, cyl vec) times cyl vector
		normal = normalize new point

 */

static void	cyl_normal(t_ray *ray, t_objs *cyl, t_hit_data *obj)
{
	obj->hit_pos = mult_vecdub(ray->vector, obj->t);
	obj->to_center = minus(obj->hit_pos, cyl->center);
	obj->pnt = plus(cyl->center, mult_vecdub(cyl->vector, dot_product(obj->to_center, cyl->vector)));
	cyl->normal = normalize_vector(obj->pnt);

//------------------------------------------------------------------------------//

	// obj->hit_pos = mult_vecdub(ray->vector, obj->t);
	// obj->tmp_t = dot_product(minus(obj->hit_pos, cyl->center), cyl->vector);
	// obj->pnt = plus(cyl->center, mult_vecdub(cyl->vector, obj->tmp_t));
	// cyl->normal = normalize_vector(minus(ray->vector, obj->pnt));
}

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *obj)
{
	cyl->base = plus(cyl->center, mult_vecdub(cyl->vector, -cyl->height_half));
	cyl->top = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height_half));
	set_points(obj, ray, cyl);
	if (quadratic(obj) == true)
	{
		if (cut_ends(obj, cyl, ray) == true)
		{
			cyl_normal(ray, cyl, obj);
			if (check_caps(obj, cyl, ray) == true) // separate into two funcs, check the hits
			{
				// puts("HI");
				return (check_closest(obj));
				// return (true); // see weird middle plane cause NOT CLOSEST
			}
			return (check_closest(obj));
			// return (true);
		}
	}
	return (false);
}
