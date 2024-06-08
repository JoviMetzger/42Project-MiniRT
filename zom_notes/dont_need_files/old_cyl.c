/**

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
	
	// cylinder->center = position
	// cylinder->vector = direction
	// ray place = origin
	// ray vector = direction
//  */
<<<<<<< HEAD
static bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_hit_data *obj_hit)
=======
static bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_hit_data *hit_data)
>>>>>>> parser
{
			// OLD ABCs
			// none of this is helpfullll
	// t_vec3	ray_og = ray->place;
	// t_vec3	ray_dir = ray->vector;
	// double	radius = cylinder->diameter / 2;
	// double	height_half = cylinder->height / 2;
	// t_vec3	oc = minus(ray_og, cylinder->center);

<<<<<<< HEAD
	// obj_hit->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
	// obj_hit->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(ray_dir, cylinder->vector);
	// obj_hit->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);
=======
	// hit_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
	// hit_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(ray_dir, cylinder->vector);
	// hit_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);
>>>>>>> parser



		///// quad
	// calcuate roots of quadratic equation
<<<<<<< HEAD
	obj_hit->root1 = (-obj_hit->b - sqrt(obj_hit->d)) / (2.0 * obj_hit->a);
	obj_hit->root2 = (-obj_hit->b + sqrt(obj_hit->d)) / (2.0 * obj_hit->a);
=======
	hit_data->root1 = (-hit_data->b - sqrt(hit_data->d)) / (2.0 * hit_data->a);
	hit_data->root2 = (-hit_data->b + sqrt(hit_data->d)) / (2.0 * hit_data->a);
>>>>>>> parser


			// NEED??
 //    add rest of this shizzle before quad ??

	//check if intersection point is within the cpaped ends of the cylinder
	//cylinder formulia = ray_ogirin (Y) + t * ray_direction (Y) 
<<<<<<< HEAD
	double t1 = ray_og.y + obj_hit->root1 * ray_dir.y;
	double t2 = ray_og.y + obj_hit->root2 * ray_dir.y;
	
	// set roots.. if not within caps, set to infinity (oder?)
	if (t1 < (cylinder->vector.y - height_half) || t1 > (cylinder->vector.y + height_half))
		obj_hit->root1 = INFINITY;
	if (t2 < (cylinder->vector.y - height_half) || t2 > (cylinder->vector.y + height_half))
		obj_hit->root2 = INFINITY;

	// 	obj_hit->t = fmin(obj_hit->root1, obj_hit->root2); // returns the smaller double
// 	if (obj_hit->t > 0)
=======
	double t1 = ray_og.y + hit_data->root1 * ray_dir.y;
	double t2 = ray_og.y + hit_data->root2 * ray_dir.y;
	
	// set roots.. if not within caps, set to infinity (oder?)
	if (t1 < (cylinder->vector.y - height_half) || t1 > (cylinder->vector.y + height_half))
		hit_data->root1 = INFINITY;
	if (t2 < (cylinder->vector.y - height_half) || t2 > (cylinder->vector.y + height_half))
		hit_data->root2 = INFINITY;

	// 	hit_data->t = fmin(hit_data->root1, hit_data->root2); // returns the smaller double
// 	if (hit_data->t > 0)
>>>>>>> parser
// 		return (true); // intersection found
// 	return (false); // no intersection

}



// ----------------------------og old not really working but not worst ----------//
/**
	// cylinder->center = position
	// cylinder->vector = direction
	// ray place = origin
	// ray vector = direction
//  */
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


// 	// calculation of coefficients for quadratic equation
// // ------------- og almost working ------------/
<<<<<<< HEAD
// 	// obj_hit->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
// 	// obj_hit->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector);
// 	// obj_hit->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);
// // ------------- og almost working ------------/
	
	
// 	obj_hit->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
// 	obj_hit->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(ray_dir, cylinder->vector);
// 	obj_hit->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);

// 	// discriminant, solve the quadratic equation
// 	obj_hit->d = obj_hit->b * obj_hit->b - 4 * obj_hit->a * obj_hit->c;


// 	// check for intersection
// 	if (obj_hit->d < 0)
// 		return (false); // no intersection

// 	// calcuate roots of quadratic equation
// 	obj_hit->root1 = (-obj_hit->b - sqrt(obj_hit->d)) / (2.0 * obj_hit->a);
// 	obj_hit->root2 = (-obj_hit->b + sqrt(obj_hit->d)) / (2.0 * obj_hit->a);
=======
// 	// hit_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
// 	// hit_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector);
// 	// hit_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);
// // ------------- og almost working ------------/
	
	
// 	hit_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
// 	hit_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(ray_dir, cylinder->vector);
// 	hit_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);

// 	// discriminant, solve the quadratic equation
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

<<<<<<< HEAD
// bool	calc_cylinder(t_ray *ray, t_objs *cylinder, t_hit_data *obj_hit)
// {
// 	if (intersect_cylinder(ray, cylinder, obj_hit))
// 	{
// 		if (obj_hit->t < obj_hit->closest_t)
// 		{
// 			obj_hit->closest_t = obj_hit->t;
=======
// bool	calc_cylinder(t_ray *ray, t_objs *cylinder, t_hit_data *hit_data)
// {
// 	if (intersect_cylinder(ray, cylinder, hit_data))
// 	{
// 		if (hit_data->t < hit_data->closest_t)
// 		{
// 			hit_data->closest_t = hit_data->t;
>>>>>>> parser
// 			return (true);
// 		}
// 	}
// 	return (false);
// }
