/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_colour_mess.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/15 17:34:09 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/16 15:38:22 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

t_colour get_colour_test(t_data *data, t_hit_data *obj_data, t_ray ray, t_objs *obj)
{

///////////////////////////////////////////////
	ft_bzero(&data->vars, sizeof(t_colour_vars));
	data->vars.ambient_ratio = data->ambient.ratio;
	data->vars.spec_intensity = 0.2;
	data->vars.spec_power = 32;
	data->vars.ambient.r = data->vars.ambient_ratio * data->ambient.colour.r;
	data->vars.ambient.g = data->vars.ambient_ratio * data->ambient.colour.g;
	data->vars.ambient.b = data->vars.ambient_ratio * data->ambient.colour.b;
	data->vars.result.r = data->vars.ambient.r;
	data->vars.result.g = data->vars.ambient.g;
	data->vars.result.b = data->vars.ambient.b;
///////////////////////////////////////////////

	// data->vars.diffuse_intense = data->light[0]->ratio;
	
	data->vars.intersect_p = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));
	data->vars.light_dir = normalize(minus(data->light[0]->place, data->vars.intersect_p));
	data->vars.normal = obj->normal;

	if (obj->what_pattern == 1 && obj->type == E_SPHERE)
		data->vars.base = get_sphere_checkerboard(obj->normal);
	else
	{
		data->vars.base.r = data->vars.ambient.r * data->ambient.colour.r + obj->colour.r;
		data->vars.base.g = data->vars.ambient.g * data->ambient.colour.g + obj->colour.g;
		data->vars.base.b = data->vars.ambient.b * data->ambient.colour.b + obj->colour.b;
	}

///////////////////////////////////////////////

	data->vars.diff_fact = dot_product(data->vars.normal, data->vars.light_dir);
	if (data->vars.diff_fact < 0.0)
		data->vars.diff_fact = 0.0;
	double diffuse_red = data->vars.diffuse_intense * data->vars.diff_fact * data->light[0]->colour.r;
	double diffuse_green = data->vars.diffuse_intense * data->vars.diff_fact * data->light[0]->colour.g;
	double diffuse_blue = data->vars.diffuse_intense * data->vars.diff_fact * data->light[0]->colour.b;
	
	// Specular light contribution

	data->vars.view_dir = normalize(minus(ray.place, data->vars.intersect_p));
	data->vars.ref_dir = normalize(ft_reflect(data->vars.light_dir, data->vars.normal));
	data->vars.spec_fact = pow(dot_product(data->vars.ref_dir, data->vars.view_dir), data->vars.spec_power);
	if (data->vars.spec_fact < 0.0)
		data->vars.spec_fact = 0.0;
	double specular_red = data->vars.spec_intensity * data->vars.spec_fact * data->light[0]->colour.r;
	double specular_green = data->vars.spec_intensity * data->vars.spec_fact * data->light[0]->colour.g;
	double specular_blue = data->vars.spec_intensity * data->vars.spec_fact * data->light[0]->colour.b;

//////////////////////////////////////////////////////////

	// Combine ambient, diffuse, and specular contributions
	double final_red = data->vars.base.r + diffuse_red;
	double final_green = data->vars.base.g + diffuse_green;
	double final_blue = data->vars.base.b + diffuse_blue;
	
	// Clamp final values to [0, 255]
	final_red = fmin(fmax(final_red, obj->colour.r), 255);
	final_green = fmin(fmax(final_green, obj->colour.g), 255);
	final_blue = fmin(fmax(final_blue, obj->colour.b), 255);
	
	final_red += final_red / 255 + specular_red;
	final_green += final_green / 255 + specular_green;
	final_blue += final_blue / 255 + specular_blue;


	data->vars.result.r = fmin(255, fmax(0, final_red));
	data->vars.result.g = fmin(255, fmax(0, final_green));
	data->vars.result.b = fmin(255, fmax(0, final_blue));
	
	return data->vars.result;	
	
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
