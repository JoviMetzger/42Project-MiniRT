/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/11 17:31:26 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * @todo fix, lopsided, why no pretty ? :(, i think I'm missing something when it goes to the colour etc... eventually norm... 
 */
static bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
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
	

	// discriminant, solve the quadratic equation
	obj_data->d = obj_data->b * obj_data->b - 4 * (obj_data->a * obj_data->c);


	// check for intersection
	if (obj_data->d < 0)
		return (false); // no intersection
	// else
	// {
		// calcuate roots of quadratic equation
	obj_data->d = sqrt(obj_data->d);
	obj_data->root1 = (-obj_data->b - obj_data->d) / obj_data->a;
	obj_data->root2 = (-obj_data->b + obj_data->d) / obj_data->a;
	// }

	//check if intersection point is within the cpaped ends of the cylinder
	//cylinder formulia = ray_ogirin (Y) + t * ray_direction (Y) 
	double t1 = ray_og.y + obj_data->root1 * ray_dir.y;
	double t2 = ray_og.y + obj_data->root2 * ray_dir.y;
	
	// set roots.. if not within caps, set to infinity (oder?)
	if (t1 < (cylinder->vector.y - height_half) || t1 > (cylinder->vector.y + height_half))
		obj_data->root1 = INFINITY;
	if (t2 < (cylinder->vector.y - height_half) || t2 > (cylinder->vector.y + height_half))
		obj_data->root2 = INFINITY;

	obj_data->t = fmin(obj_data->root1, obj_data->root2);
	if (obj_data->t > 0)
		return (true); // intersection found
	return (false); // no intersection
}

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
