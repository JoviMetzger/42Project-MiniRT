

*****************************************************************************
								THE VINCENT NOTES		


static	bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj_data)
{
	t_vec3	c = // cyl->center - height // start cap cylinder
	t_vec3	v = cyl->vector;
	double	radius = cyl->diameter / 2;
	t_vec3	maxm  = 	// cyl->center + height // following vector from center point to end heigt		// cylinder's end ap point
}
m = distance from base (C);
t = distance to hit location;
D = ray->direction;
V = cylinder->orientation;
X = vector (line) from camera to center of cylinder;


m = dot(ray->direction * scalar + (cyl->center - camera->origin), cyl->orientation);


a = 1 - pow(dot(ray->dir, cyl->orientation), 2);
b = 2 * (dot(ray->dir, X) - dot(ray->dir, cyl->orientation) * dot(X, cyl->orientation);
c = dot(X, X) - pow(dot(X, cyl->orientation), 2) - pow(cyl->radius, 2);





*****************************************************************************
						LATEST BEFORE VINCENT
		- not good but i was on to something... now the new version needs space...
	
/**
	// cylinder->center = position
	// cylinder->vector = direction
	// ray place = origin
	// ray vector = direction
//  */
// static bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
// {
// 	t_vec3	ray_og = ray->place;
// 	t_vec3	ray_dir = ray->vector;
// 	double	radius = cylinder->diameter / 2;
// 	double	height_half = cylinder->height / 2;
// 	t_vec3	oc = minus(ray_og, cylinder->center);


// 	// calculation of coefficients for quadratic equation
// // ------------- og almost working ------------/
// 	// obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
// 	// obj_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector);
// 	// obj_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);
// // ------------- og almost working ------------/
	
	
// 	obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
// 	obj_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(ray_dir, cylinder->vector);
// 	obj_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);

// 	// discriminant, solve the quadratic equation
// 	obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;


// 	// check for intersection
// 	if (obj_data->d < 0)
// 		return (false); // no intersection

// 	// calcuate roots of quadratic equation
// 	obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2.0 * obj_data->a);
// 	obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2.0 * obj_data->a);


// 	//check if intersection point is within the cpaped ends of the cylinder
// 	//cylinder formulia = ray_ogirin (Y) + t * ray_direction (Y) 
// 	double t1 = ray_og.y + obj_data->root1 * ray_dir.y;
// 	double t2 = ray_og.y + obj_data->root2 * ray_dir.y;
	
// 	// set roots.. if not within caps, set to infinity (oder?)
// 	if (t1 < (cylinder->vector.y - height_half) || t1 > (cylinder->vector.y + height_half))
// 		obj_data->root1 = INFINITY;
// 	if (t2 < (cylinder->vector.y - height_half) || t2 > (cylinder->vector.y + height_half))
// 		obj_data->root2 = INFINITY;

// 	obj_data->t = fmin(obj_data->root1, obj_data->root2); // returns the smaller double
// 	if (obj_data->t > 0)
// 		return (true); // intersection found
// 	return (false); // no intersection
// }

// bool	calc_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
// {
// 	if (intersect_cylinder(ray, cylinder, obj_data))
// 	{
// 		if (obj_data->t < obj_data->closest_t)
// 		{
// 			obj_data->closest_t = obj_data->t;
// 			return (true);
// 		}
// 	}
// 	return (false);
// }



*****************************************************************************
						BEFORE VINCENT NOTES

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
	
// ------------- test 2 ------------/
// obj_data->a = dot_product(ray_dir, ray_dir); //- pow(dot_product(ray_dir, cylinder->vector), 2);
// obj_data->b = 2.0 * (dot_product(oc, cylinder->vector) - (dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector)));
// // obj_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);
// obj_data->c = dot_product(oc, oc) - pow(dot_product(oc, cylinder->vector), 2) - (radius * radius);
// ------------- test 2 ------------/



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


************************************************************************************


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


*******************************************************************************

// bool	intersect_infi_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
// {
// 	t_vec3	oc;
// 	double	radius = cylinder->diameter / 2;
// 	double	rad;
// 	double	c_oc;
// 	double	height_half = cylinder->height / 2;

// 	oc = minus(ray->place, cylinder->vector);
// 	rad = dot_product(ray->vector, cylinder->vector);
// 	c_oc = dot_product(ray->vector, cylinder->vector);

// 	obj_data->a = rad - (pow(dot_product(ray->vector, cylinder->center), 2));
// 	obj_data->b = 2 * dot_product(oc, ray->vector) - c_oc * c_oc - radius * radius;
// 	obj_data->c = dot_product(oc, oc) - c_oc * dot_product(oc, cylinder->center);
// 	obj_data->d = obj_data->b * obj_data->b - obj_data->a * obj_data->c;

// 	if (obj_data->d < 0)
// 		return (false); // no intersect
// 	else
// 	{
// 		obj_data->d = sqrt(obj_data->d);
// 		obj_data->root1 = (-obj_data->b - obj_data->d) / obj_data->a;
// 		obj_data->root2 = (-obj_data->b + obj_data->d) / obj_data->a;
// 		if (obj_data->root1 > obj_data->root2)
// 			obj_data->t = obj_data->root1;
// 		else
// 			obj_data->t = obj_data->root2;
// 	}

// 	// check if intersection point is within the capped ends of the cylinder
// 	double	y_inter = ray->place.y + obj_data->t * ray->vector.y;

// 	if (y_inter >= cylinder->center.y - height_half && y_inter <= cylinder->center.y + height_half)
// 	{
// 		return (true); // intersect found
// 	}	
// 	else
// 		return (false); // intersect found
// }

bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
{
	t_vec3	ray_og = ray->place;
	t_vec3	ray_dir = ray->vector;
	t_vec3	oc = minus(ray_og, cylinder->vector);
	
	// cylinder params
	// double	radius = cylinder->diameter / 2;
	// double	height_half = cylinder->height / 2; // need? look at bottom of function
	double	axis = dot_product(ray_dir, cylinder->vector); // looks a lot more like a cylinder than the one below
	// double	axis = dot_product(ray_dir, cylinder->center);
	// double	axis = dot_product(ray->vector, ray->vector);

// 	obj_data->b = 2.0 * dot_product(oc, ray->vector) - (dot_product(ray->vector, cylinder->center) * dot_product(oc, cylinder->center));

	// calculation of coefficients for quadratic equation
	obj_data->a = axis - (pow(dot_product(ray_dir, cylinder->center), 2));
	// obj_data->b = 2.0 * dot_product(oc, ray_dir) - axis * axis - radius * radius;
	obj_data->b = 2.0 * dot_product(oc, ray_dir) - axis * dot_product(oc, cylinder->center);
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

	// without - height || without - height and + height || without - height_half || without - height_half and + height-half ... you get the point
	// if (y_inter >= (cylinder->center.y - cylinder->height) && (y_inter <= cylinder->center.y + cylinder->height))
	if ((y_inter >= (cylinder->center.y - cylinder->height)) && (y_inter <= cylinder->center.y + cylinder->height))
		return (true); // intersection yay!
	return (false); // no intersection
}