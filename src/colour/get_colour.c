/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_colour.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 15:45:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/08 13:11:34 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Specular light contribution
static void	specular_light(t_data *data, t_colour_vars *vars, t_ray *ray)
{
	t_vec3	view_dir_tmp;
	t_vec3	reflect_tmp;
	double	reflect_dir_tmp;

	view_dir_tmp = minus(ray->place, vars->inter_point);
	vars->view_dir = normalize_vector(view_dir_tmp);
	reflect_tmp = ft_reflect(vars->light_dir, vars->normal);
	vars->reflection_dir = normalize_vector(reflect_tmp);
	reflect_dir_tmp = dot_product(vars->reflection_dir, vars->view_dir);
	vars->spec_factor = pow(reflect_dir_tmp, vars->spec_power);
	if (vars->spec_factor < 0.0)
		vars->spec_factor = 0.0;
	vars->spec_red = vars->spec_intensity * vars->spec_factor
		* data->ambient.colour.r;
	vars->spec_green = vars->spec_intensity * vars->spec_factor
		* data->ambient.colour.g;
	vars->spec_blue = vars->spec_intensity * vars->spec_factor
		* data->ambient.colour.b;
}

// Diffuse light contribution	
static void	diffuse_light(t_data *data, t_colour_vars *vars)
{
	t_vec3	light_vec;

	light_vec = minus(data->light.place, vars->inter_point);
	vars->light_dir = normalize_vector(light_vec);
	vars->diffuse_factor = dot_product(vars->normal, vars->light_dir);
	if (vars->diffuse_factor < 0.0)
		vars->diffuse_factor = 0.0;
	vars->diffuse_red = vars->diffuse_intensity
		* vars->diffuse_factor * data->light.colour.r;
	vars->diffuse_green = vars->diffuse_intensity
		* vars->diffuse_factor * data->light.colour.g;
	vars->diffuse_blue = vars->diffuse_intensity
		* vars->diffuse_factor * data->light.colour.b;
}

static void	light_funcs(t_data *data, t_colour_vars *vars, t_ray *ray)
{
	diffuse_light(data, vars);
	specular_light(data, vars, ray);
}

static void	combine_colour(t_data *data, t_objs *obj_i)
{
	data->vars.final_red = data->vars.ambient_red
		+ data->vars.diffuse_red;
	data->vars.final_red += data->vars.spec_red;
	data->vars.final_green = data->vars.ambient_green
		+ data->vars.diffuse_green;
	data->vars.final_green += data->vars.spec_green;
	data->vars.final_blue = data->vars.ambient_blue
		+ data->vars.diffuse_blue;
	data->vars.final_blue += data->vars.spec_blue;
	data->vars.final_red
		= fmin(fmax(data->vars.final_red, obj_i->colour.r), 255);
	data->vars.final_green
		= fmin(fmax(data->vars.final_green, obj_i->colour.g), 255);
	data->vars.final_blue
		= fmin(fmax(data->vars.final_blue, obj_i->colour.b), 255);
}

// Using the 'Phong reflection model'
// Combine ambient, diffuse, and sp contributions
t_colour	get_colour(t_data *data, t_hit_data *hit, t_ray ray, t_objs *obj_i)
{
	t_colour		result;

	data->vars.inter_point = plus(ray.place, mult_vecdub(ray.vector, hit->t));
	data->vars.normal = obj_i->normal;
	light_funcs(data, &data->vars, &ray);
	combine_colour(data, obj_i);
	result.r = data->vars.final_red;
	result.g = data->vars.final_green;
	result.b = data->vars.final_blue;
	return (result);
}
