/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operators.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/16 19:03:35 by jmetzger      ########   odam.nl         */
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

// + operator (vec + dub)
t_vec3	plus_vecdub(t_vec3 u, double v)
{
	t_vec3	len;

	len.x = u.x + v;
	len.y = u.y + v;
	len.z = u.z + v;
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

// -------------- Other math functions --------------
double	pythagoras(double a, double b)
{
	return (sqrt(a * a + b * b));
}

double	vec_length(t_vec3 v1, t_vec3 v2)
{
	double	result;

	result = pythagoras(v1.x - v2.x, v1.y - v2.y);
	return (pythagoras(result, v1.z - v2.z));
}