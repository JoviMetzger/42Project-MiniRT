
--------------------------------------------------------------------------
--- to do now ---

!!!
 - are in the light or no function - maybe actually save pixels... then check objs closer to the ray for shadows, then draw... talk to jovi... 
 - add light array to new colour calculating shizzle

!!
 - cylinder normal when turned on z vector not guuci (0,1,1) / (1,0,1)
 - check the cylinder, all positons etc + cutting edges
 - cylinder plane flipping + correct normals
 - plane flipping + correct normals

!
 - prep eval files, some basic/simple, some more complicated
 - get rid of waiting message -> a little wait is fine but pop no good
 - triple check parser + new light array -> no leaks, no segfaults etc

+
 - cylinder vector 1,1,1 ... check
 - anything else we can do to improve speed?

 - if eval sheet explicitly talks about inside objects, we have to look into that...
--------------------------------------------------------------------------





//////// loads of notes from shadow day

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




------ old from get_colour file


/* Calculation of the light_ray and if it hits a object, 
 * it should not go trough the object, so that it gives a shadow.
 *	  - Creating a light_direction.
 *	  - Initializing the place & vector of the shadow_ray.
 *	  - Check for shadows by testing intersection with all objects.
 *		 - If an intersection is hit, there will be a shadow.
 *		 - If no intersection hit (!is_shadow), add light.
 *		    - Calculate diffuse light contribution.
 *		    - Calculate specular light contribution.
 *		    - Accumulate light contributions. 
 *			 (newColour += diffuse_colour * base_colour / 255 + specular_colour)
 */
// static void	shadow_calculation(t_data *data, t_colour_vars *colour,
// 		t_ray ray, t_hit_data *obj_hit)
// {
// 	(void)obj_hit;
// 	// t_ray	shadow_ray;
// 	// bool	in_shadow;
// 	// int		i;

// 	// colour.light_dir = normalize(minus(colour->curr_light->place,
// 				// colour->intersect_p));
// 	// shadow_ray.place = plus(colour->intersect_p, mult_vecdub(colour->normal,
// 	// 			EPSILON));
// 	// shadow_ray.vector = colour->light_dir;
// 	// in_shadow = false;
// 	// i = -1;
// 	// while (++i < data->objs_i)
// 	// {
// 	// 	if (intersect_sphere(&shadow_ray, data->objs[i], obj_hit)
// 	// 		|| intersect_plane(&shadow_ray, data->objs[i], obj_hit)
// 	// 		|| intersect_cylinder(&shadow_ray, data->objs[i], obj_hit)
// 	// 		|| intersect_triangle(&shadow_ray, data->objs[i], obj_hit))
// 	// 	{
// 	// 		in_shadow = true;
// 	// 		break ;
// 	// 	}
// 	// }
// 	// printf("bool = %i\n", data->is_shadow);
// 	if (!data->is_shadow)
// 	{
// 		// printf("bool = %i\n", data->is_shadow);
// 		add_light(colour, ray);
// 	}
// }


/*	Initializing the t_colour_vars struct.
 *		- Using the 'Phong reflection model'
 *			- Using the surface normal for the right object. 
 *		- Calculate ambient light contribution. (am_ratio * am_colour)
 *		- Initialize result color with ambient light contribution.
 */
// static t_colour_vars	init_colour_struct(t_data *data, t_hit_data *obj_hit,
// 				t_ray ray, t_objs *obj)
// {
// 	t_colour_vars	colour;

// 	// colour.ambient_ratio = data->ambient.ratio;
// 	// colour.spec_intensity = 0.2;
// 	// colour.spec_power = 32;
// 	init_colout(data);
// 	colour.intersect_p = plus(ray.place, mult_vecdub(ray.vector, obj_hit->t));
// 	colour.normal = get_surface_normal(colour.intersect_p, obj);
// 	// colour.ambient.r = colour.ambient_ratio * data->ambient.colour.r;
// 	// colour.ambient.g = colour.ambient_ratio * data->ambient.colour.g;
// 	// colour.ambient.b = colour.ambient_ratio * data->ambient.colour.b;
// 	// colour.result.r = colour.ambient.r;
// 	// colour.result.g = colour.ambient.g;
// 	// colour.result.b = colour.ambient.b;
// 	return (colour);
// }




		// if (data->objs[j]->obj_hit < DBL_MAX)
		// {
		// 	// 
		// }
		// // hit->t per obj loop, checking if shadow ray hits
		// // way of not doing this? + changing hit data? + saving the closest hit/going in order of file array
// REMEMBER LIGHT ARRAY..


// update_shadow_colour
// change back/cover with ambient lighting
