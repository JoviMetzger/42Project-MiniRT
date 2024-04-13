/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/13 17:07:51 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// enum e_bool intersect_cylinder(t_primitive cp, t_ray r, double *current_z)
// {
//     t_vec3  pdp = vec3_substract(cp.direction, cp.position);
//     t_vec3  eyexpdp = vec3_cross(vec3_substract(r.origin, cp.position), pdp);
//     t_vec3  rdxpdp = vec3_cross(r.direction, pdp);
//     float   a = vec3_dot(rdxpdp, rdxpdp);
//     float   b = 2 * vec3_dot(rdxpdp, eyexpdp);
//     float   c = vec3_dot(eyexpdp, eyexpdp) - (cp.radius * cp.radius * vec3_dot(pdp, pdp));
//     double  t[2];
//     double delta;
//     delta = sqrt((b * b) - (4.0 * a * c));
//     if (delta < 0)
//         return (false);
//     t[0] = (-b - (delta)) / (2.0 * a);
//     t[1] = (-b + (delta)) / (2.0 * a);
//     return (test_intersect(t, current_z));
/**
 * @todo fix, lopsided, why no pretty ? :(, i think I'm missing something when it goes to the colour etc... eventually norm... 
	// cylinder->center = position
	// cylinder->vector = direction
	// ray place = origin
	// ray vector = direction
 */
static bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
{

	
	t_vec3	ray_og = ray->place;
	t_vec3	ray_dir = ray->vector;
	// t_vec3	cyl_pos = cylinder->center;
	// t_vec3	cyl_dir = cylinder->vector;

	double	radius = cylinder->diameter / 2;
	double	height_half = cylinder->height / 2;

	t_vec3	oc = minus(ray_og, cylinder->center);
	// t_vec3	oc = minus(cyl_dir, cyl_pos);



	// calculation of coefficients for quadratic equation
// ------------- og almost working ------------/
	obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
	obj_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector);
	obj_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);
// ------------- og almost working ------------/


//    Vector3 AB = (b - a);
//     Vector3 AO = (ray.getOrigin() - a);
//     Vector3 AOxAB = (AO.cross(AB));
//     Vector3 VxAB = (ray.getDir().cross(AB));
//     double ab2 = (AB.dot(AB));
//     double A = (VxAB.dot(VxAB));
//     double B = 2 * (VxAB.dot(AOxAB));
//     double C = (AOxAB.dot(AOxAB)) - (r*r * ab2);
// ------------- test 2 ------------/

// ------------- test 2 ------------/


// ------------- test ------------/
	// t_vec3	eye = cross_product(minus(ray_og, cyl_pos), oc);
	// t_vec3	thing = cross_product(ray_dir, oc);
	// obj_data->a = dot_product(thing, thing);
	// obj_data->b = 2.0 * dot_product(thing, eye);
	// obj_data->c = dot_product(eye, eye) - (radius * radius * dot_product(oc, oc));
// ------------- test ------------/

// ------------- test 1 ------------/
	// obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
	// obj_data->b = 2.0 * dot_product(ray_dir, oc) - dot_product(ray_dir, cylinder->vector) * dot_product(oc, cylinder->vector);
	// obj_data->c = dot_product(oc, oc) - pow(dot_product(oc, cylinder->vector), 2) - radius * radius;
// ------------- test 1 ------------/
	

	// discriminant, solve the quadratic equation
	obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;


	// check for intersection
	if (obj_data->d < 0)
		return (false); // no intersection

	// calcuate roots of quadratic equation
	obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2.0 * obj_data->a);
	obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2.0 * obj_data->a);


	//check if intersection point is within the cpaped ends of the cylinder
	//cylinder formulia = ray_ogirin (Y) + t * ray_direction (Y) 
	double t1 = ray_og.y + obj_data->root1 * ray_dir.y;
	double t2 = ray_og.y + obj_data->root2 * ray_dir.y;
	
	// set roots.. if not within caps, set to infinity (oder?)
	if (t1 < (cylinder->vector.y - height_half) || t1 > (cylinder->vector.y + height_half))
		obj_data->root1 = INFINITY;
	if (t2 < (cylinder->vector.y - height_half) || t2 > (cylinder->vector.y + height_half))
		obj_data->root2 = INFINITY;

	obj_data->t = fmin(obj_data->root1, obj_data->root2); // returns the smaller double
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
