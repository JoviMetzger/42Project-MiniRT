/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maybe_triangle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/13 17:57:51 by smclacke      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2024/05/30 17:12:59 by jmetzger      ########   odam.nl         */
=======
/*   Updated: 2024/05/21 17:54:01 by smclacke      ########   odam.nl         */
>>>>>>> parser
/*                                                                            */
/* ************************************************************************** */

// can of triangle heheh
<<<<<<< HEAD
// static bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_hit_data *obj_hit)
=======
// static bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_hit_data *hit_data)
>>>>>>> parser
// {
// 	t_vec3	ray_og = ray->place;
// 	t_vec3	ray_dir = ray->vector;
// 	double	radius = cylinder->diameter / 2;
// 	double	height_half = cylinder->height / 2;

// 	t_vec3	oc = minus(ray_og, cylinder->center);
// 	// t_vec3	oc = minus(cyl_dir, cyl_pos);



	// calculation of coefficients for quadratic equation
// ------------- og almost working ------------/
<<<<<<< HEAD
	// obj_hit->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
	// obj_hit->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector);
	// obj_hit->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);
=======
	// hit_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
	// hit_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector);
	// hit_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);
>>>>>>> parser
// ------------- og almost working ------------/

/**
 *bool	cylinder_intersect(t_cylinder *cy, t_ray *ray, t_hit *inter)
{
	double		t;
	t_vec3		co;
	t_equation	equation;

	equation.t1 = -1;
	equation.t2 = -1;
	co = vec3_sub(ray->origin, cy->cap1);
	equation.a = vec3_dot(ray->direction, ray->direction) - \
		pow(vec3_dot(ray->direction, cy->normal), 2);
	equation.b = 2 * (vec3_dot(ray->direction, co) - \
		(vec3_dot(ray->direction, cy->normal) * vec3_dot(co, cy->normal)));
	equation.c = vec3_dot(co, co) - pow(vec3_dot(co, cy->normal), 2) - \
		pow(cy->radius, 2);
	solve(&equation);
	if (equation.t1 <= 0 && equation.t2 <= 0)
		return (false);
	t = verify_intersections(cy, ray, &equation, inter);
	if (t > 0.0f)
	{
		inter->t = t;
		inter->color = cy->color;
		return (true);
	}
	return (false);
}
 * 
 */
	// ------------- test 2 ------------/
<<<<<<< HEAD
// 	obj_hit->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2); // cyl->normal
// 	obj_hit->b = 2.0 * (dot_product(ray_dir, oc) - (dot_product(ray_dir, cylinder->vector) * dot_product(oc, cylinder->vector)));
// 	obj_hit->c = dot_product(oc, oc) - pow(dot_product(oc, cylinder->vector), 2) - radius * radius; // pow(radius, 2);
=======
// 	hit_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2); // cyl->normal
// 	hit_data->b = 2.0 * (dot_product(ray_dir, oc) - (dot_product(ray_dir, cylinder->vector) * dot_product(oc, cylinder->vector)));
// 	hit_data->c = dot_product(oc, oc) - pow(dot_product(oc, cylinder->vector), 2) - radius * radius; // pow(radius, 2);
>>>>>>> parser
// 	// ------------- test 2 ------------/


// 	// discriminant, solve the quadratic equation
<<<<<<< HEAD
// 	obj_hit->d = obj_hit->b * obj_hit->b - 4 * obj_hit->a * obj_hit->c;


// 	// check for intersection
// 	if (obj_hit->d < 0)
// 		return (false); // no intersection

// 	// calcuate roots of quadratic equation
// 	obj_hit->root1 = (-obj_hit->b - sqrt(obj_hit->d)) / (2.0 * obj_hit->a);
// 	obj_hit->root2 = (-obj_hit->b + sqrt(obj_hit->d)) / (2.0 * obj_hit->a);
=======
// 	hit_data->d = hit_data->b * hit_data->b - 4 * hit_data->a * hit_data->c;


// 	// check for intersection
// 	if (hit_data->d < 0)
// 		return (false); // no intersection

// 	// calcuate roots of quadratic equation
// 	hit_data->root1 = (-hit_data->b - sqrt(hit_data->d)) / (2.0 * hit_data->a);
// 	hit_data->root2 = (-hit_data->b + sqrt(hit_data->d)) / (2.0 * hit_data->a);
>>>>>>> parser


// 	//check if intersection point is within the cpaped ends of the cylinder
// 	//cylinder formulia = ray_ogirin (Y) + t * ray_direction (Y) 
<<<<<<< HEAD
// 	double t1 = ray_og.y + obj_hit->root1 * ray_dir.y;
// 	double t2 = ray_og.y + obj_hit->root2 * ray_dir.y;
	
// 	// set roots.. if not within caps, set to infinity (oder?)
// 	if (t1 < (cylinder->vector.y - height_half) || t1 > (cylinder->vector.y + height_half))
// 		obj_hit->root1 = INFINITY;
// 	if (t2 < (cylinder->vector.y - height_half) || t2 > (cylinder->vector.y + height_half))
// 		obj_hit->root2 = INFINITY;

// 	obj_hit->t = fmin(obj_hit->root1, obj_hit->root2); // returns the smaller double
// 	if (obj_hit->t > 0)
=======
// 	double t1 = ray_og.y + hit_data->root1 * ray_dir.y;
// 	double t2 = ray_og.y + hit_data->root2 * ray_dir.y;
	
// 	// set roots.. if not within caps, set to infinity (oder?)
// 	if (t1 < (cylinder->vector.y - height_half) || t1 > (cylinder->vector.y + height_half))
// 		hit_data->root1 = INFINITY;
// 	if (t2 < (cylinder->vector.y - height_half) || t2 > (cylinder->vector.y + height_half))
// 		hit_data->root2 = INFINITY;

// 	hit_data->t = fmin(hit_data->root1, hit_data->root2); // returns the smaller double
// 	if (hit_data->t > 0)
>>>>>>> parser
// 		return (true); // intersection found
// 	return (false); // no intersection
// }