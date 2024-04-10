/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/10 19:50:21 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
{
	t_vec3	ray_og = ray->place;
	t_vec3	ray_dir = ray->vector;
	t_vec3	oc = minus(ray_og, cylinder->vector);
	
	// cylinder params
	double	radius = cylinder->diameter / 2;
	double	height_half = cylinder->height / 2;
	double	axis = dot_product(ray_dir, cylinder->vector);
	(void) radius;


	// calculation of coefficients for quadratic equation
	obj_data->a = axis - (pow(dot_product(ray_dir, cylinder->center), 2));
	obj_data->b = 2.0 * dot_product(oc, ray_dir) - axis * axis - radius * radius;
	obj_data->c = dot_product(oc, oc) - axis * dot_product(oc, cylinder->center);
	obj_data->d = obj_data->b * obj_data->b - 4 * (obj_data->a * obj_data->c);

	// check for intersection
	if (obj_data->d < 0)
		return (false); // no intersection
	else
	{
		// calcuate roots of quadratic equation
		obj_data->d = sqrt(obj_data->d); // is something magic that makes it kind of cylinder like
		obj_data->root1 = (-obj_data->b - obj_data->d) / obj_data->a;
		obj_data->root2 = (-obj_data->b + obj_data->d) / obj_data->a;
		if (obj_data->root1 > obj_data->root2)
			obj_data->t = obj_data->root1;
		else
			obj_data->t = obj_data->root2;
	}

	//check if intersection point is within the cpaped ends of the cylinder
	double	y_inter = ray_og.y + obj_data->t * ray_dir.y;
	if ((y_inter >= (cylinder->center.y - height_half)) && (y_inter <= cylinder->center.y + height_half))
		return (true); // intersection yay!
	return (false); // no intersection
}
