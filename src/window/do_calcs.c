/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_calcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 16:14:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/11 14:13:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * @todo loop all lights, check all possible shadows..
 * @todo norming 
 */
static t_ray	init_light_ray(t_data *data, int i)
{
	t_vec3  inter_p = mult_vecdub(data->pix[i]->og_ray.vector, data->pix[i]->hit_t);
	t_vec3  light_dir = minus(data->light[0]->place, inter_p);

	data->pix[i]->light_ray.place = inter_p;
	data->pix[i]->light_ray.vector = light_dir;
	return (data->pix[i]->light_ray);
}

bool	in_light(t_data *data, t_ray *ray, int i)
{
    int				obj_i = 0;
    t_hit_data		hit_2;
	double			tmp_t;

	// for each pixel, loop light array, check if something creates shadow..
	tmp_t = data->pix[i]->hit_t;
	hit_2.closest_t = DBL_MAX;
    while (obj_i < data->objs_i)
    {
        if (intersect_sphere(ray, data->objs[obj_i], &hit_2)
			|| intersect_triangle(ray, data->objs[obj_i], &hit_2)
			|| intersect_cylinder(ray, data->objs[obj_i], &hit_2)
			|| intersect_plane(ray, data->objs[obj_i], &hit_2))
		{
			if (data->objs[obj_i] != data->pix[i]->obj)
				return (false);
		}
        obj_i++;
    }
	if (hit_2.closest_t < tmp_t)
		return (false);
	return (true);
}

void	do_calcs(t_data *data)
{
	t_hit_data	hit;

	data->i = 0;
	while (data->i < data->total_pix)
	{
		data->ray = ft_create_ray(data, data->pix[data->i]->x,
				data->pix[data->i]->y);
		data->pix[data->i]->og_ray = data->ray;
		ft_calculate_colour(data, &hit, data->i);
		data->mouse.mou_y = data->pix[data->i]->y;
		data->mouse.mou_x = data->pix[data->i]->x;
		data->pix[data->i]->hit_t = hit.t;
		data->i++;
	}
	data->i = 0;
	while (data->i < data->total_pix)
	{
		if (data->pix[data->i]->hit_b == true)
		{
			t_ray 			ray = init_light_ray(data, data->i); // move and loop light aray
			if (in_light(data, &ray, data->i))
				data->pix[data->i]->colour = data->pix[data->i]->light;
			else
				data->pix[data->i]->colour = data->pix[data->i]->ambient;
		}
		data->i++;
	}
}
