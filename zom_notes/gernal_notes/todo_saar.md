


--- not implementing ---

 - dont do window resizing

 - dont do textures, remove extra code

 - no inside objects (but actually have to for cylinder...?)



--- to do now ---

 - triangles overlapping colour not gooci
 - check the things dont go wrong using/updating the hit values
 - triple check the normals
 - check the cylinder, all positons etc + cutting edges
 - plane flipping + correct normals
 - cylinder plane flipping + correct normals
 - prep eval files, some basic/simple, some more complicated
 - get rid of waiting message -> a little wait is fine but pop no good
 - triple check parser + new light array -> no leaks, no segfaults etc
 - ensure sphere stretching is acceptable, just test lots of positions
 - cylinder vector 1,1,1 ... check
 - anything else we can do to improve speed?

 - if eval sheet explicitly talks about inside objects, we have to look into that...



----   Jovi normals   ----

colour.intersect_p = plus(ray.place, mult_vecdub(ray.vector, obj_hit->t));
	colour.normal = get_surface_normal(colour.intersect_p, obj);

static t_vec3	normal_for_cylinder(t_vec3 intersection_point, t_objs obj)
{
	t_vec3	vector;
	t_vec3	center_point;
	t_vec3	projection;

	vector = normalize(obj.vector);
	center_point = minus(intersection_point, obj.center);
	projection = mult_vecdub(vector, dot_product(center_point, vector));
	return (minus(center_point, projection));
}

// Get the surface normal for the correct object.
t_vec3	get_surface_normal(t_vec3 intersect_point, t_objs *obj)
{
	t_vec3	normal;

	if (obj->type == E_SPHERE)
		normal = normalize(minus(intersect_point, obj->center));
	if (obj->type == E_PLANE)
		normal = normalize(obj->vector);
	if (obj->type == E_CYLINDER)
		normal = normalize(normal_for_cylinder(intersect_point, *obj));
	return (normal);
}