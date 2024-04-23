/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_colour.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 15:45:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/23 17:44:44 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Specular light contribution
static void	specular_light(t_data *data, t_colour_vars *vars, t_ray *ray)
{
	t_vec3	tmp;
	t_vec3	tmp2;
	double	dot_reflect;

	tmp = minus(ray->place, vars->inter_point);
	tmp2 = ft_reflect(vars->light_dir, vars->normal);
	dot_reflect = dot_product(vars->reflection_dir, vars->view_dir);
	vars->view_dir = normalize_vector(tmp);
	vars->reflection_dir = normalize_vector(tmp2);
	vars->spec_factor = pow(dot_reflect, vars->spec_power);
	if (vars->spec_factor < 0.0)
		vars->spec_factor = 0.0;
	vars->spec_red = vars->spec_power * vars->spec_factor
		* data->light.colour.r;
	vars->spec_green = vars->spec_power * vars->spec_factor
		* data->light.colour.g;
	vars->spec_blue = vars->spec_power * vars->spec_factor
		* data->light.colour.b;
}

// Diffuse light contribution	
static void	diffuse_light(t_data *data, t_colour_vars *vars)
{
	t_vec3	tmp;

	tmp = minus(data->light.place, vars->inter_point);
	vars->light_dir = normalize_vector(tmp);
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

// Ambient intensity
// Ambient light contribution
// ambeint ratio = 0.2 | light ratio = 0.6
static void	init_vars(t_data *data, t_colour_vars *vars)
{
	vars->ambient_intensity = data->ambient.ratio;
	vars->diffuse_intensity = data->light.ratio;
	vars->spec_intensity = 0.2;
	vars->spec_power = 32;
	vars->ambient_red = vars->ambient_intensity * data->ambient.colour.r;
	vars->ambient_green = vars->ambient_intensity * data->ambient.colour.g;
	vars->ambient_blue = vars->ambient_intensity * data->ambient.colour.b;
}

// Using the 'Phong reflection model'
// Combine ambient, diffuse, and sp contributions
// Clamp final values to [0, 255]
// obj - data_obj | obj_i - specific object passed
t_colour	get_colour(t_data *data, t_obj_data *obj, t_ray ray, t_objs *obj_i)
{
	t_colour		result;
	t_colour_vars	vars;

	ft_bzero(&vars, sizeof(t_colour_vars));
	init_vars(data, &vars);
	diffuse_light(data, &vars);
	specular_light(data, &vars, &ray);
	vars.inter_point = plus(ray.place, mult_vecdub(ray.vector, obj->t));
	vars.normal = normalize_vector(minus(vars.inter_point, obj_i->center));
	vars.final_red = vars.ambient_red + vars.diffuse_red;
	vars.final_red += vars.spec_red;
	vars.final_green = vars.ambient_green + vars.diffuse_green;
	vars.final_green += vars.spec_green;
	vars.final_blue = vars.ambient_blue + vars.diffuse_blue;
	vars.final_blue += vars.spec_blue;
	vars.final_red = fmin(fmax(vars.final_red, obj_i->colour.r), 255);
	vars.final_green = fmin(fmax(vars.final_green, obj_i->colour.g), 255);
	vars.final_blue = fmin(fmax(vars.final_blue, obj_i->colour.b), 255);
	result.r = vars.final_red;
	result.g = vars.final_green;
	result.b = vars.final_blue;
	return (result);
}
