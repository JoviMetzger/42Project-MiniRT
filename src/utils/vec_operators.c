/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_operators.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/14 17:12:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// -------------- Operators (+-*/) --------------
// + operator
t_vec3	plus(t_vec3 u, t_vec3 v)
{
	t_vec3	len;

	len.x = u.x + v.x;
	len.y = u.y + v.y;
	len.z = u.z + v.z;
	return (len);
}

t_vec3	plus_vecdub(t_vec3 u, double v)
{
	t_vec3	len;

	len.x = u.x + v;
	len.y = u.y + v;
	len.z = u.z + v;
	return (len);
}

// - operator
t_vec3	minus(t_vec3 u, t_vec3 v)
{
	t_vec3	len;

	len.x = u.x - v.x;
	len.y = u.y - v.y;
	len.z = u.z - v.z;
	return (len);
}

// * operator -> between two vectors (vec * vec)
t_vec3	mult_vecvec(t_vec3 u, t_vec3 v)
{
	t_vec3	len;

	len.x = u.x * v.x;
	len.y = u.y * v.y;
	len.z = u.z * v.z;
	return (len);
}

// * operator -> between vector and double (vec * double)
// MIGHT NOT NEED -> don't know
t_vec3	mult_vecdub(t_vec3 v, double dub)
{
	t_vec3	len;

	len.x = v.x * dub;
	len.y = v.y * dub;
	len.z = v.z * dub;
	return (len);
}
