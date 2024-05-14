/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_ops1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 17:09:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/14 17:13:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// / operator -> between vector and vector (vec / vec)
t_vec3	division_vec_dub(t_vec3 v, double dub)
{
	t_vec3	len;

	len.x = v.x / dub;
	len.y = v.y / dub;
	len.z = v.z / dub;
	return (len);
}

// / operator -> between vector and double (vec / double)
// MIGHT NOT NEED -> don't know
t_vec3	division_vec_vec(t_vec3 u, t_vec3 v)
{
	t_vec3	len;

	len.x = u.x / v.x;
	len.y = u.y / v.y;
	len.z = u.z / v.z;
	return (len);
}

// -------------- Other stuff we might need --------------
// This function calculates the dot product between two vectors u and v.
// The dot product of two vectors measures the cosine of the angle between 
// them, scaled by their lenghts (magnitudes).
double	dot_product(t_vec3 u, t_vec3 v)
{
	double	len;

	len = u.x * v.x + u.y * v.y + u.z * v.z;
	return (len);
}

// This function computes the cross product between two vectors u and v. 
// The cross product of two vectors results in a vector that is perpendicular 
// to both input vectors, whose direction is determined by the right-hand rule.
// right-hand rule: 
// (http://citadel.sjfc.edu/faculty/kgreen/vector/block1/vectors/node22.html) 
// OR (https://www.britannica.com/science/right-hand-rule-vectors)
t_vec3	cross_product(t_vec3 u, t_vec3 v)
{
	t_vec3	len;

	len.x = u.y * v.z - u.z * v.y;
	len.y = u.z * v.x - u.x * v.z;
	len.z = u.x * v.y - u.y * v.x;
	return (len);
}

// Calculates the length (magnitude) of a vector using the 
// Euclidean distance formula.
// Euclidean distance formula: 
// (https://www.cuemath.com/euclidean-distance-formula/)
double	length_squared(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
