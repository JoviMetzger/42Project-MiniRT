/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operators.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/06 16:41:44 by jmetzger      ########   odam.nl         */
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
