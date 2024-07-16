/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operators1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/16 15:42:51 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// -------------- Operators (*/) --------------
// * operator (vec * vec)
t_vec3	mult_vecvec(t_vec3 u, t_vec3 v)
{
	t_vec3	len;

	len.x = u.x * v.x;
	len.y = u.y * v.y;
	len.z = u.z * v.z;
	return (len);
}

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
t_vec3	division_vec_dub(t_vec3 v, double dub)
{
	t_vec3	len;

	len.x = v.x / dub;
	len.y = v.y / dub;
	len.z = v.z / dub;
	return (len);
}

// / operator (vec / vec)
t_vec3	division_vec_vec(t_vec3 u, t_vec3 v)
{
	t_vec3	len;

	len.x = u.x / v.x;
	len.y = u.y / v.y;
	len.z = u.z / v.z;
	return (len);
}
