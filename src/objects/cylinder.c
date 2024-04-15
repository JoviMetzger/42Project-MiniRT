/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/15 18:45:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// dont have to have objects ... parser todo

static	bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj_data)
{
	t_vec3	c = // cyl->center - height // start cap cylinder
	t_vec3	v = cyl->vector;
	double	radius = cyl->diameter / 2;
	t_vec3	maxm  = 	// cyl->center + height // following vector from center point to end heigt		// cylinder's end ap point
}
m = distance from base (C);
t = distance to hit location;
D = ray->direction;
V = cylinder->orientation;
X = vector (line) from camera to center of cylinder;


m = dot(ray->direction * scalar + (cyl->center - camera->origin), cyl->orientation);


a = 1 - pow(dot(ray->dir, cyl->orientation), 2);
b = 2 * (dot(ray->dir, X) - dot(ray->dir, cyl->orientation) * dot(X, cyl->orientation);
c = dot(X, X) - pow(dot(X, cyl->orientation), 2) - pow(cyl->radius, 2);
/**
	// cylinder->center = position
	// cylinder->vector = direction
	// ray place = origin
	// ray vector = direction
 */
// static bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
// {
// 	t_vec3	ray_og = ray->place;
// 	t_vec3	ray_dir = ray->vector;
// 	double	radius = cylinder->diameter / 2;
// 	double	height_half = cylinder->height / 2;
// 	t_vec3	oc = minus(ray_og, cylinder->center);


// 	// calculation of coefficients for quadratic equation
// // ------------- og almost working ------------/
// 	// obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
// 	// obj_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector);
// 	// obj_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);
// // ------------- og almost working ------------/
	
	
// 	obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
// 	obj_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(ray_dir, cylinder->vector);
// 	obj_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);

// 	// discriminant, solve the quadratic equation
// 	obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;


// 	// check for intersection
// 	if (obj_data->d < 0)
// 		return (false); // no intersection

// 	// calcuate roots of quadratic equation
// 	obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2.0 * obj_data->a);
// 	obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2.0 * obj_data->a);


// 	//check if intersection point is within the cpaped ends of the cylinder
// 	//cylinder formulia = ray_ogirin (Y) + t * ray_direction (Y) 
// 	double t1 = ray_og.y + obj_data->root1 * ray_dir.y;
// 	double t2 = ray_og.y + obj_data->root2 * ray_dir.y;
	
// 	// set roots.. if not within caps, set to infinity (oder?)
// 	if (t1 < (cylinder->vector.y - height_half) || t1 > (cylinder->vector.y + height_half))
// 		obj_data->root1 = INFINITY;
// 	if (t2 < (cylinder->vector.y - height_half) || t2 > (cylinder->vector.y + height_half))
// 		obj_data->root2 = INFINITY;

// 	obj_data->t = fmin(obj_data->root1, obj_data->root2); // returns the smaller double
// 	if (obj_data->t > 0)
// 		return (true); // intersection found
// 	return (false); // no intersection
// }

bool	calc_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
{
	if (intersect_cylinder(ray, cylinder, obj_data))
	{
		if (obj_data->t < obj_data->closest_t)
		{
			obj_data->closest_t = obj_data->t;
			return (true);
		}
	}
	return (false);
}
