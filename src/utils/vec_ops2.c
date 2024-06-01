/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_ops2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 17:10:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/01 15:29:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Returns a new vector that has the same direction as v but with a 
// lenght (magnitude) of 1. 
// This operation effectively normalizes the vector.
// Normalized vectors are often used in calculations involving reflection 
// and refraction rays to ensure accurate results.
t_vec3	normalize_vector(t_vec3 v)
{
	t_vec3	len;
	double	normalize;

	normalize = length_squared(v);
	if (normalize == 0)
	{
		v.x = 0;
		v.y = 0;
		v.z = 0;
		return (v);
	}
	len = division_vec_dub(v, normalize);
	return (len);
}

double	distance(t_vec3 pnt1, t_vec3 pnt2)
{
	double	d;

	d = sqrt(pow(pnt2.x - pnt1.x, 2) + pow(pnt2.y - pnt1.y, 2)
			+ pow(pnt2.z - pnt1.z, 2));
	return (d);
}

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

t_vec3	init_vec(t_vec3 vec, t_vec3 v1, t_vec3 v2)
{
	vec.x = 0;
	vec.y = 0;
	vec.z = 0;
	vec = minus(v2, v1);
	vec = normalize_vector(vec);
	return (vec);
}
