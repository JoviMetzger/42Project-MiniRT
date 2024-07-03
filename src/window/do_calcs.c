/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_calcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 16:14:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/03 17:55:44 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

static t_ray	init_light_ray(t_data *data, int i)
{
	t_vec3  inter_p = plus(data->pix[i]->og_ray.place,
		mult_vecdub(data->pix[i]->og_ray.vector, data->pix[i]->hit_t));

	t_vec3  light_dir = normalize(minus(data->light[0]->place, inter_p));

	data->pix[i]->light_ray.place = data->light[0]->place;
	data->pix[i]->light_ray.vector = light_dir;

	return (data->pix[i]->light_ray);
}

// trace another ray from the intersection of the prime ray and the object back to the light. 
// If there is another object between the intersection and the light, the point is in shadow.
bool	in_light(t_data *data, int i)
{
	t_ray 			ray = init_light_ray(data, i);
    int				obj_i = 0;
    t_hit_data		hit_2;


	hit_2.closest_t = DBL_MAX;

    while (obj_i < data->objs_i && data->objs[obj_i] != data->pix[i]->obj)
    {
        if (intersect_sphere(&ray, data->objs[obj_i], &hit_2)
			|| intersect_cylinder(&ray, data->objs[obj_i], &hit_2)
			|| intersect_triangle(&ray, data->objs[obj_i], &hit_2)
			|| intersect_plane(&ray, data->objs[obj_i], &hit_2))
		{
			// if (hit_2.closest_t > data->pix[i]->hit_t)
				return (false);
		}
        obj_i++;
    }
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
			if (in_light(data, data->i) == true)
				data->pix[data->i]->colour = data->pix[data->i]->light;
			else
				data->pix[data->i]->colour = data->pix[data->i]->ambient;
		}
		data->i++;
	}
}
