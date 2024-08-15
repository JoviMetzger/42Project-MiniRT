/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operators.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/15 14:00:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// -------------- Operators (+-) --------------
// + operator (vec + vec)
t_vec3	plus(t_vec3 u, t_vec3 v)
{
	t_vec3	len;

	len.x = u.x + v.x;
	len.y = u.y + v.y;
	len.z = u.z + v.z;
	return (len);
}

// - operator (vec - vec)
t_vec3	minus(t_vec3 u, t_vec3 v)
{
	t_vec3	len;

	len.x = u.x - v.x;
	len.y = u.y - v.y;
	len.z = u.z - v.z;
	return (len);
}

// -------------- Operators (*/) --------------
// * operator (vec * double)
t_vec3	mult_vecdub(t_vec3 v, double dub)
{
	t_vec3	len;

	len.x = v.x * dub;
	len.y = v.y * dub;
	len.z = v.z * dub;
	return (len);
}

// / operator (vec / double)
t_vec3	division_vecdub(t_vec3 v, double dub)
{
	t_vec3	len;

	len.x = v.x / dub;
	len.y = v.y / dub;
	len.z = v.z / dub;
	return (len);
}

// -------------- Other math functions --------------
bool	check_closest(t_hit_data *hit)
{
	if (hit->t < hit->closest_t)
	{
		hit->closest_t = hit->t;
		return (true);
	}
	return (false);
}
