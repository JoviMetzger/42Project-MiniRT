/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_calcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 16:14:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/23 17:07:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

static t_ray	init_light_ray(t_data *data, int i, int light_i)
{
	t_vec3	inter_p;
	t_vec3	light_dir;

	inter_p = mult_vecdub(data->pix[i]->og_ray.vector, data->pix[i]->hit_t);
	// light_dir = plus(data->light[light_i]->place, inter_p);
	light_dir = minus(data->light[light_i]->place, inter_p);
	data->pix[i]->light_ray.place = inter_p;
	data->pix[i]->light_ray.vector = light_dir;
	return (data->pix[i]->light_ray);
}

static bool	in_light(t_data *data, int i, int light_i)
{
    t_hit_data		hit_2;
	t_ray			ray;
	int				obj_i = 0;

	ft_bzero(&ray, sizeof(t_ray));
	ray = init_light_ray(data, i, light_i);
	while (obj_i < data->objs_i)
	{
		data->objs[obj_i]->in_light = true;
		ft_bzero(&hit_2, sizeof(t_hit_data));
		if ((does_intersect(&ray, data->objs[obj_i], &hit_2) == true)
			&& data->objs[obj_i] != data->pix[i]->obj)
			{
				data->pix[i]->in_light = false;
				// break ;
			}
		obj_i++;
	}
	// obj_i = 0;
	// while (obj_i < data->objs_i)
	// {
	// 	if (data->objs[obj_i]->in_light == true)
	// 	{
	// 		data->pix[i]->in_light = true;
	// 		break ;
	// 	}
	// 	obj_i++;
	// }
	if (data->pix[i]->in_light == true)
		return (true);
	return (false);
}

static void	initial_cals(t_data *data)
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
}

void	do_calcs(t_data *data)
{
	int	light_i = 0; // use later for loopin multi lights
	
	initial_cals(data);
	data->i = 0;
	while (data->i < data->total_pix)
	{
		if (data->pix[data->i]->hit_b == true)
		{
			data->pix[data->i]->in_light = true;
			if (in_light(data, data->i, light_i) == true)
				data->pix[data->i]->colour = data->pix[data->i]->light;
			else
				data->pix[data->i]->colour = data->pix[data->i]->ambient;
		}
		data->i++;
	}
}


// could use later for when handling many lights

// void	do_calcs(t_data *data)
// {
// 	bool	light_bool = false;
// 	initial_cals(data);
// 	data->i = 0;
// 	while (data->i < data->total_pix)
// 	{
// 		if (data->pix[data->i]->hit_b == true)
// 		{
// 			data->pix[data->i]->in_light = true;
// 			int	light_i = 0;
// 			while (light_i < data->light_i)
// 			{
// 				if (in_light(data, data->i, light_i))
// 					data->light[light_i]->in_light = true;
// 				else
// 					data->light[light_i]->in_light = false;
// 				light_i++;
// 			}
// 			light_i = 0;
// 			while (light_i < data->light_i)
// 			{
// 				if (data->light[light_i]->in_light == true)
// 				{
// 					light_bool = true;
// 					break ;
// 				}
// 				light_i++;
// 			}
// 			if (light_bool == true)
// 			if (data->light[0]->in_light == true)
// 				data->pix[data->i]->colour = data->pix[data->i]->light;
// 			else
// 			{
// 				puts("ambient");
// 				data->pix[data->i]->colour = data->pix[data->i]->ambient;
// 			}
// 		}
// 		data->i++;
// 	}
// }

// possibly want this too but older and shiter than above

// bool	do_loops(t_data *data)
// {
// 	int	light_i;
// 	int	obj_i;

// 	light_i = 0;
// 	obj_i = 0;
// 	while (light_i < data->light_i)
// 	{
// 		obj_i = 0;
// 		while (obj_i < data->objs_i)
// 		{
// 			if (data->objs[obj_i]->in_light == true)
// 				obj_i++;
// 		}

// 		if (data->light[light_i]->in_light == true)
// 			return (true);
// 		light_i++;
// 	}
// 	return (false);
// }

