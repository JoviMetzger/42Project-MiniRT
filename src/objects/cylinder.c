/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/15 20:33:40 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj_data)
{
	

	
	// if (quadratic(obj_data) == true)
	// 	return (check_closest(obj_data));
	// return (false);
}



// 	t_vec3	c = // cyl->center - height // start cap cylinder
// 	t_vec3	v = cyl->vector;
// 	double	radius = cyl->diameter / 2;
// 	t_vec3	maxm  = 	// cyl->center + height // following vector from center point to end heigt		// cylinder's end ap point


	
// m = distance from base (C);
// t = distance to hit location;
// D = ray->direction;
// V = cylinder->orientation;
// X = vector (line) from camera to center of cylinder;


// m = dot(ray->direction * scalar + (cyl->center - camera->origin), cyl->orientation);


// a = 1 - pow(dot(ray->dir, cyl->orientation), 2);
// b = 2 * (dot(ray->dir, X) - dot(ray->dir, cyl->orientation) * dot(X, cyl->orientation);
// c = dot(X, X) - pow(dot(X, cyl->orientation), 2) - pow(cyl->radius, 2);

// obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;

// now quad it
