/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 22:38:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// obj_data->d = discriminant; -> discriminant = b*b - 4*a*c;
bool intersect_sphere(t_ray *ray, t_sphere *sphere, t_obj_data *obj_data, double *t)
{
    double radius;
	t_vec3	oc;

	radius = sphere->diameter / 2;
	oc = minus(ray->place, sphere->center);
	obj_data->a = dot_product(ray->vector, ray->vector);
	obj_data->b = 2.0 * dot_product(oc, ray->vector);
	obj_data->c = dot_product(oc, oc) - radius * radius;
	obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;

	if (obj_data->d  < 0)
		return (false);	// No intersection
    else 
	{
        double root1 = (-obj_data->b - sqrt(obj_data->d)) / (2.0 * obj_data->a);
        double root2 = (-obj_data->b + sqrt(obj_data->d)) / (2.0 * obj_data->a);
        *t = (root1 < root2) ? root1 : root2;
		return (true); // Intersection found
    }

}