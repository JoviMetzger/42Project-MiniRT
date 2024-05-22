/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/22 18:54:58 by smclacke      ########   odam.nl         */
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
		double distance = -vec_length(cyl->top, obj->hit_pos);
		
		// printf("radius = %f\n", cyl->radius);
		// printf("t = %f\n", obj->t);
		// printf("closest = %f\n", obj->closest_t);
		// printf("hit = %f %f %f\n", obj->hit_pos.x, obj->hit_pos.y, obj->hit_pos.z);
		// printf("distance = %f\n", distance);
		// exit(EXIT_SUCCESS);
		if (distance <= cyl->radius && obj->t > 0) // && obj->t <= obj->closest_t - in plane calculation
		{
			// puts("top");
			// obj->closest_t = obj->t;
			cyl->normal = normalize_vector(cyl->vector);
			truth_or_dare = true;
		}
	}
	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->base;
	tmppl.vector = mult_vecdub(cyl->vector, -1);
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = mult_vecdub(ray->vector, obj->t);
		double distance = vec_length(cyl->base, obj->hit_pos);

		if (distance <= cyl->radius && obj->t > 0)
		{
			// puts("bottom");
			// obj->closest_t = obj->t;
			cyl->normal = normalize_vector(mult_vecdub(cyl->vector, -1)); // yes? for opposite 
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
	// oc = minus(cyl->center, ray->place);
	oc = minus(ray->place, cyl->center);
	// oc = cross_product(oc, cyl->vector);
	oc = cross_product(oc, ray->vector); // andersom?
	obj->a = dot_product(vector_cross, vector_cross);
	obj->b = 2.0 * dot_product(vector_cross, oc);
	obj->c = dot_product(oc, oc) - pow(cyl->radius, 2);
}

static void	cyl_normal(t_ray *ray, t_objs *cyl, t_hit_data *obj)
{
	// FOR BODY
	// normal bullshit
	// The cylinder normal vector starts at the centerline of the 
	// cylinder at the same z-height of the point where the ray 
	// intersects the cylinder, ends at the radial point of intersection. 
	// Normalize it and you have your unit normal vector.
	obj->hit_pos = mult_vecdub(ray->vector, obj->t);

	obj->tmp_t = dot_product(minus(obj->hit_pos, cyl->center), cyl->vector);
	obj->pnt = plus(cyl->center, mult_vecdub(cyl->vector, obj->tmp_t));
	cyl->normal = normalize_vector(minus(ray->vector, obj->pnt));
}

/**
 * after checking roots, save t in tmp, check if body or cap, if body, use og t, otherwise
 * if cap, use updated t 
	// when how what where normalize?
	// cyl->center = normalize_vector(cyl->center);
	// ray->vector = normalize_vector(ray->vector);
 */
bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *obj)
{
	cyl->base = plus(cyl->center, mult_vecdub(cyl->vector, -cyl->height_half));
	cyl->top = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height_half));
	set_points(obj, ray, cyl);
	if (quadratic(obj) == true)
	{
		if (cut_ends(obj, cyl, ray) == true)
		{
			// if (check_caps(obj, cyl, ray) == true)
			// {
			// 	// puts("HI");
			// 	return (true);
			// }
			cyl_normal(ray, cyl, obj);
			return (check_closest(obj));
		}
	}
	return (false);
}
