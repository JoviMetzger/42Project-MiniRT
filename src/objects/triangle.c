/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triangle.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 18:00:14 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/01 19:06:36 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	intersect_triangle(t_ray *ray, t_objs *tri, t_hit_data *hit)
{
	float	dir;

	tri->edge[0] = minus(tri->point[1], tri->point[0]);
	tri->edge[1] = minus(tri->point[2], tri->point[0]);
	hit->hit_pos = cross_product(ray->vector, tri->edge[1]);
	dir = dot_product(tri->edge[0], hit->hit_pos);
	if (dir > -EPSILON && dir < EPSILON)
		return (false);
	hit->a = 1.0 / dir;
	hit->o_c = minus(ray->place, tri->point[0]);
	hit->b = dot_product(hit->o_c, hit->hit_pos);
	hit->b = hit->a * hit->b;
	if (hit->b < 0.0 || hit->b > 1.0)
		return (false);
	hit->c_c = cross_product(hit->o_c, tri->edge[0]);
	hit->c = dot_product(ray->vector, hit->c_c);
	hit->c = hit->a * hit->c;
	if (hit->c < 0.0 || hit->b + hit->c > 1.0)
		return (false);
	hit->t = dot_product(tri->edge[1], hit->c_c);
	hit->t = hit->a * hit->t;
	if (hit->t < EPSILON)
		return (false);
	return (check_closest(hit));
}
