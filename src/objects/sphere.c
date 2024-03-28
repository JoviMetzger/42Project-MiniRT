/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/28 16:12:33 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/* quadratic equation:
 *  a = d * d (dot product of ray direction with itself)
 *  b = 2 * oc * d (dot product of vector from ray origin to sphere center with ray direction, doubled)
 *  c = oc * oc -r^2 (dot product of vector from ray origin to sphere center with itself, minus radius squared)
 *  d = b^2 - 4ac (discriminant)
 * 
 *  If the discriminant b^2 - 4ac is negative, 
 *  there are no real solutions to the quadratic equation,
 *  meaning the ray does not intersect the sphere.
 * 
 *  If the discriminant is non-negative, there are potentially two real solutions, 
 *  representing the points where the ray intersects the sphere. 
 *  These solutions are given by the roots of the quadratic equation. 
 *  The smaller root is chosen as the parameter 't' for the intersection point 
 *  closer to the ray's origin.
 */
bool intersect_sphere(t_ray *ray, t_objs *sphere, t_obj_data *obj_data)
{
    double radius;
    t_vec3	oc;

    // printf("----- SPHERE OBJ: -----\ncenter: %f - %f - %f\nvector: %f - %f - %f\n,diameter: %f\nheight: %f", sphere->center.x, sphere->center.y, sphere->center.z, sphere->vector.x, sphere->vector.y, sphere->vector.z, sphere->diameter, sphere->height);
    radius = sphere->diameter / 2;
    oc = minus(ray->place, sphere->center);
    obj_data->a = dot_product(ray->vector, ray->vector);
    obj_data->b = 2.0 * dot_product(oc, ray->vector);
    obj_data->c = dot_product(oc, oc) - radius * radius;
    obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;

    if (obj_data->d < 0)
        return (false);	// No intersection
    else 
    {
        obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2.0 * obj_data->a);
        obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2.0 * obj_data->a);
        if (obj_data->root1 < obj_data->root2)
            obj_data->t = obj_data->root1;
        else
            obj_data->t = obj_data->root2;
        return (true); // Intersection found
    }
}
