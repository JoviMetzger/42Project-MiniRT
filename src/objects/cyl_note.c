
//------------------------------//
//------------------------------//
//------------------------------//
//------------------------------//
ANOTHER EXAMPLE

static double	caps_intersection(t_p3 o, t_p3 d, t_figures *lst)
{
	double	id1;
	double	id2;
	t_p3	ip1;
	t_p3	ip2;
	t_p3	c2;

	c2 = vadd(lst->fig.cy.c, scal_x_vec(lst->fig.cy.h, lst->fig.cy.nv));
	id1 = solve_plane(o, d, lst->fig.cy.c, lst->fig.cy.nv);
	id2 = solve_plane(o, d, c2, lst->fig.cy.nv);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		ip1 = vadd(o, scal_x_vec(id1, d));
		ip2 = vadd(o, scal_x_vec(id2, d));
		if ((id1 < INFINITY && distance(ip1, lst->fig.cy.c) <= lst->fig.cy.r)
				&& (id2 < INFINITY && distance(ip2, c2) <= lst->fig.cy.r))
			return (id1 < id2 ? id1 : id2);
		else if (id1 < INFINITY
						&& distance(ip1, lst->fig.cy.c) <= lst->fig.cy.r)
			return (id1);
		else if (id2 < INFINITY && distance(ip2, c2) <= lst->fig.cy.r)
			return (id2);
		return (INFINITY);
	}
	return (INFINITY);
}


//------------------------------//
//------------------------------//
FIGURING OUT THE CAP PLANE BIT

	if (obj->t > 0)
	{
		if (obj->t < (cyl->vector.y - obj->height_half) || obj->t > cyl->vector.y + obj->height_half)
		{
			
			double denom = dot_product(ray->vector, cyl->vector);
			if (fabs(denom) > EPSILON)
			{
				t_vec3 oc = minus(ray->place, cyl->center);
				obj->t = -dot_product(oc, cyl->vector) / denom;
				if (obj->t >= cyl->height)
					return (true);
			}
		}
	}
//------------------------------//
//------------------------------//
//------------------------------//

// bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
// {
// 	t_vec3	c_c;
// 	t_vec3	r_c;

// 	r_c = cross_product(cyl->vector, ray->vector);
// 	c_c = minus(ray->place, cyl->center);
// 	c_c = cross_product(c_c, cyl->vector);
	
// 	obj->radius = cyl->diameter / 2;
// 	obj->height_half = cyl->height / 2;

// 	obj->a = dot_product(r_c, r_c);
// 	obj->b = -2.0 * dot_product(r_c, c_c);
// 	obj->c = dot_product(c_c, c_c) - pow(obj->radius, 2);
// 	if (quadratic(obj) == true)
// 	{
// 		if (obj->t > EPSILON)
// 		{	
// 			if (check_caps(obj, cyl, ray) == true)
// 			{
// 				obj->t = obj->tmp_t;
// 				return (check_closest(obj));
// 			}
// 			else
// 				return (false);
// 				// return (check_closest(obj));	
// 		}
// 	}
// 	return (false);
// }

//------------------------------//

static void	check_hit(double root, t_objs *cyl, t_ray *ray, t_obj_data *obj)
{
	t_vec3	a;
	t_vec3	b;

	b = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
	a = plus(ray->place, mult_vecdub(ray->vector, obj->t));

	if (dot_product(cyl->vector, minus(a, cyl->center)) <= 0)
		root = -1;
	if (dot_product(cyl->vector, minus(a, b)) >= 0)
		root = -1;
}	

static t_vec3 good_norm(t_vec3 normal, t_ray *ray)
{
	if (dot_product(normal, ray->vector) > EPSILON)
		normal = mult_vecdub(normal, -1);
	return (normal);
}

static t_vec3 cyl_norm(t_vec3 hit, t_ray *ray, t_objs *cyl)
{
	t_vec3 ctp;
	t_vec3 normal;

	ctp = minus(hit, cyl->center);
	normal = minus(ctp, mult_vecdub(cyl->vector, dot_product(cyl->vector, ctp)));
	normalize_vector(normal);
	return (good_norm(normal, ray));
}

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
{
	t_vec3	aaa;
	t_vec3	right;

	aaa = minus(ray->vector, mult_vecdub(cyl->vector, dot_product(ray->vector, cyl->vector)));
	obj->a = dot_product(aaa, aaa);
	
	right = minus(minus(ray->place, cyl->center), mult_vecdub(cyl->vector, dot_product(minus(ray->place, cyl->center), cyl->vector)));
	obj->b = 2.0 * dot_product(aaa, right);
	
	obj->c = dot_product(right, right) - (obj->radius * obj->radius);

	if (quadratic(obj) == false)
		return (false);
	if (obj->root1 > 0)
		check_hit(obj->root1, cyl, ray, obj);
	if (obj->root2 > 0)
		check_hit(obj->root2, cyl, ray, obj);
	if (obj->root1 < 0 && obj->root2 < 0)
		return (false);
	if ((obj->root2 < obj->root1 && obj->root2 > 0) || (obj->root1 < obj->root2 && obj->root1 <= 0)) 
		obj->t = obj->root2;
	else
		obj->t = obj->root1;
	t_vec3 hit = plus(ray->place, mult_vecdub(ray->vector, obj->t));
	cyl->center = cyl_norm(hit, ray, cyl);
	return (check_closest(obj));
}
//------------------------------//


	// obj->tmp_t = obj->t;
	
	// obj->hit1 = ray->place.y + obj->root1 * ray->vector.y;
	// obj->hit2 = ray->place.y + obj->root2 * ray->vector.y;
	
	// obj->hit1 = ray->place.y + obj->root1 * ray->vector.y;
	// obj->hit2 = ray->place.y + obj->root2 * ray->vector.y;

	// if (obj->hit1 < (cyl->vector.y - obj->height_half) || obj->hit1 > cyl->vector.y + obj->height_half)
	// 	obj->root1 = obj->hit1;
	// 	// obj->hit1 = obj->root1;
	// if (obj->hit2 < (cyl->vector.y - obj->height_half) || obj->hit2 > cyl->vector.y + obj->height_half)
	// 	obj->root2 = obj->hit2;
		// obj->hit2 = obj->root2;
	// obj->tmp_t = fmin(obj->hit1, obj->hit2);

// without hit variables

			// static bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
			// {
			// 	obj->tmp_t = obj->t;
			// 	// double	hit1 = 0;
			// 	// double	hit2 = 0;
			// 	double	t1 = ray->place.y + obj->root1 * ray->vector.y;
			// 	double	t2 = ray->place.y + obj->root2 * ray->vector.y;

			// 	if (t1 < (cyl->vector.y - obj->height_half) || t1 > cyl->vector.y + obj->height_half)
			// 		obj->root1 = INFINITY;
			// 		// hit1 = obj->root1;
			// 	if (t2 < (cyl->vector.y - obj->height_half) || t2 > cyl->vector.y + obj->height_half)
			// 		obj->root2 = INFINITY;
			// 		// hit2 = obj->root2;
			// 	obj->tmp_t = fmin(obj->root1, obj->root2);
			// 	// obj->tmp_t = fmin(hit1, hit2);
			// 	if (obj->tmp_t > 0)
			// 	{
			// 		double	denom = dot_product(ray->vector, cyl->vector);
			// 		if (fabs(denom) > EPSILON)
			// 		{
			// 			t_vec3	oc = minus(ray->place, cyl->center);
			// 			obj->tmp_t = -dot_product(oc, cyl->vector) / denom;
			// 			if (obj->tmp_t >= cyl->height)
			// 			{
			// 				obj->t = obj->tmp_t;
			// 				return (check_closest(obj));
			// 			}
			// 			else
			// 				return (false);
			// 		}
			// 	}
			// 	return (false);
			// }

// old plane bit

			// if (obj_data->t > 0)
			// 			{
			// 				// printf("here\n");
			// 				// exit(EXIT_SUCCESS);
			// 				// solve_capps
			// 				double	denom = dot_product(ray->vector, cyl->vector);
			// 				if (fabs(denom) > EPSILON)
			// 				{
			// 					t_vec3	oc = minus(ray->place, cyl->center);
			// 					obj_data->t = -dot_product(oc, cyl->vector) / denom;
			// 					if (obj_data->t >= EPSILON)
			// 						return (check_closest(obj_data));
			// 				}
			// 				return (false);
			// 			}

// old version before function split

			// double	t1 = ray->place.y + obj_data->root1 * ray->vector.y;
			// double	t2 = ray->place.y + obj_data->root2 * ray->vector.y;
			// if (t1 < (cyl->vector.y - height_half) || t1 > cyl->vector.y + height_half)
			// 	obj_data->t = obj_data->root1;
			// 	// obj_data->root1 = INFINITY;
			// else if (t2 < (cyl->vector.y - height_half) || t2 > cyl->vector.y + height_half)
			// 	obj_data->t = obj_data->root2;
			// 	// obj_data->root2 = INFINITY;
			// // printf("root1 = %f | root2 = %f\n", obj_data->root1, obj_data->root2);
			// // exit(EXIT_SUCCESS);
			// // obj_data->t = fmin(obj_data->root1, obj_data->root2);
			// // printf("t = %f\n", obj_data->t);
			// // exit(EXIT_SUCCESS);
			// // if (obj_data->t == INFINITY || obj_data->t == 0)
			// // 	return (true);
			// if (obj_data->t > 0)
			// {
			// 	// printf("here\n");
			// 	// exit(EXIT_SUCCESS);
			// 	// solve_capps
			// 	double	denom = dot_product(ray->vector, cyl->vector);
			// 	if (fabs(denom) > EPSILON)
			// 	{
			// 		t_vec3	oc = minus(ray->place, cyl->center);
			// 		obj_data->t = -dot_product(oc, cyl->vector) / denom;
			// 		if (obj_data->t >= EPSILON)
			// 			return (check_closest(obj_data));
			// 	}
			// 	return (false);
			// }
			// else if (obj_data->t < 0) //- no intersection
			// 	return (false);

// possible solution ish not really

		// 	if (obj_data->t > 0)
		// 	{
		// 		// check caps (top) using height, for bottom we need base point
		// 		// return (check_closest(obj_data));
		// 		double	distance;
		// 		double	denom = dot_product(ray->vector, cyl->vector);
		// 		t_vec3	oc = minus(cyl->center, ray->place);
		// 		t_vec3	hit;
		// 		if (fabs(denom) > EPSILON)
		// 		{
		// 			distance = dot_product(oc, cyl->vector); // minus and div denom
		// 			hit = plus(mult_vecdub(ray->vector, distance), ray->place);
		// 			// if vector length (hit , height (for top ? )) <= cyl->radius
		// 			if (length_squared(hit) + sqrt(cyl->height) <= radius)
		// 			{
		// 				if (distance > 0 && distance < obj_data->t)
		// 					return (check_closest(obj_data));
		// 			}
		// 		}
		// 	}
		// }

static bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->tmp_t = obj->t;
	obj->hit1 = ray->place.y + obj->root1 * ray->vector.y;
	obj->hit2 = ray->place.y + obj->root2 * ray->vector.y;

	if (obj->hit1 < (cyl->vector.y - obj->height_half) || obj->hit1 > cyl->vector.y + obj->height_half)
		obj->root1 = obj->hit1;
		// obj->hit1 = obj->root1;
	if (obj->hit2 < (cyl->vector.y - obj->height_half) || obj->hit2 > cyl->vector.y + obj->height_half)
		obj->root2 = obj->hit2;
		// obj->hit2 = obj->root2;

	// obj->tmp_t = fmin(obj->hit1, obj->hit2);
	obj->tmp_t = fmin(obj->root1, obj->root2);

	if (obj->tmp_t > 0)
	{
		double	denom = dot_product(ray->vector, cyl->vector);
		t_vec3	oc = minus(cyl->center, ray->place);
		if (fabs(denom) > EPSILON)
		{
			obj->tmp_t = dot_product(oc, cyl->vector) / denom;
			if (obj->tmp_t >= obj->height_half)
				return (true);
			else
				return (false);
		}
	}
	return (false);
}

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
{
	t_vec3	c_c;
	t_vec3	r_c;

	r_c = cross_product(cyl->vector, ray->vector);
	c_c = minus(ray->place, cyl->center);
	c_c = cross_product(c_c, cyl->vector);
	
	obj->radius = cyl->diameter / 2;
	obj->height_half = cyl->height / 2;

	obj->a = dot_product(r_c, r_c);
	obj->b = -2.0 * dot_product(r_c, c_c);
	obj->c = dot_product(c_c, c_c) - pow(obj->radius, 2);
	if (quadratic(obj) == true)
	{
		if (obj->t > EPSILON)
		{	
			if (check_caps(obj, cyl, ray) == true)
			{
				obj->t = obj->tmp_t;
				return (check_closest(obj));
			}
			else
				return (false);
				// return (check_closest(obj));	
		}
	}
	return (false);
}


//--------------------//

// static bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
// {
// 	obj->tmp_t = obj->t;
// 	// obj->hit1 = ray->place.y + obj->root1 * ray->vector.y;
// 	// obj->hit2 = ray->place.y + obj->root2 * ray->vector.y;

// 	// if (obj->hit1 < (cyl->vector.y - obj->height_half) || obj->hit1 > cyl->vector.y + obj->height_half)
// 	// 	obj->root1 = obj->hit1;
// 	// 	// obj->hit1 = obj->root1;
// 	// if (obj->hit2 < (cyl->vector.y - obj->height_half) || obj->hit2 > cyl->vector.y + obj->height_half)
// 	// 	obj->root2 = obj->hit2;
// 		// obj->hit2 = obj->root2;

// 	// obj->tmp_t = fmin(obj->hit1, obj->hit2);
// 	obj->tmp_t = fmin(obj->root1, obj->root2);

// 	if (obj->tmp_t > 0)
// 	{
// 		double	denom = dot_product(ray->vector, cyl->vector);
// 		t_vec3	oc = minus(cyl->center, ray->place);
// 		if (fabs(denom) > EPSILON)
// 		{
// 			obj->tmp_t = dot_product(oc, cyl->vector) / denom;
// 			if (obj->tmp_t >= obj->height_half)
// 				return (true);
// 			else
// 				return (false);
// 		}
// 	}
// 	return (false);
// }

static void	check_hit(double root, t_objs *cyl, t_ray *ray, t_obj_data *obj)
{
	t_vec3	a;
	t_vec3	b;

	b = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
	a = plus(ray->place, mult_vecdub(ray->vector, obj->t));

	if (dot_product(cyl->vector, minus(a, cyl->center)) <= 0)
		root = -1;
	if (dot_product(cyl->vector, minus(a, b)) >= 0)
		root = -1;
}	

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
{
	t_vec3	c_c;
	t_vec3	r_c;

	r_c = cross_product(cyl->vector, ray->vector);
	c_c = minus(ray->place, cyl->center);
	c_c = cross_product(c_c, cyl->vector);
	
	obj->radius = cyl->diameter / 2;
	obj->height_half = cyl->height / 2;

	obj->a = dot_product(r_c, r_c);
	obj->b = -2.0 * dot_product(r_c, c_c);
	obj->c = dot_product(c_c, c_c) - pow(obj->radius, 2);
	if (quadratic(obj) == true)
	{
		if (obj->t > EPSILON)
		{	
			if (obj->root1 > 0)
				check_hit(obj->root1, cyl, ray, obj);
			if (obj->root2 > 0)
				check_hit(obj->root2, cyl, ray, obj);
			if (obj->root1 < 0 && obj->root2 < 0)
				return (false);
			if ((obj->root2 < obj->root1 && obj->root2 > 0) || (obj->root1 < obj->root2 && obj->root1 <= 0)) 
				obj->t = obj->root2;
			else
				obj->t = obj->root1;
			return (true); // check_closest(obj);
		// 	if (check_caps(obj, cyl, ray) == true)
		// 	{
		// 		obj->t = obj->tmp_t;
		// 		return (check_closest(obj));
		// 	}
		// 	else
		// 		return (false);
				// return (check_closest(obj));	
		}
	}
	return (false);
}
