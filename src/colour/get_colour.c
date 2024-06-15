/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_colour.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/15 17:34:09 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/15 22:29:38 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

t_colour get_colour_test(t_data *data, t_hit_data *obj_data, t_ray ray, t_objs *cylinder)
{
    t_colour result;
	
    double AMBIENT_INTENSITY = data->ambient.ratio; // (0.2)
    double DIFFUSE_INTENSITY = data->light[0]->ratio;   // (0.6)
    double SPECULAR_INTENSITY = 0.2;
    double SPECULAR_POWER = 32;
    
    // Using the 'Phong reflection model'
	t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));
	// t_vec3	normal = normalize(minus(intersection_point, cylinder->center));
	t_vec3	normal = cylinder->normal;

	// Ambient light contribution
	// double ambient_red = AMBIENT_INTENSITY * data->ambient.colour.r;
	// double ambient_green = AMBIENT_INTENSITY * data->ambient.colour.g;
	// double ambient_blue = AMBIENT_INTENSITY * data->ambient.colour.b;
	t_colour	base;

	if (cylinder->what_pattern == 1 && cylinder->type == E_SPHERE)
		base = get_sphere_checkerboard(cylinder->normal);
	else
	{
		// base = cylinder->colour;
		base.r = AMBIENT_INTENSITY * data->ambient.colour.r + cylinder->colour.r;
		base.g = AMBIENT_INTENSITY * data->ambient.colour.g + cylinder->colour.g;
		base.b = AMBIENT_INTENSITY * data->ambient.colour.b + cylinder->colour.b;
	}

	// Diffuse light contribution
	t_vec3 light_direction = normalize(minus(data->light[0]->place, intersection_point));
	double diffuse_factor = dot_product(normal, light_direction);
	if (diffuse_factor < 0.0)
		diffuse_factor = 0.0;
	double diffuse_red = DIFFUSE_INTENSITY * diffuse_factor * data->light[0]->colour.r;
	double diffuse_green = DIFFUSE_INTENSITY * diffuse_factor * data->light[0]->colour.g;
	double diffuse_blue = DIFFUSE_INTENSITY * diffuse_factor * data->light[0]->colour.b;
	
	// Specular light contribution
	t_vec3 view_direction = normalize(minus(ray.place, intersection_point));
	t_vec3 reflection_direction = normalize(ft_reflect(light_direction, normal));
	double specular_factor = pow(dot_product(reflection_direction, view_direction), SPECULAR_POWER);
	if (specular_factor < 0.0)
		specular_factor = 0.0;
	double specular_red = SPECULAR_INTENSITY * specular_factor * data->light[0]->colour.r;
	double specular_green= SPECULAR_INTENSITY * specular_factor * data->light[0]->colour.g;
	double specular_blue = SPECULAR_INTENSITY * specular_factor * data->light[0]->colour.b;

	// Combine ambient, diffuse, and specular contributions
	double final_red = base.r + diffuse_red;
	double final_green = base.g + diffuse_green;
	double final_blue = base.b + diffuse_blue;
	
	// Clamp final values to [0, 255]
	// final_red = fmin(fmax(final_red, cylinder->colour.r), 255);
	// final_green = fmin(fmax(final_green, cylinder->colour.g), 255);
	// final_blue = fmin(fmax(final_blue, cylinder->colour.b), 255);
	final_red += final_red / 255 + specular_red;
	final_green += final_green / 255 + specular_green;
	final_blue += final_blue / 255 + specular_blue;


	result.r = fmin(255, fmax(0, final_red));
	result.g = fmin(255, fmax(0, final_green));
	result.b = fmin(255, fmax(0, final_blue));
	
	return result;	
	
}

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

/*	This function add the light if no shadow (no intersection with object)	    
 *		- Calculate diffuse light contribution.
 *		- Calculate specular light contribution.
 *		- Accumulate light contributions. 
 *		  (newColour += diffuse_colour * base_colour / 255 + specular_colour)
 */
void	add_light(t_colour_vars *colour, t_ray ray)
{
	t_ray	shadow_ray;


	colour->light_dir = normalize(minus(colour->curr_light->place,
				colour->intersect_p));
	shadow_ray.place = plus(colour->intersect_p, mult_vecdub(colour->normal,
				EPSILON));
	shadow_ray.vector = colour->light_dir;

	diffuse_light(colour);
	specular_light(colour, ray);
	colour->result.r += colour->diffuse.r * colour->base.r / 255
		+ colour->specular.r;
	colour->result.g += colour->diffuse.g * colour->base.g / 255
		+ colour->specular.g;
	colour->result.b += colour->diffuse.b * colour->base.b / 255
		+ colour->specular.b;
}

/*	STEP 3. Compute a color for the closest intersection point.
 *
 *	This function uses the 'Phong reflection model' for each object.
 *	Including multiple light and creating shadows.
 *		- Initializing data->vars variables.
 *		- Initializing the base colour of the object.
 *		- Initializing the result of the colour with ambient light contribution.
 *		  (colour = ambient * base / 255)
 *		- Creating a light_direction.
 *		- Clamp final values to [0, 255]. 
 *		  This ensurs that the value is not less than 0 and not bigger than 255. 
 *		  So basiclly controls the overflow/underflow of RGB colour range.
 */
t_colour	get_colour(t_data *data, t_ray ray, t_hit_data *obj_hit, t_objs *obj)
{
	data->vars.intersect_p = plus(ray.place, mult_vecdub(ray.vector, obj_hit->t));
	data->vars.normal = obj->normal;
	data->vars.base = get_base_colour(obj, &data->vars);
	data->vars.result.r = data->vars.ambient.r * data->vars.base.r / 255;
	data->vars.result.g = data->vars.ambient.g * data->vars.base.g / 255;
	data->vars.result.b = data->vars.ambient.b * data->vars.base.b / 255;
	
	data->vars.curr_light = data->light[0];
	add_light(&data->vars, ray);
	// data->vars.light_dir = normalize(minus(data->vars.curr_light->place,
	// 	data->vars.intersect_p));
	// add_light(&data->vars, ray);

	data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
	data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
	data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));
	return (data->vars.result);
}
