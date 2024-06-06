/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 15:45:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/06 19:58:29 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Function to calculate the surface normal of a cylinder
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

/*	This Function calculates the base colour of an object.
 *		- So if the object has a pattern (Checkerboard, texture),
 *		  it will first calculate that pattern and use it as a base colour,
 *		  before it applies the 'Phong reflection model'.
 *		- If the object is plain (has no pattern),
 *		  it will return the colour of the object as the base colour.	
 */
t_colour	get_base_colour(t_objs *obj, t_colour_vars colour)
{
	t_colour	base;

	if (obj->what_pattern == 1)
	{
		if (obj->type == E_SPHERE)
			base = get_sphere_checkerboard(colour.normal);
		if (obj->type == E_PLANE)
			base = get_plane_checkerboard(obj, colour.normal);
		if (obj->type == E_CYLINDER)
			base = get_cylinder_checkerboard(colour.normal);
	}
	else
		base = obj->colour;
	return (base);
}

/*	Calculate the reflection direction using 
 *	the incident ray direction and surface normal.
 */
t_vec3	ft_reflect(t_vec3 incident, t_vec3 normal)
{
	return (minus(incident, mult_vecdub(normal, 2
				* dot_product(incident, normal))));
}

//	Bit shifts the ints rg,b, 
//	so that the correct colour is displayed into mlx_put_pixel();
int32_t	ft_convert_rgb(int32_t r, int32_t g, int32_t b)
{
	int32_t	a;

	a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}
