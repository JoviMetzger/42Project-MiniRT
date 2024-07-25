/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_calcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 16:14:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/25 20:24:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

static t_ray	init_light_ray(t_data *data, int i, int light_i)
{
	t_vec3	inter_p;
	t_vec3	inter_p_offset;
	t_vec3	light_dir;

	inter_p = mult_vecdub(data->pix[i]->og_ray.vector, data->pix[i]->hit_t);
	inter_p_offset = plus(inter_p,
			mult_vecdub(data->pix[i]->obj->normal, EPSILON));
	light_dir = minus(data->light[light_i]->place, inter_p_offset);
	data->pix[i]->light_ray.place = inter_p_offset;
	data->pix[i]->light_ray.vector = light_dir;
	data->pix[i]->light_ray.distance = length_squared(light_dir);
	normalize(data->pix[i]->light_ray.vector);
	return (data->pix[i]->light_ray);
}

// static bool	does_intersect(t_ray *ray, t_objs *obj, t_hit_data *hit_2)
// {
// 	if (intersect_sphere(ray, obj, hit_2))
// 	{
// 		if (hit_2->t < ray->distance)
// 			return (true);
// 	}
// 	else if (intersect_cylinder(ray, obj, hit_2))
// 	{
// 		puts("here");
// 		exit(0);
// 		if (hit_2->t < ray->distance)
// 			return (true);
// 	}
// 	// else if (intersect_sphere(ray, obj, hit_2))
// 	// {
// 	// 	if (hit_2->t < ray->distance)
// 	// 		return (true);
// 	// }
// 	// else if (intersect_sphere(ray, obj, hit_2))
// 	// {
// 	// 	if (hit_2->t < ray->distance)
// 	// 		return (true);
// 	// }
// 		// || intersect_triangle(ray, obj, hit_2)
// 		// || intersect_cylinder(ray, obj, hit_2)
// 		// || intersect_plane(ray, obj, hit_2))
// 		// {	
// 		// 	if (hit_2->t < ray->distance)
// 		// 		return (true);
// 		// }
// 	return (false);
// }

// fix this function so that the type is check, correct intersect function called... then test plane + triangle again
static bool	in_light(t_data *data, int i, int light_i)
{
	t_hit_data		hit_2;
	t_ray			ray;
	int				obj_i;

	obj_i = 0;
	ft_bzero(&ray, sizeof(t_ray));
	ray = init_light_ray(data, i, light_i);
	while (obj_i < data->objs_i)
	{
		ft_bzero(&hit_2, sizeof(t_hit_data));
		if (data->objs[obj_i] != data->pix[i]->obj)
		{
			if (data->objs[obj_i]->type == E_SPHERE
				&& intersect_sphere(&ray, data->objs[obj_i], &hit_2))
			{
				if (hit_2.t < ray.distance)
					return (false);
			}
			if (data->objs[obj_i]->type == E_CYLINDER
				&& intersect_cylinder(&ray, data->objs[obj_i], &hit_2))
			{
				if (hit_2.t < ray.distance)
					return (false);
			}
			// if (does_intersect(&ray, data->objs[obj_i], &hit_2) == true)
			// 	return (false);
		}
		obj_i++;
	}
	return (true);
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
	int	light_i;

	initial_cals(data);
	data->i = 0;
	light_i = 0;
	while (data->i < data->total_pix)
	{
		if (data->pix[data->i]->hit_b == true)
		{
			light_i = 0;
			while (light_i < data->light_i)
			{
				if (in_light(data, data->i, light_i) == true)
				{
					data->pix[data->i]->colour = data->pix[data->i]->light;
					break ;
				}
				else
					data->pix[data->i]->colour = data->pix[data->i]->ambient;
				light_i++;
			}
		}
		data->i++;
	}
}
