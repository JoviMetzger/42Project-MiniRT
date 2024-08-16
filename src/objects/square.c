/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   square.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 21:20:04 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/16 21:56:27 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	intersect_square(t_ray *ray, t_objs *squ, t_hit_data *hit)
{
	float	denom;
	float	u;
	float	v;
	t_vec3	p_to_o;
	t_vec3	int_to_p0;

	denom = dot_product(squ->vector, ray->vector);
	if (denom == 0.0f)
		return (false);
	p_to_o = minus(ray->place, squ->center);
	hit->t = dot_product(p_to_o, squ->vector) / denom;
	if (hit->t < 0.0f)
		return (false);
	squ->hit_pos = plus(ray->place, mult_vecdub(ray->vector, hit->t));
	int_to_p0 = minus(squ->hit_pos, squ->center);
	u = dot_product(int_to_p0, squ->edge[0]) / dot_product(squ->edge[0], squ->edge[0]);	
	v = dot_product(int_to_p0, squ->edge[1]) / dot_product(squ->edge[1], squ->edge[1]);	
	if (u >= -squ->edge_length && u <= squ->edge_length && v >= -squ->edge_length && v <= squ->edge_length)
		return (true);
	return (false);
	
}

bool	square(t_ray *ray, t_objs *square, t_hit_data *hit)
{
	if (intersect_square(ray, square, hit))
		return (check_closest(hit));
	return (false);
}
