

uint32_t ft_calculate_colour(t_data *data, t_obj_data *obj_data, t_ray ray)
{
	// printf("\n--- OBJ ---\na: %f\nb: %f\nc: %f\nd: %f\nroot1: %f\nroot2: %f\nt: %f\n", obj_data->a, obj_data->b, obj_data->c, obj_data->d, obj_data->root1, obj_data->root2, obj_data->t);
	// printf("TYPE: %f %f %f\n", data->objs->center.x, data->objs->center.y, data->objs->center.z);

	t_colour	colour;
	int		i = 0;
	double closest_t = DBL_MAX; // Initialize closest intersection distance to a large value

	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_SPHERE)
		{
			if (intersect_sphere(&ray, data->objs[i], obj_data))
			{
				// Check if the intersection point is closer than previous intersections
                if (obj_data->t < closest_t)
                {
                    closest_t = obj_data->t; // Update closest intersection distance
					colour = get_sphere_colour(data, obj_data, ray, data->objs[i]);
					// colour = get_sphere_checherboard(data, obj_data, ray, data->objs[i]);	// will be moved
					// colour = get_sphere_bumpmap(data, obj_data, ray, data->objs[i]);	// will be moved
                }
			}
		}
		// else if (data->objs[i]->type == E_PLANE)
		// {
		// 	if (obj_data->t < closest_t)
        //     {
        //         closest_t = obj_data->t;
		// 		colour = get_plane_colour(data, obj_data, ray, data->objs[i]);
		// 	}
		// }
		// else if (data->objs[i]->type == E_CYLINDER)
		// {
		// 	if (obj_data->t < closest_t)
        //     {
        //         closest_t = obj_data->t;
		// 		colour = get_cylinder_colour(data, obj_data, ray, data->objs[i]);
		// 	}
		// }
		i++;

	}
	if (closest_t != DBL_MAX)
        return (ft_convert_rgb(colour.r, colour.g, colour.b));
    else
        return (ft_convert_rgb(0, 0, 0)); // No intersection found, return black
}

	• obtaining [ t1, t2 ]
	– The equation of the infinite height cylinder :
	– xsq + ysq = rsq
	– Substituting the ray equation in this equation we obtain:
	tsq . ( dxsq + dysq ) + 2t . (x0 . dx + y0 . dy ) + ( x0sq + y0sq - r2 ) = 0
	– Solving this equation gives the interval [ t1, t2 ].

	• obtaining [ t3, t4 ]
	– Let A and B the two values of t resulting from the intersection
	with the two planes :
	A = - z0 / dz and B = ( h - z0 ) / dz
	• We get :
	t3 = min( A,B ) and t4 = max( A, B )



// bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
// {
// 	t_vec3	oc;
// 	double	radius;

// 	radius = cylinder->diameter / 2;

// 	oc = minus(ray->place, cylinder->center);

// 	obj_data->a = (dot_product(ray->vector, ray->vector)) - (pow(dot_product(ray->vector, cylinder->center), 2));
// 	obj_data->b = 2.0 * dot_product(oc, ray->vector) - (dot_product(ray->vector, cylinder->center) * dot_product(oc, cylinder->center));
// 	obj_data->c = dot_product(oc, oc) - pow(dot_product(oc, cylinder->center), 2) - pow(radius, 2);

	
// 	obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;
// 	if (obj_data->d < 0)
// 	{	
// 		return (false); // no intersection
// 	}
// 	else
// 	{
// 		obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2 * obj_data->a);
// 		obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2 * obj_data->a);
// 		if (obj_data->root1 > obj_data->root2)
// 			obj_data->t = obj_data->root1;
// 		else
// 			obj_data->t = obj_data->root2;
// 		return (true); // Intersection found
// 	}
// }



/*
**Cylinder**
	• The cylinder : intersection between an infinite height cylinder and the
	subspace delimited by two planes which equations are
	z = 0 and z= h
	• The intersection between the ray an the infinite height cylinder is first
	performed. This yields a first interval [t1,t2]
	• The intersection with the two planes gives a second interval [ t3, t4 ].
	• The final intersection interval [ I, M ] results from the combination of these
	two intervals ( as for the parallelepiped).

	• obtaining [ t1, t2 ]
	– The equation of the infinite height cylinder :
	– x2 + y2 = r2
	– Substituting the ray equation in this equation we obtain:
	tsq . ( dxsq + dysq ) + 2t . (x0 . dx + y0 . dy ) + ( x0sq + y0sq - r2 ) = 0
	
	– Solving this equation gives the interval [ t1, t2 ].
	• obtaining [ t3, t4 ]
	– Let A and B the two values of t resulting from the intersection
	with the two planes :
	A = - z0 / dz and B = ( h - z0 ) / dz
	• We get :
	t3 = min( A,B ) and t4 = max( A, B )
	
*/

// height, rotation... cylinder vector... 
/**
 * 	GENERAL NOTE
	P = P0 + t . D
	• where :
	P0 is the ray origin;
	D = (dx, dy, dz) is the direction vector of the ray ;
	t > 0 
 */




*/
/**
 * 
 * float Cylinder::intersect(Vector pos, Vector dir)
{   
    float a = (dir.x * dir.x) + (dir.z * dir.z);
    float b = 2*(dir.x*(pos.x-center.x) + dir.z*(pos.z-center.z));
    float c = (pos.x - center.x) * (pos.x - center.x) + (pos.z - center.z) * (pos.z - center.z) - (radius*radius);
    
    float delta = b*b - 4*(a*c);
	if(fabs(delta) < 0.001) return -1.0; 
    if(delta < 0.0) return -1.0;
    
    float t1 = (-b - sqrt(delta))/(2*a);
    float t2 = (-b + sqrt(delta))/(2*a);
    float t;
    
    if (t1>t2) t = t2;
    else t = t1;
    
    float r = pos.y + t*dir.y;
    
    if ((r >= center.y) and (r <= center.y + height))return t;
    else return -1;
}

* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the sphere.
Vector Cylinder::normal(Vector p)
    Vector n = Vector (p.x-center.x,0,p.z-center.z);
    n.normalise();
    return (n);
*/

pl              2,0,-3       0.0,1.0,0.0     0,255,225
pl              0,0,-5       0.0,1.0,0.0     0,255,0
pl              -2,0,-3       0.0,1.0,0.0     0,0,22


weird orange cycle stuff
pl              2,0,-3       0,0.2,-1    255,255,255
pl              0,5,5       0,1,-1    255,0,0
pl              1,2,1       0,0,0    255,0,255



big blobby orange curve
pl              0,5,5       0,1,-1    255,0,0

nothing?
pl              1,2,1       0,0,0    255,0,255


white cycle
pl              2,0,-3       0,0.2,-1    255,255,255


/**
 * 
 * t_inter_point ft_cylinder_collision(t_ray ray, t_pack cylinder, int id)
{
    t_inter_point inter_point;
    t_delta delta;
    t_ray new_ray;
    t_vect c_to_o;

    inter_point.hit = FALSE;
    inter_point.id = id;
    new_ray.origin = ray.origin;
    cylinder.rot = normalize(cylinder.rot);
    new_ray.direction = cross(ray.direction, cylinder.rot);
	
    c_to_o = sub(ray.origin, cylinder.pos);
    delta.a = dot(new_ray.direction, new_ray.direction);
    delta.b = 2 * dot(new_ray.direction, cross(c_to_o, cylinder.rot));
    delta.c = dot(cross(c_to_o, cylinder.rot), cross(c_to_o, cylinder.rot)) - pow(cylinder.diameter / 2, 2);
    delta.delta = pow(delta.b, 2) - 4 * delta.c * delta.a;
   
    if (delta.delta < 0)
        return (inter_point);
    inter_point.t1 = (-delta.b - sqrt(delta.delta)) / (2 * delta.a);
    inter_point.t2 = (-delta.b + sqrt(delta.delta)) / (2 * delta.a);
    if (inter_point.t2 < 0)
        return (inter_point);
    inter_point.t = (inter_point.t1 > 0 ? inter_point.t1 : inter_point.t2);
    return (ft_find_edges(cylinder, ray, inter_point));
}
*/


// coords, 3D ector, diameter, height, rgb
// vector for cylinder needs to be used plus height
bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
{
	t_vec3	oc;

	oc = minus(ray->place, cylinder->center);

	// obj_data->a = (dot_product(ray->vector, ray->vector)) - (pow(dot_product(ray->vector, cylinder->center), 2));

	// obj_data->b = 2.0 * dot_product(ray->vector, cross_product(oc, cylinder->center));
	// obj_data->c = dot_product(cross_product(oc, cylinder->center), cross_product(oc, cylinder->center)) - pow(cylinder->diameter / 2, 2);
	// obj_data->d = pow(obj_data->b, 2) - 4 * obj_data->c * obj_data->a;
	
	obj_data->b = 2.0 * ray->place.x * ray->vector.x + 2 * ray->place.z * ray->vector.z;

	obj_data->c = pow(ray->place.x, 2) + pow(ray->place.z, 2) - 1;
	
	obj_data->d = pow(obj_data->b, 2) - 4 * obj_data->c * obj_data->a;

	if (obj_data->d < 0)
		return (false); // no intersection
	else
	{
		obj_data->t = (-obj_data->b + sqrt(obj_data->d)) / (2 * obj_data->a);
		if (obj_data->t >= EPSILON)
			return (true);

		// obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2.0 * obj_data->a);
        // obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2.0 * obj_data->a);
        // if (obj_data->root1 < obj_data->root2)
        //     obj_data->t = obj_data->root1;
        // else
        //     obj_data->t = obj_data->root2;
        // return (true); // Intersection found
	}
	return (false);
}


JUST A WEIRD THINGY
bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
{
	t_vec3	oc;
	double	radius;

	radius = cylinder->diameter / 2;
	oc = minus(ray->place, cylinder->center);

	obj_data->a = (dot_product(ray->vector, ray->vector)) - (pow(dot_product(ray->vector, cylinder->center), 2));
	obj_data->b = 2.0 * dot_product(oc, ray->vector) - (dot_product(ray->vector, cylinder->center) * dot_product(oc, cylinder->center));
	obj_data->c = dot_product(oc, oc) - pow(dot_product(oc, cylinder->center), 2) - pow(radius, 2);

	// if (obj_data->a == 0 && obj_data->b != 0)
	// {
	// 	obj_data->root1 = -obj_data->c / obj_data->b;
	// 	return (true);
	// }
	// else
	// {
	obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;
	// obj_data->d = pow(obj_data->b, 2) - (4 * obj_data->a * obj_data->c);
	if (obj_data->d < 0)
		return (false); // no intersection
	else
	{
		obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2 * obj_data->a);
		obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2 * obj_data->a);
		if (obj_data->root1 < obj_data->root2)
			obj_data->t = obj_data->root1;
		else
			obj_data->t = obj_data->root2;
		return (true); // Intersection found
	}
}