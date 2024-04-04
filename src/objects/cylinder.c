/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/04 15:23:35 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/*
	Cylinder
	• The cylinder : intersection between an infinite height cylinder and the
	subspace delimited by two planes which equations are
	z = 0 and z= h
	• The intersection between the ray an the infinite height cylinder is first
	performed. This yields a first interval [t1,t2]
	• The intersection with the two planes gives a second interval [ t3, t4 ].
	• The final intersection interval [ I, M ] results from the combination of these
	two intervals ( as for the parallelepiped).

	• obtaining [ t1, t2 ]
	– The equation of the infinite height cylinder :
	– x2 + y2 = r2
	– Substituting the ray equation in this equation we obtain:
	tsq . ( dxsq + dysq ) + 2t . (x0 . dx + y0 . dy ) + ( x0sq + y0sq - r2 ) = 0
	
	– Solving this equation gives the interval [ t1, t2 ].
	• obtaining [ t3, t4 ]
	– Let A and B the two values of t resulting from the intersection
	with the two planes :
	A = - z0 / dz and B = ( h - z0 ) / dz
	• We get :
	t3 = min( A,B ) and t4 = max( A, B )
	
*/

// height, rotation... cylinder vector... 
/**
 * 	GENERAL NOTE
	P = P0 + t . D
	• where :
	P0 is the ray origin;
	D = (dx, dy, dz) is the direction vector of the ray ;
	t > 0 
 */

bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
{
	t_vec3	oc;
	double	radius;

	radius = cylinder->diameter / 2;
	
	// cylinder->center.z = (cylinder->center.z * cylinder->center.z);
	// cylinder->center.z = (cylinder->center.x * cylinder->center.x) + (cylinder->center.y * cylinder->center.y); 

	// obj_data->t = obj_data->t * obj_data->t;

	oc = minus(ray->place, cylinder->center);

	obj_data->a = (dot_product(ray->vector, ray->vector)) - (pow(dot_product(ray->vector, cylinder->center), 2));
	obj_data->b = 2.0 * dot_product(oc, ray->vector) - (dot_product(ray->vector, cylinder->center) * dot_product(oc, cylinder->center));
	obj_data->c = dot_product(oc, oc) - pow(dot_product(oc, cylinder->center), 2) - pow(radius, 2);

	// dont know if this is necessary
	// if (obj_data->a == 0 && obj_data->b != 0)
	// {
	// 	obj_data->root1 = -obj_data->c / obj_data->b;
	// 	return (true);
	// }
	
	obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;
	if (obj_data->d < 0)
	{	
		return (false); // no intersection
	}
	else
	{
		obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2 * obj_data->a);
		obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2 * obj_data->a);
		if (obj_data->root1 > obj_data->root2)
			obj_data->t = obj_data->root1;
		else
			obj_data->t = obj_data->root2;
		return (true); // Intersection found
	}
}

