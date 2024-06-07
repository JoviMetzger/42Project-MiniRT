/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_colour.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 15:45:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/07 17:24:13 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/*	Initializing the t_colour_vars struct.
 *		- Using the 'Phong reflection model'
 *			- Using the surface normal for the right object. 
 *		- Calculate ambient light contribution. (am_ratio * am_colour)
 *		- Initialize result color with ambient light contribution.
 */
static t_colour_vars	init_colour_struct(t_data *data, t_obj_hit *obj_hit,
				t_ray ray, t_objs *obj)
{
	t_colour_vars	colour;

	colour.ambient_ratio = data->ambient.ratio;
	colour.spec_intensity = 0.2;
	colour.spec_power = 32;
	colour.intersect_p = plus(ray.place, mult_vecdub(ray.vector, obj_hit->t));
	colour.normal = get_surface_normal(colour.intersect_p, obj);
	colour.ambient.r = colour.ambient_ratio * data->ambient.colour.r;
	colour.ambient.g = colour.ambient_ratio * data->ambient.colour.g;
	colour.ambient.b = colour.ambient_ratio * data->ambient.colour.b;
	colour.result.r = colour.ambient.r;
	colour.result.g = colour.ambient.g;
	colour.result.b = colour.ambient.b;
	return (colour);
}

// Calculation of the diffuse light
void	diffuse_light(t_colour_vars *colour)
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
void	specular_light(t_colour_vars *colour, t_ray ray)
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
static void	shadow_calculation(t_data *data, t_colour_vars *colour,
		t_ray ray, t_obj_hit *obj_hit)
{
	t_ray	shadow_ray;
	bool	in_shadow;
	int		i;

	colour->light_dir = normalize(minus(colour->curr_light->place,
				colour->intersect_p));
	shadow_ray.place = plus(colour->intersect_p, mult_vecdub(colour->normal,
				EPSILON));
	shadow_ray.vector = colour->light_dir;
	in_shadow = false;
	i = -1;
	while (++i < data->objs_i)
	{
		if (intersect_sphere(&shadow_ray, data->objs[i], obj_hit)
			|| intersect_plane(&shadow_ray, data->objs[i], obj_hit)
			|| intersect_cylinder(&shadow_ray, data->objs[i], obj_hit))
		{
			in_shadow = true;
			break ;
		}
	}
	if (!in_shadow)
	{
		add_light(colour, ray);
	}
}

/*	STEP 3. Compute a color for the closest intersection point.
 *
 *	This function uses the 'Phong reflection model' for each object.
 *	Including multiple lights and creating shadows.
 *		- Initializing colour_vars.
 *		- Initializing the base colour of the object.
 *		- Initializing the result of the colour with ambient light contribution.
 *		  (colour = ambient * base / 255)
 *		- Goes through all the different lights 
 *		  and does the shadow_calculation on each object for each light.
 *		- Clamp final values to [0, 255]. 
 *		  This ensurs that the value is not less than 0 and not bigger than 255. 
 *		  So basiclly controls the overflow/underflow of RGB colour range.
 */
t_colour	get_colour(t_data *data, t_obj_hit *obj_hit, t_ray ray, t_objs *obj)
{
	t_colour_vars	colour;
	int				j;

	j = -1;
	colour = init_colour_struct(data, obj_hit, ray, obj);
	colour.base = get_base_colour(obj, colour);
	colour.result.r = colour.ambient.r * colour.base.r / 255;
	colour.result.g = colour.ambient.g * colour.base.g / 255;
	colour.result.b = colour.ambient.b * colour.base.b / 255;
	while (++j < data->lights_i)
	{
		colour.curr_light = data->lightS[j];
		shadow_calculation(data, &colour, ray, obj_hit);
	}
	colour.result.r = fmin(255, fmax(0, colour.result.r));
	colour.result.g = fmin(255, fmax(0, colour.result.g));
	colour.result.b = fmin(255, fmax(0, colour.result.b));
	return (colour.result);
}
