/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_colour.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 15:11:36 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/20 21:07:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

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

static void	loop_light_array(t_data *data, t_colour_vars *vars, t_objs *obj, t_ray ray)
{
	t_colour	tmp_save;

	data->tmp_i = 0;
	while (data->tmp_i < data->light_i)
	{
		data->vars.intersect_p = plus(data->ray.place,
				mult_vecdub(data->ray.vector, obj->obj_t));
		data->vars.normal = obj->normal;
		vars->curr_light = data->light[data->tmp_i];
		vars->light_dir = normalize(minus(vars->curr_light->place,
					vars->intersect_p));
		diffuse_light(vars);
		vars->result.r += vars->diffuse.r;
		vars->result.g += vars->diffuse.g;
		vars->result.b += vars->diffuse.b;
		specular_light(&data->vars, ray);
		vars->result.r += vars->specular.r;
		vars->result.g += vars->specular.g;
		vars->result.b += vars->specular.b;
		if (data->tmp_i == 0)
			tmp_save = vars->result;
		else
		{
			vars->result = add_tmp(tmp_save, vars->result);
			tmp_save = vars->result;
		}
		data->tmp_i++;
	}
}

uint32_t	get_light(t_data *data, t_ray ray, t_objs *obj)
{
	loop_light_array(data, &data->vars, obj, ray);
	data->vars.result.r += data->vars.result.r / 255;
	data->vars.result.g += data->vars.result.g / 255;
	data->vars.result.b += data->vars.result.b / 255;
	data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
	data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
	data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));
	return (ft_convert_rgb(data->vars.result.r,
			data->vars.result.g, data->vars.result.b));
}

uint32_t	get_ambient(t_data *data, t_objs *obj)
{
	data->vars.base = get_base_colour(obj, &data->vars);
	data->vars.result.r = data->vars.ambient.r * data->vars.base.r / 255;
	data->vars.result.g = data->vars.ambient.g * data->vars.base.g / 255;
	data->vars.result.b = data->vars.ambient.b * data->vars.base.b / 255;
	data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
	data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
	data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));
	return (ft_convert_rgb(data->vars.result.r,
			data->vars.result.g, data->vars.result.b));
}
