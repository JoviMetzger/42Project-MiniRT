/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operators2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/06 19:58:29 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// -------------- Other math functions --------------
/*	This function calculates the dot product between two vectors u and v. 
 *		- The dot product of two vectors measures the cosine 
 *		  of the angle between them, scaled by their lenghts (magnitudes).
 */
double	dot_product(t_vec3 u, t_vec3 v)
{
	double	len;

	len = u.x * v.x + u.y * v.y + u.z * v.z;
	return (len);
}

/*	This function computes the cross product between two vectors u and v. 
 *	- The cross product of two vectors results in a vector 
 *	  that is perpendicular to both input vectors, 
 *	  whose direction is determined by the right-hand rule.
 *	- right-hand rule: 
 *	  (http://citadel.sjfc.edu/faculty/kgreen/vector/block1/vectors/node22.html) 
 *	  (https://www.britannica.com/science/right-hand-rule-vectors)
 */
t_vec3	cross_product(t_vec3 u, t_vec3 v)
{
	t_vec3	len;

	len.x = u.y * v.z - u.z * v.y;
	len.y = u.z * v.x - u.x * v.z;
	len.z = u.x * v.y - u.y * v.x;
	return (len);
}

/*	Calculates the length (magnitude) of a vector 
 *	using the Euclidean distance formula.
 *		- Euclidean distance formula: 
 *		  (https://www.cuemath.com/euclidean-distance-formula/)
 */
double	length_squared(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

/*	Returns a new vector that has the same direction as v, 
 *	but with a lenght (magnitude) of 1. 
 *	This function effectively normalizes the vector.
 */
t_vec3	normalize(t_vec3 v)
{
	t_vec3	len;
	double	normalize;

	normalize = length_squared(v);
	len = division_vec_dub(v, normalize);
	return (len);
}

// This function gets the distance between two vectors.
double	distance(t_vec3 pnt1, t_vec3 pnt2)
{
	double	d;

	d = sqrt(pow(pnt2.x - pnt1.x, 2) + pow(pnt2.y
				- pnt1.y, 2) + pow(pnt2.z - pnt1.z, 2));
	return (d);
}
