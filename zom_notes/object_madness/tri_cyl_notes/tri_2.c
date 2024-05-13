


// TRY THIS

double			triangle_intersection(t_p3 o, t_p3 d, t_figures *lst)
{
	double	id;
	t_p3	ip;

	id = solve_plane(o, d, lst->fig.tr.p1, lst->normal);
	ip = vadd(o, scal_x_vec(id, d));
	if (p_is_outside(lst->fig.tr.p1, lst->fig.tr.p2, lst->fig.tr.p3, ip))
		return (INFINITY);
	if (p_is_outside(lst->fig.tr.p2, lst->fig.tr.p3, lst->fig.tr.p1, ip))
		return (INFINITY);
	if (p_is_outside(lst->fig.tr.p3, lst->fig.tr.p1, lst->fig.tr.p2, ip))
		return (INFINITY);
	return (id);
}



// does not hit triangle
bool		intersect_triangle(t_ray *ray, t_objs *tri, t_obj_data *obj_data)
{
	t_vec3	edge1;
	t_vec3	edge2;

	t_vec3	hit;
	t_vec3	tvec;
	t_vec3	normal;

	edge1 = minus(tri->point2, tri->point1);
	edge2 = minus(tri->point3, tri->point1);

	hit = cross_product(ray->vector, edge2);
	obj_data->t = dot_product(edge1, hit);

	normal = mult_vecvec(edge1, edge2);

	if (fabs(obj_data->t) < EPSILON)
		return (false);

	obj_data->c = 1 / obj_data->t;
	tvec = minus(ray->place, tri->point1);


	obj_data->a = dot_product(edge1, hit) * obj_data->c;
	if (obj_data->a < 0 || obj_data->a > 1)
		return (false);

	tvec = cross_product(tvec, edge1);
	obj_data->b = dot_product(ray->vector, tvec) * obj_data->c;

	if (obj_data->b < 0 || obj_data->a + obj_data->b > 1)
		return (false);

	obj_data->t = dot_product(edge2, tvec) * obj_data->c;
	return (true);
}


// does hit
bool		intersect_triangle(t_ray *ray, t_objs *tri, t_obj_data *obj_data)
{
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	hit;
	// t_vec3	normal;
	float	dir;

	edge1 = minus(tri->point2, tri->point1);
	edge2 = minus(tri->point3, tri->point1);

	hit = cross_product(ray->vector, edge2);
	dir = dot_product(edge1, hit);

	// normal = mult_vecvec(edge1, edge2);
	
	if (dir > -EPSILON && dir < EPSILON) // fabs?
		return (false);
		
		
	double f = 1.0 / dir;
	
	t_vec3 s = minus(ray->place, tri->point1);
	
	double u = dot_product(s, hit); // edge1, hit
	u = f * u;
	if (u < 0.0 || u > 1.0)
		return (false);
	t_vec3 q = cross_product(s, edge1);
	double v = dot_product(ray->vector, q);
	v = f * v;
	if (v < 0.0 || u + v > 1.0)
		return (false);
	obj_data->t = dot_product(q, edge2);
	obj_data->t = f * obj_data->t;
	// tri->center = hit;
	// tri->center = cross_product(edge1, edge2);
	if (obj_data->t > EPSILON)
		return (true);
	else
		return (false);
}



// does hit // mix of two above
bool		intersect_triangle(t_ray *ray, t_objs *tri, t_obj_data *obj_data)
{
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	hit;
	// t_vec3	normal;
	float	dir;

	edge1 = minus(tri->point2, tri->point1);
	edge2 = minus(tri->point3, tri->point1);

	hit = cross_product(ray->vector, edge2);
	dir = dot_product(edge1, hit);

	// normal = mult_vecvec(edge1, edge2);
	
	if (dir > -EPSILON && dir < EPSILON) // fabs?
		return (false);
		
		// f = a
		// u = b
		// v = c
		// q vec3 - c_c
		// s vec3 - o_c (tvec)
		
	obj_data->a = 1.0 / dir;
	t_vec3 o_c = minus(ray->place, tri->point1);
	

	obj_data->b = dot_product(edge1, hit);
	obj_data->b = obj_data->a * obj_data->b;
	
	if (obj_data->b < 0.0 || obj_data->b > 1.0)
		return (false);
		
	o_c = cross_product(o_c, edge1); 
	
	obj_data->c = dot_product(o_c, edge1);
	obj_data->c = obj_data->a * obj_data->c;
	if (obj_data->c < 0.0 || obj_data->b + obj_data->c > 1.0)
		return (false);

		
	// obj_data->d = dot_product(c_c, edge2); // edge2, q
	// obj_data->t = obj_data->a * obj_data->t;

	// if (obj_data->t < 0 || u + obj_data->t > 1)
	// 	return (false);

	obj_data->t = dot_product(edge2, o_c);
	return (true);


	
	// if (obj_data->t > EPSILON)
	// 	return (true);
	// else
	// 	return (false);
}


//---------------- total mess ------------//


// bool		intersect_triangle(t_ray *ray, t_objs *tri, t_obj_data *obj_data)
// {
// 	t_vec3	vec1 = tri->point1;
// 	t_vec3	vec2 = tri->point2;
// 	t_vec3	vec3 = tri->point3;
	
// 	t_vec3	thing1;
// 	t_vec3	thing2;
	
// 	t_vec3	ray_normal;
// 	t_vec3	tri_normal;

// 	t_vec3	pvec;
// 	t_vec3	qvec;
// 	t_vec3	tvec;

// 	float	d;
// 	float	u;
// 	float	v;

// 	thing1 = minus(vec2, vec1);
// 	thing2 = minus(vec3, vec1);
	
// 	pvec = cross_product(ray->vector, thing2);

// 	tri_normal = mult_vecvec(vec1, vec2);
// 	ray_normal = normalize_vector(ray->vector); // necessary?
	
// 	// d = dot_product(pvec, thing1);

// 	// if (d < EPSILON)
// 	// 	return (false);
	
// 	// tvec = minus(ray->place, vec1);
// 	// u = dot_product(tvec, pvec);
	
// 	// if (u < 0.0 || u > d)
// 	// 	return (false);
	
// 	// qvec = cross_product(tvec, thing1);
// 	// v = dot_product(ray->vector, qvec);
// 	// if (v < 0.0f || v + u > d)
// 	// 	return (false);
	
// 	// if (d < EPSILON && d > -EPSILON)
// 	// 	return (false);

// 	// float	det = 1.0f / d;
// 	// tvec = minus(ray->place, vec1);
	
// 	// float g = det * dot_product(tvec, pvec);
// 	// if (g < 0.0f || g > 1.0f)
// 	// 	return (false);

// 	// qvec = cross_product(tvec, thing1);

// 	// float h = det * dot_product(qvec, ray->vector);
// 	// if (h < 0.0f || g + h > 1.0f)
// 	// 	return (false);

// 	// // double distance = 40; //dot_product(thing2, qvec)
// 	// tri->center = plus(ray->place, mult_vecdub(ray->vector, obj_data->t));
// 	// obj_data->t = 40;
// 	// return (true);

// 	tri->center = tri_normal;
// 	tri->center = tri->point1;

// 	obj_data->t = dot_product(vec1, tri_normal);

// 	if (fabs(obj_data->t) < EPSILON)
// 		return (false);
// 		// return (printf("this one\n"), false);
		
// 	obj_data->c = 1 / obj_data->t;
// 	tvec = minus(ray->place, tri->point1);
// 	obj_data->a = dot_product(vec1, pvec) * obj_data->c;
// 	if (obj_data->a < 0 || obj_data->a > 1)
// 		return (false);
// 		// return (printf("this two\n"), false);
// 	tvec = cross_product(tvec, vec1);
// 	obj_data->b = dot_product(ray->vector, tvec) * obj_data->c;
// 	if (obj_data->b < 0 || obj_data->a + obj_data->b > 1)
// 		return (false);
// 		// return (printf("this three\n"), false);
// 	obj_data->t = dot_product(vec2, tvec) * obj_data->c;
// 	return (true);
// }

// bool		intersect_triangle(t_ray *ray, t_objs *tri, t_obj_data *obj_data)
// {
// 	t_vec3	vec1;
// 	t_vec3	vec2;
// 	t_vec3	pvec;
// 	t_vec3	tvec;
// 	t_vec3	normal;

// 	vec1 = minus(tri->point2, tri->point1);
// 	vec2 = minus(tri->point3, tri->point1);

// 	normal = mult_vecvec(vec1, vec2);

// 	pvec = cross_product(ray->vector, vec2);
// 	obj_data->t = dot_product(vec1, pvec);

// 	if (fabs(obj_data->t) < EPSILON)
// 		return (false);
// 	obj_data->c = 1 / obj_data->t;
// 	tvec = minus(ray->place, tri->point1);
// 	obj_data->a = dot_product(vec1, pvec) * obj_data->c;
// 	if (obj_data->a < 0 || obj_data->a > 1)
// 		return (false);
// 	tvec = cross_product(tvec, vec1);
// 	obj_data->b = dot_product(ray->vector, tvec) * obj_data->c;
// 	if (obj_data->b < 0 || obj_data->a + obj_data->b > 1)
// 		return (false);
// 	obj_data->t = dot_product(vec2, tvec) * obj_data->c;
// 	return (true);
// }
