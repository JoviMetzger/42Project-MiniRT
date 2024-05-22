/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/22 17:12:10 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

		// printf("hit = %f %f %f | t = %f\n", obj->hit_pos.x, obj->hit_pos.y, obj->hit_pos.z, obj->t);
		// printf("closest = %f\n", obj->closest_t);
		// printf("distance = %f\n", distance);
		// printf("radius = %f\n", cyl->radius);
		// exit(EXIT_SUCCESS);
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
		double distance = vec_length(obj->hit_pos, cyl->top);
		if (distance <= cyl->radius && obj->t > 0 && obj->t <= obj->closest_t)
		{
			puts("top");
			obj->closest_t = obj->t;
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

		double distance = vec_length(obj->hit_pos, cyl->base);
		if (distance <= cyl->radius && obj->t > 0 && obj->t <= obj->closest_t)
		{
			puts("bottom");
			obj->closest_t = obj->t;
			cyl->normal = normalize_vector(mult_vecdub(cyl->vector, -1)); // yes? for opposite 
			truth_or_dare = true;
		}
	}
	return (truth_or_dare);
}


// ray->vector * t + ray->place - cyl->center
bool	cut_ends(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	// t_vec3	to_center;

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
	// mult vector height_half, minus center
	// cyl->base = mult_vecdub(plus(cyl->center, cyl->vector), -cyl->height_half);
	// cyl->top = mult_vecdub(plus(cyl->center, cyl->vector), cyl->height_half);

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
			//  t = dot((hit_pt - cy.bottom_center), cy.ori); // cy.ori should be normalized and so has the length of 1.

			// normal of body
			obj->tmp_t = dot_product(minus(obj->hit_pos, cyl->center), cyl->vector);
			obj->pnt = plus(cyl->center, mult_vecdub(cyl->vector, obj->tmp_t));
			cyl->normal = normalize_vector(minus(obj->hit_pos, obj->pnt));
			return (check_closest(obj));
		}
	}
	return (false);
}


// Clamp final values to [0, 255]
t_colour	get_cy_colour(t_data *data, t_hit_data *hit, t_ray ray, t_objs *obj)
{
	t_colour		result;
	t_colour_vars	vars;
	
	ft_bzero(&vars, sizeof(t_colour_vars));
	vars.inter_point = plus(ray.place, mult_vecdub(ray.vector, hit->t));
	get_colour(data, &vars, ray);

	// bewaar normal ook in obj struct
	// need cylinder
	vars.normal = obj->normal;

	vars.final_red = fmin(fmax(vars.final_red, obj->colour.r), 255);
	vars.final_green = fmin(fmax(vars.final_green, obj->colour.g), 255);
	vars.final_blue = fmin(fmax(vars.final_blue, obj->colour.b), 255);
	result.r = vars.final_red;
	result.g = vars.final_green;
	result.b = vars.final_blue;
	return (result);
}
