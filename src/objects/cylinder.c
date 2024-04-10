/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/10 21:58:27 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
// ------------ pretty good --------- //
---------- 1 -----------------
	// obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
	// obj_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector);
	// obj_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - radius * radius;
	
---------- 2 -----------------
	// obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
	// obj_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector);
	// obj_data->c = dot_product(oc, oc) - dot_product(ray_dir, oc) * dot_product(ray_dir, oc) - radius * radius;
 *  
 */
bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
{
	t_vec3	ray_og = ray->place;
	t_vec3	ray_dir = ray->vector;
	t_vec3	oc = minus(ray_og, cylinder->center); // vector
	double	radius = cylinder->diameter / 2;
	double	height_half = cylinder->height / 2;

	// calculation of coefficients for quadratic equation
	obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
	obj_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector);
	obj_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - radius * radius;
	
	// obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
	// obj_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector);
	// obj_data->c = dot_product(oc, oc) - dot_product(ray_dir, oc) * dot_product(ray_dir, oc) - radius * radius;


	// discriminant, solve the quadratic
	obj_data->d = obj_data->b * obj_data->b - 4 * (obj_data->a * obj_data->c);


	// check for intersection
	if (obj_data->d < 0)
		return (false); // no intersection
	else
	{
		// calcuate roots of quadratic equation
		obj_data->d = sqrt(obj_data->d);
		obj_data->root1 = (-obj_data->b - obj_data->d) / obj_data->a; // just div a || (2 * obj_data->a)
		obj_data->root2 = (-obj_data->b + obj_data->d) / obj_data->a;
	}

	//check if intersection point is within the cpaped ends of the cylinder
	double t1 = ray_og.y + obj_data->root1 * ray_dir.y;
	double t2 = ray_og.y + obj_data->root2 * ray_dir.y;
	

	if (t1 < (cylinder->vector.y - height_half) || t1 > (cylinder->vector.y + height_half))
		obj_data->root1 = INFINITY;
	if (t2 < (cylinder->vector.y - height_half) || t2 > (cylinder->vector.y + height_half))
		obj_data->root2 = INFINITY;

	obj_data->t = fmin(obj_data->root1, obj_data->root2);
	if (obj_data->t > 0)
		return (true); // intersection found
	return (false); // no intersection
}


// not close but semi reliable source
// bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
// {
// 	t_vec3	ray_og = ray->place;
// 	t_vec3	ray_dir = ray->vector;
// 	t_vec3	oc = minus(ray_og, cylinder->center); // vector
// 	double	radius = cylinder->diameter / 2;
// 	double	height_half = cylinder->height / 2;

// 	// calculation of coefficients for quadratic equation

// 	obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
// 	obj_data->b = 2.0 * dot_product(oc, ray_dir) - dot_product(oc, cylinder->vector) * dot_product(ray_dir, cylinder->vector);
// 	obj_data->c = dot_product(oc, oc) - pow(dot_product(oc, cylinder->vector), 2) - pow(radius, radius); // radius, radius OR radius, 2
	
// 	// discriminant, solve the quadratic
// 	obj_data->d = obj_data->b * obj_data->b - 4 * (obj_data->a * obj_data->c);

// 	// check for intersection
// 	if (obj_data->d < 0)
// 		return (false); // no intersection

// 		// calcuate roots of quadratic equation
// 	obj_data->d = sqrt(obj_data->d);
// 	obj_data->root1 = (-obj_data->b - obj_data->d) / (2 * obj_data->a);
// 	obj_data->root2 = (-obj_data->b + obj_data->d) / (2 * obj_data->a);

// 	double t1 = ray_og.y + obj_data->root1 * ray_dir.y;
// 	double t2 = ray_og.y + obj_data->root2 * ray_dir.y;
	
// 	if (t1 < (cylinder->vector.y - height_half) || t1 > (cylinder->vector.y + height_half))
// 		obj_data->root1 = INFINITY;
// 	if (t2 < (cylinder->vector.y - height_half) || t2 > (cylinder->vector.y + height_half))
// 		obj_data->root2 = INFINITY;
	
// 	obj_data->t = fmin(obj_data->root1, obj_data->root2);
// 	if (obj_data->t > 0)
// 		return (true);
// 	return (false);

// }


// close but not right
// bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
// {
// 	t_vec3	ray_og = ray->place;
// 	t_vec3	ray_dir = ray->vector;
// 	t_vec3	oc = minus(ray_og, cylinder->vector);
	
// 	// cylinder params
// 	double	radius = cylinder->diameter / 2;
// 	double	height_half = cylinder->height / 2;
// 	double	axis = dot_product(ray_dir, cylinder->vector);
// 	(void) radius;


// 	// calculation of coefficients for quadratic equation
// 	obj_data->a = axis - (pow(dot_product(ray_dir, cylinder->center), 2));
// 	obj_data->b = 2.0 * dot_product(oc, ray_dir) - axis * axis - radius * radius;
// 	obj_data->c = dot_product(oc, oc) - axis * dot_product(oc, cylinder->center);
// 	obj_data->d = obj_data->b * obj_data->b - 4 * (obj_data->a * obj_data->c);

// 	// check for intersection
// 	if (obj_data->d < 0)
// 		return (false); // no intersection
// 	else
// 	{
// 		// calcuate roots of quadratic equation
// 		obj_data->d = sqrt(obj_data->d); // is something magic that makes it kind of cylinder like
// 		obj_data->root1 = (-obj_data->b - obj_data->d) / obj_data->a;
// 		obj_data->root2 = (-obj_data->b + obj_data->d) / obj_data->a;
// 		if (obj_data->root1 > obj_data->root2)
// 			obj_data->t = obj_data->root1;
// 		else
// 			obj_data->t = obj_data->root2;
// 	}

// 	//check if intersection point is within the cpaped ends of the cylinder
// 	double	y_inter = ray_og.y + obj_data->t * ray_dir.y;
// 	if ((y_inter >= (cylinder->center.y - height_half)) && (y_inter <= cylinder->center.y + height_half))
// 		return (true); // intersection yay!
// 	return (false); // no intersection
// }
