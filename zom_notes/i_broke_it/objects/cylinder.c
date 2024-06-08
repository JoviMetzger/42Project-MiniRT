/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/08 14:23:09 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// checking more than zero for if behind

bool	check_caps(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	// obj->base = mult_vecdub(plus(cyl->center, cyl->vector), -cyl->height_half);
	// obj->top = mult_vecdub(plus(cyl->center, cyl->vector), cyl->height_half);

	// printf("base x: %f y: %f z: %f\n", obj->base.x, obj->base.y, obj->base.z);
	// printf("top x: %f y: %f z: %f\n", obj->top.x, obj->top.y, obj->top.z);
	// exit (EXIT_SUCCESS);
	
	t_objs	tmppl;
	bool	truth_or_dare = false;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->top;
	tmppl.vector = cyl->vector;
	if (intersect_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = mult_vecdub(ray->vector, obj->t);

		double distance = vec_length(obj->hit_pos, cyl->top);
		if (distance <= cyl->radius && obj->t > 0 && obj->t < obj->closest_t)
		{
			obj->closest_t = obj->t;
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
		if (distance <= cyl->radius && obj->t > 0 && obj->t < obj->closest_t)
		{
			obj->closest_t = obj->t;
			truth_or_dare = true;
		}
	}
	return (truth_or_dare);
}

bool	cut_ends(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	t_vec3	to_center;

	// ray->vector * t + ray->place - cyl->center

	to_center = plus(minus(ray->place, cyl->center), mult_vecdub(ray->vector, obj->t));
	if (fabs(dot_product(to_center, cyl->vector)) <= cyl->height_half)
		return (true);
	// obj->cut[0] = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
	// obj->cut[1] = plus(ray->place, mult_vecdub(ray->vector, obj->t));
	// if (obj->root1 > 0)
	// {
	// 	if (dot_product(cyl->vector, minus(obj->cut[1], cyl->center)) <= 0
	// 		|| dot_product(cyl->vector, minus(obj->cut[1], obj->cut[0])) >= 0)
	// 			obj->root1 = -1;
	// }
	// if (obj->root2 > 0)
	// {
	// 	if (dot_product(cyl->vector, minus(obj->cut[1], cyl->center)) <= 0
	// 		|| dot_product(cyl->vector, minus(obj->cut[1], obj->cut[0])) >= 0)
	// 		obj->root2 = -1;
	// }
	// if ((obj->root2 < obj->root1 && obj->root2 > 0)
	// 	|| (obj->root1 < obj->root2 && obj->root1 <= 0)) 
	// 	obj->t = obj->root2;
	// else
	// 	obj->t = obj->root1;
	// if (obj->t > 0 && obj->t >= cyl->height)
	// 		return (true);
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
	// cyl->center = normalize(cyl->center);
	// ray->vector = normalize(ray->vector);
 */
bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *obj)
{
	// mult vector height_half, minus center
	// cyl->base = mult_vecdub(plus(cyl->center, cyl->vector), -cyl->height_half);
	// cyl->top = mult_vecdub(plus(cyl->center, cyl->vector), cyl->height_half);

	cyl->base = plus(cyl->center, mult_vecdub(cyl->vector, -cyl->height_half));
	cyl->top = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height_half));

	// printf("base x: %f y: %f z: %f\n", obj->base.x, obj->base.y, obj->base.z);
	// printf("top x: %f y: %f z: %f\n", obj->top.x, obj->top.y, obj->top.z);
	// exit (EXIT_SUCCESS);
	set_points(obj, ray, cyl);
	if (quadratic(obj) == true)
	{
		if (cut_ends(obj, cyl, ray) == true)
		{
			if (check_caps(obj, cyl, ray) == true)
			{
				puts("HI");
				return (true);
			}
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
	// vars.normal = 

	vars.final_red = fmin(fmax(vars.final_red, obj->colour.r), 255);
	vars.final_green = fmin(fmax(vars.final_green, obj->colour.g), 255);
	vars.final_blue = fmin(fmax(vars.final_blue, obj->colour.b), 255);
	result.r = vars.final_red;
	result.g = vars.final_green;
	result.b = vars.final_blue;
	return (result);
}
