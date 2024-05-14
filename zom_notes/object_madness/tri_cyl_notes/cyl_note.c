
//------------------------------////------------------------------////------------------------------////------------------------------//
//------------------------------////------------------------------////------------------------------//
//------------------------------////------------------------------////------------------------------////------------------------------//
//------------------------------////------------------------------////------------------------------//

static int	solve_caps(t_eq *caps, t_object *obj, t_vector ray)
{
	short		res[2];
	t_vector	cap_c[2];
	t_vector	hit[2];

	ft_memset(&res, 0, sizeof(res));
	if (caps->dist1 >= MIN_DIST)
	{
		hit[0] = vect_mult(ray, caps->dist1);
		cap_c[0] = vect_add(obj->center, vect_mult(obj->norm_v, caps->m1));
		res[0] = (fabs(point_dist(hit[0], cap_c[0])) <= obj->radius);
	}
	if (caps->dist2 >= MIN_DIST)
	{
		hit[1] = vect_mult(ray, caps->dist2);
		cap_c[1] = vect_add(obj->center, vect_mult(obj->norm_v, caps->m2));
		res[1] = (fabs(point_dist(hit[1], cap_c[1])) <= obj->radius);
	}
	if (!res[0] && !res[1])
		return (0);
	if ((res[0] && res[1] && caps->dist2 < caps->dist1) || !res[0])
	{
		caps->dist1 = caps->dist2;
		caps->m1 = caps->m2;
	}
	return (1);
}

int	get_cylinder_caps(t_eq *caps, t_object *obj, t_vector ray, t_vector origin)
{
	float		dot_r_nv;
	t_vector	orig_pl1;
	t_vector	orig_pl2;

	normalise_vect(&obj->norm_v);
	dot_r_nv = vect_dot_product(ray, obj->norm_v);
	if (dot_r_nv == 0 || fabs(dot_r_nv) < MIN_DIST)
		return (0);
	caps->m1 = obj->height;
	caps->m2 = -obj->height;
	orig_pl1 = vect_substract(origin,
			vect_add(obj->center, vect_mult(obj->norm_v, caps->m1)));
	orig_pl2 = vect_substract(origin,
			vect_add(obj->center, vect_mult(obj->norm_v, caps->m2)));
	caps->dist1 = -vect_dot_product(orig_pl1, obj->norm_v) / dot_r_nv;
	caps->dist2 = -vect_dot_product(orig_pl2, obj->norm_v) / dot_r_nv;
	if (caps->dist1 < MIN_DIST && caps->dist2 < MIN_DIST)
		return (0);
	return (solve_caps(caps, obj, ray));
}



//------------------------------////------------------------------////------------------------------////------------------------------//
//------------------------------////------------------------------////------------------------------//

//------------------------------////------------------------------////------------------------------////------------------------------//
//------------------------------////------------------------------////------------------------------//

new caps aproach: NO

double	pick_cy_inter(t_cylinder inf, t_CamRay *ray, t_objs *cy)
{
	inf.t1 = (-inf.b + sqrt(inf.delta)) / (2 * inf.a);
	inf.t2 = (-inf.b - sqrt(inf.delta)) / (2 * inf.a);
	if (inf.t1 < EPS)
		return (-1.0);
	if (inf.t1 > inf.t2)
		inf.t = inf.t2;
	else
		inf.t = inf.t1;


	inf.y0 = dot_product(ray->dir, inf.normal) * inf.t2
		+ dot_product(inf.oc, inf.normal);
	inf.y1 = dot_product(ray->dir, inf.normal) * inf.t1
		+ dot_product(inf.oc, inf.normal);
	if (inf.y0 >= EPS && inf.y0 <= cy->p.y)
		return (inf.t2);
	if (inf.y1 >= EPS && inf.y1 <= cy->p.y)
		return (inf.t1);
	return (-1.0);
}


//------------------------------//
//------------------------------////------------------------------////------------------------------////------------------------------//


double	plane_cyl(t_ray *ray, t_vec3 center, t_vec3 vector)
{
	double	x;
	double	denom;
	t_vec3	oc;

	denom = dot_product(ray->vector, vector);
	if (fabs(denom))
	{
		oc = minus(ray->place, center);
		x = -dot_product(oc, vector) / denom;
		if (x < 0)
			x = INFINITY;
		return (x);
	}
	return (INFINITY);
}

bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	double hit1;
	double hit2;
	t_vec3 pnt1;
	t_vec3 pnt2;
	t_vec3 cent2;

	cent2 = plus(cyl->center, mult_vecdub(cyl->vector, obj->height_half));

	hit1 = plane_cyl(ray, cyl->center, cyl->vector);
	hit2 = plane_cyl(ray, cent2, cyl->vector);

	if (hit1 < INFINITY || hit2 < INFINITY)
	{
		pnt2 = plus(mult_vecdub(ray->vector, hit2), ray->place);
		pnt1 = plus(mult_vecdub(ray->vector, hit1), ray->place);
		if ((hit1 < INFINITY && distance(cyl->center, pnt1) <= obj->radius) 
			&& (hit2 < INFINITY && distance(cent2, pnt2) <= obj->radius))
		{
			if (hit1 < hit2)
				obj->t = hit1;
			else
				obj->t = hit2;
			return (true);
		}
		if (hit1 < INFINITY && distance(cyl->center, pnt1) <= obj->radius)
		{
			obj->t = hit1;
			return (true);
		}
		else if (hit2 < INFINITY && distance(cent2, pnt2) <= obj->radius)
		{
			obj->t = hit2;
			return (true);
		}
		return (false);
	}
	return (false);
}


//------------------------------//
/**

 * 
 * 

// // infinity shittt
// // double	plane_cyl(t_obj_data *obj, t_ray *ray, t_vec3 center, t_vec3 vector)
// // {
// // 	t_vec3 oc;
// // 	double	denom;

// // 	denom = dot_product(ray->vector, vector);
// // 	if (fabs(denom) > EPSILON)
// // 	{
// // 		oc = minus(ray->place, center);
// // 		obj->t = -dot_product(oc, vector) / denom;
// // 		if (obj->t >= EPSILON)
// // 			return (check_closest(obj));
// // 		else
// // 			return (INFINITY);
// // 	}
// // 	return (INFINITY);
// // }
 * 
 * 		// not sure this bit is necessary.. doesnt seem to ever hit?
		// if ((hit1 < INFINITY && distance(pnt1, cyl->center) <= obj->radius) 
		// 	&& (hit2 < INFINITY && distance(pnt2, cent2) <= obj->radius))
		// {
		// 	// printf("this hit\n");/
		// 	if (hit1 < hit2) // more or less?
		// 		obj->t = hit1;
		// 	else
		// 		obj->t = hit2;
		// 	return (true);
		// }
 * 
 * 				t_vec3 hit = plus(ray->place, mult_vecdub(ray->vector, obj->t));
				t_vec3 ctp = minus(hit, cyl->center);
				t_vec3 normal = minus(ctp, mult_vecdub(cyl->vector, dot_product(cyl->vector, ctp)));
				normalize_vector(normal);
				if (dot_product(normal, ray->vector) > EPSILON)
					normal = mult_vecdub(normal, -1);
				cyl->center = normal;
 * 

 * not sure if in root check function, find cap or just in intersect cyl
 * also, how find cap? and if cap count what do?
 */

// double			solve_plane(t_p3 o, t_p3 d, t_p3 plane_p, t_p3 plane_nv)
// {
// 	double	x;
// 	double	denom;

// 	denom = dot(plane_nv, d);
// 	if (denom == 0)
// 		return (INFINITY);
// 	x = (dot(plane_nv, vsubstract(plane_p, o))) / denom;
// 	return (x > 0 ? x : INFINITY);
// }

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
