/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_calcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 16:14:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/09 14:55:48 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

static t_ray	init_light_ray(t_data *data, int i)
{
	// t_vec3  inter_p = plus(data->pix[i]->og_ray.place,
	// 	mult_vecdub(data->pix[i]->og_ray.vector, data->pix[i]->hit_t));
	
	t_vec3  inter_p = plus(data->light[0]->place,
		mult_vecdub(data->pix[i]->og_ray.vector, data->pix[i]->hit_t));

	// t_vec3  light_dir = normalize(minus(data->light[0]->place, inter_p));
	t_vec3  light_dir = minus(data->light[0]->place, inter_p);

	// data->pix[i]->light_ray.place = data->light[0]->place;
	data->pix[i]->light_ray.place = inter_p;
	data->pix[i]->light_ray.vector = light_dir;

	return (data->pix[i]->light_ray);
}

// static bool	inter_triangle(t_ray *ray, t_objs *tri, t_hit_data *hit)
// {
// 	float	dir;

// 	hit->hit_pos = cross_product(ray->vector, tri->edge[1]);
// 	dir = dot_product(tri->edge[0], hit->hit_pos);
// 	if (dir > -EPSILON && dir < EPSILON)
// 		return (false);
// 	hit->a = 1.0 / dir;
// 	hit->o_c = minus(ray->place, tri->point[0]);
// 	hit->b = dot_product(hit->o_c, hit->hit_pos);
// 	hit->b = hit->a * hit->b;
// 	if (hit->b < 0.0 || hit->b > 1.0)
// 		return (false);
// 	hit->c_c = cross_product(hit->o_c, tri->edge[0]);
// 	hit->c = dot_product(ray->vector, hit->c_c);
// 	hit->c = hit->a * hit->c;
// 	if (hit->c < 0.0 || hit->b + hit->c > 1.0)
// 		return (false);
// 	hit->t = dot_product(tri->edge[1], hit->c_c);
// 	hit->t = hit->a * hit->t;
// 	if (hit->t < EPSILON)
// 		return (false);
// 	tri->obj_t = hit->t;
// 	tri->hit_pos = plus(ray->place, mult_vecdub(ray->vector, tri->obj_t));
// 	return (true);
// }


static bool	inter_sphere(t_ray *ray, t_objs *sphere, t_hit_data *hit)
{
	t_vec3	inter_point;


	hit->o_c = minus(ray->place, sphere->center);
	hit->a = dot_product(ray->vector, ray->vector);
	hit->b = 2.0 * dot_product(ray->vector, hit->o_c);
	hit->c = dot_product(hit->o_c, hit->o_c) - (sphere->radius
			* sphere->radius);
	if (quadratic(hit) == true)
	{
		inter_point = plus(ray->place, mult_vecdub(ray->vector, hit->t));
		sphere->normal = normalize(minus(inter_point, sphere->center));
		sphere->obj_t = hit->t;
		return (true);
	}
	return (false);
}

// trace another ray from the intersection of the prime ray and the object back to the light. 
// If there is another object between the intersection and the light, the point is in shadow.
bool	in_light(t_data *data, t_ray *ray, int i)
{
    int				obj_i = 0;
    t_hit_data		hit_2;
	double			tmp_t;
	(void) i;


	tmp_t = data->pix[i]->hit_t;
	hit_2.closest_t = DBL_MAX;
    while (obj_i < data->objs_i)
    {
        if (inter_sphere(ray, data->objs[obj_i], &hit_2))
			// || inter_triangle(ray, data->objs[obj_i], &hit_2))
			// || intersect_cylinder(ray, data->objs[obj_i], &hit_2)
			// || intersect_plane(ray, data->objs[obj_i], &hit_2))
		{
			if (hit_2.closest_t > tmp_t)
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
		t_ray 			ray = init_light_ray(data, data->i);
		if (data->pix[data->i]->hit_b == true)
		{
			if (in_light(data, &ray, data->i))
				data->pix[data->i]->colour = data->pix[data->i]->light;
			else
				data->pix[data->i]->colour = data->pix[data->i]->ambient;
		}
		data->i++;
	}
}
