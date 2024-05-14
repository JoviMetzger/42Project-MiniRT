/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_ops2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 17:10:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/14 17:15:34 by smclacke      ########   odam.nl         */
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
