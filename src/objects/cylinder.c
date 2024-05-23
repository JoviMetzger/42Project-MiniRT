/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/23 19:29:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// bool	check_caps(t_hit_data *obj, t_objs *cyl, t_ray *ray)
// {
// 	cyl->base = plus(cyl->center, mult_vecdub(cyl->vector, -cyl->height_half));
// 	cyl->top = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height_half));
// 	// printf("base = %f %f %f\n", cyl->base.x,  cyl->base.y,  cyl->base.z);
// 	// printf("top = %f %f %f\n", cyl->top.x,  cyl->top.y,  cyl->top.z);
// 	// exit(EXIT_SUCCESS);
// 	t_objs	tmppl;
// 	bool	truth_or_dare = false;

// 	ft_bzero(&tmppl, sizeof(t_objs));
// 	tmppl.center = cyl->top;
// 	tmppl.vector = cyl->vector;
// 	if (intersect_plane(ray, &tmppl, obj) == true)
// 	{
// 		obj->hit_pos = mult_vecdub(ray->vector, obj->t);
	
// 		double distance = vec_length(cyl->top, obj->hit_pos);

// 		if (distance <= cyl->radius && obj->t > 0 && distance > 0)
// 		{
// 			puts("top");
// 			cyl->normal = normalize_vector(cyl->vector);
// 			// cyl->normal = cyl->vector;
// 			truth_or_dare = true;
// 		}
// 	}
// 	ft_bzero(&tmppl, sizeof(t_objs));
// 	tmppl.center = cyl->base;
// 	tmppl.vector = mult_vecdub(cyl->vector, -1);
// 	if (intersect_plane(ray, &tmppl, obj) == true)
// 	{
// 		obj->hit_pos = mult_vecdub(ray->vector, obj->t);
// 		// printf("hit = %f %f %f\n", obj->hit_pos.x, obj->hit_pos.y, obj->hit_pos.z);
// 		double distance = vec_length(cyl->base, obj->hit_pos);

// 		// printf("radius = %f\n", cyl->radius);
// 		// printf("t = %f\n", obj->t);
// 		// printf("distance = %f\n", distance);
// 		// exit(EXIT_SUCCESS);
// 		if (distance <= cyl->radius && obj->t > 0 && distance > 0)
// 		{
// 			// puts("bottom");
// 			cyl->normal = normalize_vector(mult_vecdub(cyl->vector, -1)); // yes? for opposite 
// 			// cyl->normal = mult_vecdub(cyl->vector, -1); // yes? for opposite 
// 			truth_or_dare = true;
// 		}
// 	}
// 	return (truth_or_dare);
// }


// // // ray->vector * t + ray->place - cyl->center
// // bool	cut_ends(t_hit_data *obj, t_objs *cyl, t_ray *ray)
// // {
// // 	obj->to_center = plus(minus(ray->place, cyl->center), mult_vecdub(ray->vector, obj->t));
// // 	if (fabs(dot_product(obj->to_center, cyl->vector)) <= cyl->height_half)
// // 		return (true);
// // 	return (false);
// // }



// static bool	check_roots(t_hit_data *obj, t_objs *cyl, t_ray *ray)
// {
// 	obj->cut[0] = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
// 	obj->cut[1] = plus(ray->place, mult_vecdub(ray->vector, obj->t));
// 	if (obj->root1 > 0)
// 	{
// 		if (dot_product(cyl->vector, minus(obj->cut[1], cyl->center)) <= 0
// 			|| dot_product(cyl->vector, minus(obj->cut[1], obj->cut[0])) >= 0)
// 				obj->root1 = -1;
// 	}
// 	if (obj->root2 > 0)
// 	{
// 		if (dot_product(cyl->vector, minus(obj->cut[1], cyl->center)) <= 0
// 			|| dot_product(cyl->vector, minus(obj->cut[1], obj->cut[0])) >= 0)
// 			obj->root2 = -1;
// 	}
// 	if ((obj->root2 < obj->root1 && obj->root2 > 0)
// 		|| (obj->root1 < obj->root2 && obj->root1 <= 0)) 
// 		obj->t = obj->root2;
// 	else
// 		obj->t = obj->root1;
// 	if (obj->t > 0 && obj->t >= cyl->height)
// 			return (true);
// 	return (false);

// }

// static void	set_points(t_hit_data *obj, t_ray *ray, t_objs *cyl)
// {
// 	t_vec3	vector_cross;
// 	t_vec3	oc;

// 	vector_cross = cross_product(cyl->vector, ray->vector);
// 	oc = minus(ray->place, cyl->center);
// 	// oc = cross_product(oc, ray->vector); // cyl | ray
// 	oc = cross_product(oc, cyl->vector); // cyl | ray
// 	obj->a = dot_product(vector_cross, vector_cross);
// 	obj->b = 2.0 * dot_product(vector_cross, oc); // negative
// 	obj->c = dot_product(oc, oc) - pow(cyl->radius, 2);
// }

// /**
// 	// FOR BODY
// 	// The cylinder normal vector starts at the centerline of the 
// 	// cylinder at the same z-height of the point where the ray 
// 	// intersects the cylinder, ends at the radial point of intersection. 
// 	// Normalize it and you have your unit normal vector.
	
// 		to center = hit point minus cyl center
// 		new point = cyl center plus prod(to cent, cyl vec) times cyl vector
// 		normal = normalize new point

//  */

// static void	cyl_normal(t_ray *ray, t_objs *cyl, t_hit_data *obj)
// {
// 	obj->hit_pos = mult_vecdub(ray->vector, obj->t);
// 	obj->to_center = minus(obj->hit_pos, cyl->center);
// 	obj->pnt = plus(cyl->center, mult_vecdub(cyl->vector, dot_product(obj->to_center, cyl->vector)));
// 	cyl->normal = normalize_vector(obj->pnt);
// }

// bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *obj)
// {
// 	set_points(obj, ray, cyl);
// 	if (quadratic(obj) == true)
// 	{
// 		// if (cut_ends(obj, cyl, ray) == true)
// 		if (check_roots(obj, cyl, ray) == true)
// 		{
// 			puts("hello");
// 			// obj->hit_pos = mult_vecdub(ray->vector, obj->t);
// 			// cyl->normal = normalize_vector(minus(obj->hit_pos, cyl->center));
// 			cyl_normal(ray, cyl, obj);
// 			// if (check_caps(obj, cyl, ray) == true) // separate into two funcs, check the hits
// 			// {
// 			// 	// return (check_closest(obj));
// 			// 	return (true); // see weird middle plane cause NOT CLOSEST
// 			// }
// 			return (check_closest(obj));
// 			// return (true);
// 		}
// 	}
// 	return (false);
// }



// origin.x^2 + origin.z^2 <= radius^2 and -height/2 <= origin.y <= height/2

// ray.place.x^2 + ray.place.z^2 <= radius^2 and -height/2 <= ray.place.y <= height/2

/**
 *	t_vec3	oc;
	double denom;

	denom = dot_product(ray->vector, plane->vector);
	if (fabs(denom) > EPSILON)
	{
		oc = minus(plane->center, ray->place);
		hit_data->t = dot_product(oc, plane->vector) / denom;
		if (hit_data->t >= EPSILON)
			return (check_closest(hit_data)); 
	}
 */

bool	check_caps(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	// cyl->base = mult_vecdub(minus(cyl->center, cyl->vector), cyl->height_half);
	// cyl->top = mult_vecdub(plus(cyl->center, cyl->vector), cyl->height_half);
	cyl->base = plus(cyl->center, mult_vecdub(cyl->vector, -cyl->height_half));
	cyl->top = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height_half));
	// printf("base = %f %f %f\n", cyl->base.x,  cyl->base.y,  cyl->base.z);
	// printf("top = %f %f %f\n", cyl->top.x,  cyl->top.y,  cyl->top.z);
	// exit(EXIT_SUCCESS);

	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->top;
	tmppl.vector = cyl->vector;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		// obj->hit_pos = normalize_vector(mult_vecdub(cyl->vector, obj->t));
		obj->hit_pos = mult_vecdub(ray->vector, obj->t);
		
		// printf("hit = %f %f %f\n", obj->hit_pos.x, obj->hit_pos.y, obj->hit_pos.z);
		// double distance = vec_length(obj->hit_pos, cyl->top);
		double distance = vec_length(cyl->top, obj->hit_pos);
		// printf("radius = %f\n", cyl->radius);
		// printf("t = %f\n", obj->t);
		// printf("distance = %f\n", distance);
		// exit(EXIT_SUCCESS);

		if (distance <= cyl->radius)
		{
			return (true);
		}
	}
	// ft_bzero(&tmppl, sizeof(t_objs));
	// tmppl.center = cyl->base;
	// tmppl.vector = cyl->vector;
	// if (intersect_plane(ray, &tmppl, obj) == true)
	// {
	// 	obj->hit_pos = mult_vecdub(ray->vector, obj->t);

	// 	double distance = vec_length(obj->hit_pos, cyl->base);
	// 	if (distance <= cyl->radius)
	// 	{
	// 		return (true);
	// 	}
	// }
	return (false);
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
	oc = minus(cyl->center, ray->place);
	oc = cross_product(oc, cyl->vector);
	obj->a = dot_product(vector_cross, vector_cross);
	obj->b = 2.0 * dot_product(vector_cross, oc);
	obj->c = dot_product(oc, oc) - pow(cyl->radius, 2);
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
	set_points(obj, ray, cyl);
	if (quadratic(obj) == true)
	{
		obj->tmp_t = obj->t;
		if (cut_ends(obj, cyl, ray) == true)
		{
			if (check_caps(obj, cyl, ray) == true)
				return (check_closest(obj));
			else
			{
				obj->t = obj->tmp_t;
				return (check_closest(obj));
			}
			return (check_closest(obj));
		}
	}
	return (false);
}
