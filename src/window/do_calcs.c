/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_calcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 16:14:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/16 20:54:52 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// static t_ray	init_lights(t_data *data, t_ray	light_ray, t_objs *obj, int index)
// {
// 	ft_bzero(&light_ray, sizeof(t_ray));
// 	data->vars.curr_light = data->light[index];
// 	data->vars.intersect_p = plus(data->ray.place, mult_vecdub(data->ray.vector, obj->obj_t));
// 	data->vars.light_dir = normalize(minus(data->vars.curr_light->place,
// 		data->vars.intersect_p));
// 	data->vars.normal = obj->normal;
// 	// light_ray.place = data->light[index]->place;
// 	light_ray.place = plus(data->vars.intersect_p, mult_vecdub(data->vars.normal, EPSILON));
// 	light_ray.vector = data->vars.light_dir;
// 	return (light_ray);
// }

// static void	init_light(t_data *data, t_objs *obj, double hit)
// {
// 	data->vars.curr_light = data->light[0]; // !!!!!!
// 	data->vars.intersect_p = plus(data->ray.place, mult_vecdub(data->ray.vector, hit));
// 	data->vars.light_dir = normalize(minus(data->vars.curr_light->place,
// 		data->vars.intersect_p));
// 	data->vars.normal = obj->normal;
// }

void	do_calcs(t_data *data)
{
	t_hit_data	hit;
	int			i = 0;

	// t_ray		light_ray;
	// light_ray = init_lights(data, light_ray, data->pix[i]->obj, index);

	// int			index = 0;

	while (i < data->total_pix)
	{
		data->ray = ft_create_ray(data, data->pix[i]->x, data->pix[i]->y);
		ft_calculate_colour(data, &hit, i);
		data->mouse.mou_y = data->pix[i]->y;
		data->mouse.mou_x = data->pix[i]->x;
		data->pix[i]->hit_t = hit.t;
		i++;
	}
	i = 0;
	while (i < data->total_pix)
	{
		if (data->pix[i]->hit_b == true)
		{
			data->pix[i]->colour = data->pix[i]->ambient;
			// while (index < data->light_i)
			// {
				// if light[index] [DIRECTLY] intersects object, overwrite colour with light
					data->pix[i]->colour = data->pix[i]->light;
			// 	index++;
			// }
		}
		i++;
	}
}
