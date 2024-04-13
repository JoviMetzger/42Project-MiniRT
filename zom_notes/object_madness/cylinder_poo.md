
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