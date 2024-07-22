/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/22 13:26:36 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Cut of the ends, else there will be a infinite cylinder
static bool	cut_ends_hit_bod(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	double	distance_along_axis;
	hit->hit_pos = plus(ray->place, mult_vecdub(ray->vector, hit->t));
	distance_along_axis = dot_product(minus(hit->hit_pos, cyl->center), cyl->vector);	
	// if (distance_along_axis >= 0 && distance_along_axis <= cyl->height)
	if (distance_along_axis >= -cyl->height / 2.0 && distance_along_axis <= cyl->height / 2.0)
		return (true);
	else
		return (false);
}

// calculating the body
bool	bodyody(t_hit_data *hit, t_objs *cyl, t_ray *ray)
{
	t_vec3	dir_proj;
	t_vec3	oc_proj;

	hit->o_c = minus(ray->place, cyl->center);
	dir_proj = minus(ray->vector, mult_vecdub(cyl->vector, dot_product(ray->vector, cyl->vector)));
	oc_proj = minus(hit->o_c, mult_vecdub(cyl->vector, dot_product(hit->o_c, cyl->vector)));
	hit->a = dot_product(dir_proj, dir_proj);
	hit->b = 2.0 * dot_product(dir_proj, oc_proj);
	hit->c = dot_product(oc_proj, oc_proj) - (cyl->radius * cyl->radius);
	hit->d = hit->b * hit->b - 4 * (hit->a * hit->c);
	if (hit->d < 0.0)
		return (false);
	hit->root1 = (-hit->b - sqrt(hit->d)) / (2 * hit->a);
	hit->root2 = (-hit->b + sqrt(hit->d)) / (2 * hit->a);
	if (hit->root1 > 0 && hit->root2 > 0)
		hit->t = fmin(hit->root1, hit->root2);
	else if (hit->root1 > 0)
		hit->t = hit->root1;
	else if (hit->root2 > 0)
		hit->t = hit->root2;
	else
		return (false);
	return (cut_ends_hit_bod(hit, cyl, ray));
}

// surface normal of the cylinder
void	cyl_normal(t_ray *ray, t_objs *cyl, t_hit_data *hit)
{
	double	distance_along_axis;
	t_vec3	point_on_axis;

	hit->hit_pos = plus(ray->place, mult_vecdub(ray->vector, hit->t));
	hit->to_center = minus(hit->hit_pos, cyl->center);
	distance_along_axis = dot_product(hit->to_center, cyl->vector);
	point_on_axis = plus(cyl->center, mult_vecdub(cyl->vector, distance_along_axis));
	cyl->normal = normalize(minus(hit->hit_pos, point_on_axis));
	// cyl->normal = normalize(mult_vecdub(minus(hit->hit_pos, point_on_axis), -1));
	// printf("NORMAL : %lf %lf %lf\n", cyl->normal.x, cyl->normal.y, cyl->normal.z);
}


bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *hit)
{	
	hit->tmp_t = DBL_MAX;
	if (intersect_caps(ray, cyl, hit) == true)
	{
		if (hit->t < hit->tmp_t)
			hit->tmp_t = hit->t;
	}
	if (bodyody(hit, cyl, ray) == true)
	{
		if (hit->t < hit->tmp_t)
		{
			hit->tmp_t = hit->t;
			cyl_normal(ray, cyl, hit);
		}
	}
	if (hit->tmp_t != DBL_MAX)
	{
		cyl->obj_t = hit->tmp_t;
		hit->t = hit->tmp_t;
		cyl->hit_pos = plus(ray->place, mult_vecdub(ray->vector, cyl->obj_t));
		return (true);
	}
	return (false);
}

bool	cylinder(t_ray *ray, t_objs *cyl, t_hit_data *hit)
{	
	if (intersect_cylinder(ray, cyl, hit))
		return (check_closest(hit));
	return (false);
}

//=========================================================

// t_inter_point ft_cylinder_collision(t_ray ray, t_pack cylinder, int id)
// {
//     t_inter_point inter_point;
//     t_delta delta;
//     t_ray new_ray;
//     t_vect c_to_o;

//     inter_point.hit = FALSE;
//     inter_point.id = id;
    
//     // Initialize new_ray with ray's origin and direction
//     new_ray.origin = ray.origin;
//     cylinder.rot = normalize(cylinder.rot); // Normalize cylinder's rotation vector
    
//     // Calculate new_ray direction perpendicular to cylinder's axis
//     new_ray.direction = cross(ray.direction, cylinder.rot);
    
//     // Vector from cylinder position to ray origin
//     c_to_o = sub(ray.origin, cylinder.pos);
    
//     // Quadratic coefficients for cylinder intersection
//     delta.a = dot(new_ray.direction, new_ray.direction);
//     delta.b = 2 * dot(new_ray.direction, cross(c_to_o, cylinder.rot));
//     delta.c = dot(cross(c_to_o, cylinder.rot), cross(c_to_o, cylinder.rot)) - pow(cylinder.diameter / 2, 2);
    
//     // Calculate discriminant
//     delta.delta = pow(delta.b, 2) - 4 * delta.c * delta.a;
    
//     // No intersection if discriminant is negative
//     if (delta.delta < 0)
//         return (inter_point);
    
//     // Calculate potential intersection points
//     inter_point.t1 = (-delta.b - sqrt(delta.delta)) / (2 * delta.a);
//     inter_point.t2 = (-delta.b + sqrt(delta.delta)) / (2 * delta.a);
    
//     // Choose closest intersection point in front of the ray origin
//     if (inter_point.t2 < 0)
//         return (inter_point);
//     inter_point.t = (inter_point.t1 > 0 ? inter_point.t1 : inter_point.t2);
    
//     // Check and handle intersection with cylinder edges (caps)
//     return (ft_find_edges(cylinder, ray, inter_point));
// }

// t_inter_point ft_find_edges(t_pack cylinder, t_ray ray, t_inter_point inter_point)
// {
//     double a;

//     // Compute normal vector at intersection point
//     ft_get_normal(ray, cylinder.pos, &inter_point);
    
//     // Check if intersection point is outside cylinder's height
//     if (get_norm(sub(inter_point.coord, cylinder.pos)) > cylinder.height)
//         return (inter_point);
    
//     // Project intersection point onto cylinder's surface to find normal
//     a = dot(cylinder.rot, sub(inter_point.coord, cylinder.pos));
//     inter_point.normal = normalize(sub(inter_point.coord, add(cylinder.pos, ft_scale(cylinder.rot, a))));
    
//     // Mark intersection as valid
//     inter_point.hit = TRUE;
    
//     return (inter_point);
// }