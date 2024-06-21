/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_colour.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 15:11:36 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/20 18:59:27 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// // TODO norm, add utils to colour_utils file

// // Calculation of the diffuse light
// static void	diffuse_light(t_colour_vars *colour)
// {
// 	colour->diff_fact = dot_product(colour->normal, colour->light_dir);
// 	if (colour->diff_fact < 0.0)
// 		colour->diff_fact = 0.0;
// 	colour->diffuse.r = colour->curr_light->ratio * colour->diff_fact
// 		* colour->curr_light->colour.r;
// 	colour->diffuse.g = colour->curr_light->ratio * colour->diff_fact
// 		* colour->curr_light->colour.g;
// 	colour->diffuse.b = colour->curr_light->ratio * colour->diff_fact
// 		* colour->curr_light->colour.b;
// }


// // Calculation of the specular light
// static void	specular_light(t_colour_vars *colour, t_ray ray)
// {
// 	colour->view_dir = normalize(minus(ray.place, colour->intersect_p));
// 	colour->ref_dir = normalize(ft_reflect(colour->light_dir, colour->normal));
// 	colour->spec_fact = pow(dot_product(colour->ref_dir, colour->view_dir),
// 			colour->spec_power);
// 	if (colour->spec_fact < 0.0)
// 		colour->spec_fact = 0.0;
// 	colour->specular.r = colour->spec_intensity * colour->spec_fact
// 		* colour->curr_light->colour.r;
// 	colour->specular.g = colour->spec_intensity * colour->spec_fact
// 		* colour->curr_light->colour.g;
// 	colour->specular.b = colour->spec_intensity * colour->spec_fact
// 		* colour->curr_light->colour.b;
// }

// uint32_t	get_light(t_data *data, t_ray ray, t_objs *obj)
// {
// 	// light init stuff
// 	data->vars.curr_light = data->light[0];
// 	data->vars.intersect_p = plus(data->ray.place, mult_vecdub(data->ray.vector, obj->obj_t));
// 	data->vars.light_dir = normalize(minus(data->vars.curr_light->place,
// 		data->vars.intersect_p));
// 	data->vars.normal = obj->normal;


// 	// combine ambient, diffuse and specular

// 	// add diffuse + clamp
// 	diffuse_light(&data->vars);
// 	data->vars.result.r = data->vars.base.r + data->vars.diffuse.r;
// 	data->vars.result.g = data->vars.base.g + data->vars.diffuse.g;
// 	data->vars.result.b = data->vars.base.b + data->vars.diffuse.b;

// 	data->vars.result.r = fmin(fmax(data->vars.result.r, obj->colour.r), 255);
// 	data->vars.result.g = fmin(fmax(data->vars.result.g, obj->colour.g), 255);
// 	data->vars.result.b = fmin(fmax(data->vars.result.b, obj->colour.b), 255);


// 	// add specular + clamp
// 	specular_light(&data->vars, ray);
// 	data->vars.result.r += data->vars.result.r / 255 + data->vars.specular.r;
// 	data->vars.result.g += data->vars.result.g / 255 + data->vars.specular.g;
// 	data->vars.result.b += data->vars.result.b / 255 + data->vars.specular.b;

// 	data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
// 	data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
// 	data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));
// 	return ft_convert_rgb(data->vars.result.r, data->vars.result.g, data->vars.result.b);
// }

// /*	STEP 3. Compute a color for the closest intersection point.
//  *
//  *	This function uses the 'Phong reflection model' for each object.
//  *	Including multiple light and creating shadows.
//  *		- Initializing colour_vars.
//  *		- Initializing the base colour of the object.
//  *		- Initializing the result of the colour with ambient light contribution.
//  *		  (colour = ambient * base / 255)
//  *		- Goes through all the different light 
//  *		  and does the shadow_calculation on each object for each light.
//  *		- Clamp final values to [0, 255]. 
//  *		  This ensurs that the value is not less than 0 and not bigger than 255. 
//  *		  So basiclly controls the overflow/underflow of RGB colour range.
//  */
// uint32_t	get_ambient(t_data *data, t_objs *obj)
// {
// 	// ambient
// 	data->vars.base = get_base_colour(obj, &data->vars);
	

// 	// final ambient
// 	data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
// 	data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
// 	data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));
// 	return ft_convert_rgb(data->vars.result.r, data->vars.result.g, data->vars.result.b);
// }


// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------

// TODO norm, add utils to colour_utils file

// Calculation of the diffuse light
static void	diffuse_light(t_colour_vars *colour)
{
	colour->diff_fact = dot_product(colour->normal, colour->light_dir);
	if (colour->diff_fact < 0.0)
		colour->diff_fact = 0.0;
	colour->diffuse.r = colour->curr_light->ratio * colour->diff_fact
		* colour->curr_light->colour.r;
	colour->diffuse.g = colour->curr_light->ratio * colour->diff_fact
		* colour->curr_light->colour.g;
	colour->diffuse.b = colour->curr_light->ratio * colour->diff_fact
		* colour->curr_light->colour.b;
}


// Calculation of the specular light
static void	specular_light(t_colour_vars *colour, t_ray ray)
{
	colour->view_dir = normalize(minus(ray.place, colour->intersect_p));
	colour->ref_dir = normalize(ft_reflect(colour->light_dir, colour->normal));
	colour->spec_fact = pow(dot_product(colour->ref_dir, colour->view_dir),
			colour->spec_power);
	if (colour->spec_fact < 0.0)
		colour->spec_fact = 0.0;
	colour->specular.r = colour->spec_intensity * colour->spec_fact
		* colour->curr_light->colour.r;
	colour->specular.g = colour->spec_intensity * colour->spec_fact
		* colour->curr_light->colour.g;
	colour->specular.b = colour->spec_intensity * colour->spec_fact
		* colour->curr_light->colour.b;
}


// // Function to calculate the surface normal of a cylinder
// static t_vec3	normal_for_cylinder(t_vec3 intersection_point, t_objs obj)
// {
// 	t_vec3	vector;
// 	t_vec3	center_point;
// 	t_vec3	projection;

// 	vector = normalize(obj.vector);
// 	center_point = minus(intersection_point, obj.center);
// 	projection = mult_vecdub(vector, dot_product(center_point, vector));
// 	return (minus(center_point, projection));
// }

// // Get the surface normal for the correct object.
// static t_vec3	get_surface_normal(t_vec3 intersect_point, t_objs *obj)
// {
// 	t_vec3	normal;

// 	if (obj->type == E_SPHERE)
// 		normal = normalize(minus(intersect_point, obj->center));
// 	if (obj->type == E_PLANE)
// 		normal = normalize(obj->vector);
// 	if (obj->type == E_CYLINDER)
// 		normal = normalize(normal_for_cylinder(intersect_point, *obj));
// 	return (normal);
// }


// uint32_t	get_light(t_data *data, t_ray ray, t_objs *obj)
// {
// 	// (void)ray;
		
// 	data->vars.base = get_base_colour(obj, data->vars);
// 	// data->vars.result.r = data->vars.ambient.r / 255;
// 	// data->vars.result.g = data->vars.ambient.g / 255;
// 	// data->vars.result.b = data->vars.ambient.b / 255;
// 	data->vars.result.r = data->vars.ambient.r;
// 	data->vars.result.g = data->vars.ambient.g;
// 	data->vars.result.b = data->vars.ambient.b;
	
// 	int i = 0;
// 	// light init stuff
// 		data->vars.intersect_p = plus(ray.place, mult_vecdub(ray.vector, obj->obj_t));
// 		data->vars.normal = normalize(minus(data->vars.intersect_p, obj->center));
// 		// data->vars.normal = obj->normal;
// 		// get_surface_normal(data->vars.intersect_p, obj);
// 	while (i < data->light_i)
// 	{
		
// 		data->vars.curr_light = data->light[i];
// 		data->vars.light_dir = normalize(minus(data->vars.curr_light->place, data->vars.intersect_p));

// 		// combine ambient, diffuse and specular

// 		// add diffuse + clamp
// 		diffuse_light(&data->vars);
// 		// data->vars.result.r = data->vars.base.r + data->vars.diffuse.r;
// 		// data->vars.result.g = data->vars.base.g + data->vars.diffuse.g;
// 		// data->vars.result.b = data->vars.base.b + data->vars.diffuse.b;



// 		// add specular + clamp
// 		specular_light(&data->vars, ray);
// 		// printf("Light Dir: %f, %f, %f\n", data->vars.light_dir.x, data->vars.light_dir.y, data->vars.light_dir.z);
// 		// printf("Diffuse Fact: %f\n", data->vars.diff_fact);
// 		// printf("Diffuse Color: %d, %d, %d\n", data->vars.diffuse.r, data->vars.diffuse.g, data->vars.diffuse.b);
// 		// exit(0);
// 		data->vars.result.r += data->vars.diffuse.r * data->vars.base.r / 255 + data->vars.specular.r;
// 		data->vars.result.g += data->vars.diffuse.g * data->vars.base.g / 255 + data->vars.specular.g;
// 		data->vars.result.b += data->vars.diffuse.b * data->vars.base.b / 255 + data->vars.specular.b;
// 		i++;
// 	}

// 	data->vars.result.r = fmin(fmax(data->vars.result.r, data->vars.base.r), 255);
// 	data->vars.result.g = fmin(fmax(data->vars.result.g, data->vars.base.g), 255);
// 	data->vars.result.b = fmin(fmax(data->vars.result.b, data->vars.base.b), 255);
// 	// data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
// 	// data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
// 	// data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));
// 	return ft_convert_rgb(data->vars.result.r, data->vars.result.g, data->vars.result.b);
// }

/*	STEP 3. Compute a color for the closest intersection point.
 *
 *	This function uses the 'Phong reflection model' for each object.
 *	Including multiple light and creating shadows.
 *		- Initializing colour_vars.
 *		- Initializing the base colour of the object.
 *		- Initializing the result of the colour with ambient light contribution.
 *		  (colour = ambient * base / 255)
 *		- Goes through all the different light 
 *		  and does the shadow_calculation on each object for each light.
 *		- Clamp final values to [0, 255]. 
 *		  This ensurs that the value is not less than 0 and not bigger than 255. 
 *		  So basiclly controls the overflow/underflow of RGB colour range.
 */
// uint32_t	get_ambient(t_data *data, t_objs *obj)
// {
// 	// ambient
// 	data->vars.base = get_base_colour(obj, data->vars);
	

// 	// // final ambient
// 	data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
// 	data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
// 	data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));
// 	return ft_convert_rgb(data->vars.result.r, data->vars.result.g, data->vars.result.b);
// }

// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------


// t_colour get_sphere_colour(t_data *data, t_hit_data *obj_data, t_ray ray, t_objs *sphere)
uint32_t	get_light(t_data *data, t_ray ray, t_objs *obj)
{
    t_colour result;
	t_light	*curr_light = data->light[0]; 

    double AMBIENT_INTENSITY = data->ambient.ratio; // (0.2)
    double DIFFUSE_INTENSITY = curr_light->ratio;   // (0.6)
    double SPECULAR_INTENSITY = 0.2;
    double SPECULAR_POWER = 32;
    
    // Using the 'Phong reflection model'
	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));
	t_vec3	normal = normalize(minus(intersection_point, obj->center));

	// Ambient light contribution
	double ambient_red = AMBIENT_INTENSITY * data->ambient.colour.r;
	double ambient_green = AMBIENT_INTENSITY * data->ambient.colour.g;
	double ambient_blue = AMBIENT_INTENSITY * data->ambient.colour.b;

	// Diffuse light contribution
	t_vec3 light_direction = normalize(minus(curr_light->place, intersection_point));
	double diffuse_factor = dot_product(normal, light_direction);
	if (diffuse_factor < 0.0)
		diffuse_factor = 0.0;
	double diffuse_red = DIFFUSE_INTENSITY * diffuse_factor * curr_light->colour.r;
	double diffuse_green = DIFFUSE_INTENSITY * diffuse_factor * curr_light->colour.g;
	double diffuse_blue = DIFFUSE_INTENSITY * diffuse_factor * curr_light->colour.b;
	
	// Specular light contribution
	t_vec3 view_direction = normalize(minus(ray.place, intersection_point));
	t_vec3 reflection_direction = normalize(ft_reflect(light_direction, normal));
	double specular_factor = pow(dot_product(reflection_direction, view_direction), SPECULAR_POWER);
	if (specular_factor < 0.0)
		specular_factor = 0.0;
	double specular_red = SPECULAR_INTENSITY * specular_factor * data->ambient.colour.r;
	double specular_green= SPECULAR_INTENSITY * specular_factor * data->ambient.colour.g;
	double specular_blue = SPECULAR_INTENSITY * specular_factor * data->ambient.colour.b;

	// Combine ambient, diffuse, and specular contributions
	double final_red = ambient_red + diffuse_red + specular_red;
	double final_green = ambient_green + diffuse_green + specular_green;
	double final_blue = ambient_blue + diffuse_blue + specular_blue;
	
	// Clamp final values to [0, 255]
	final_red = fmin(fmax(final_red, obj->colour.r), 255);
	final_green = fmin(fmax(final_green, obj->colour.g), 255);
	final_blue = fmin(fmax(final_blue, obj->colour.b), 255);

	result.r = final_red;
	result.g = final_green;
	result.b = final_blue;

	return result;	
	
	
}