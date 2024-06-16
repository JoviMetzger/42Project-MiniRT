/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_colour.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 15:11:36 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/16 17:44:48 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

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

uint32_t	get_light(t_data *data, t_ray ray, t_objs *obj)
{
	// light init stuff 

//
// this stuff for light array looping... (data->light[], will have correct light)

	data->vars.curr_light = data->light[0];
	data->vars.intersect_p = plus(data->ray.place, mult_vecdub(data->ray.vector, obj->obj_t));
	data->vars.light_dir = normalize(minus(data->vars.curr_light->place,
		data->vars.intersect_p));
//
	data->vars.normal = obj->normal;

	// combine ambient, diffuse and specular

	// add diffuse + clamp
	diffuse_light(&data->vars);
	data->vars.result.r = data->vars.base.r + data->vars.diffuse.r;
	data->vars.result.g = data->vars.base.g + data->vars.diffuse.g;
	data->vars.result.b = data->vars.base.b + data->vars.diffuse.b;

	data->vars.result.r = fmin(fmax(data->vars.result.r, obj->colour.r), 255);
	data->vars.result.g = fmin(fmax(data->vars.result.g, obj->colour.g), 255);
	data->vars.result.b = fmin(fmax(data->vars.result.b, obj->colour.b), 255);


	// add specular + clamp
	specular_light(&data->vars, ray);
	data->vars.result.r += data->vars.result.r / 255 + data->vars.specular.r;
	data->vars.result.g += data->vars.result.g / 255 + data->vars.specular.g;
	data->vars.result.b += data->vars.result.b / 255 + data->vars.specular.b;

	data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
	data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
	data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));

	return ft_convert_rgb(data->vars.result.r, data->vars.result.g, data->vars.result.b);
}

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
uint32_t	get_ambient(t_data *data, t_objs *obj)
{
	// ambient
	data->vars.base = get_base_colour(obj, &data->vars);
	
	if (obj->what_pattern == 1 && obj->type == E_SPHERE)
		data->vars.base = get_sphere_checkerboard(obj->normal);
	else
	{	
		data->vars.result.r = data->vars.ambient.r * data->vars.base.r / 255;
		data->vars.result.g = data->vars.ambient.g * data->vars.base.g / 255;
		data->vars.result.b = data->vars.ambient.b * data->vars.base.b / 255;
	}

	// final ambient
	data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
	data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
	data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));
	return ft_convert_rgb(data->vars.result.r, data->vars.result.g, data->vars.result.b);
}
