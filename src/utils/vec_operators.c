/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_operators.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/11 16:39:26 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// -------------- Operators (+-*/) --------------
// + operator
t_vec3 plus(t_vec3 u, t_vec3 v) 
{
    t_vec3	len;

	len.x = u.x + v.x;
	len.y = u.y + v.y;
	len.z = u.z + v.z;
	return (len);
}

t_vec3 plus_vecdub(t_vec3 u, double v) 
{
    t_vec3	len;

	len.x = u.x + v;
	len.y = u.y + v;
	len.z = u.z + v;
	return (len);
}

// - operator
t_vec3 minus(t_vec3 u, t_vec3 v)
{
    t_vec3	len;

	len.x = u.x - v.x;
	len.y = u.y - v.y;
	len.z = u.z - v.z;
	return (len);
}

// * operator -> between two vectors (vec * vec)
t_vec3 mult_vecvec(t_vec3 u, t_vec3 v) 
{
    t_vec3	len;

	len.x = u.x * v.x;
	len.y = u.y * v.y;
	len.z = u.z * v.z;
	return (len);
}

// * operator -> between vector and double (vec * double)
// MIGHT NOT NEED -> don't know
t_vec3 mult_vecdub(t_vec3 v, double dub) 
{
    t_vec3	len;

	len.x = v.x * dub;
	len.y = v.y * dub;
	len.z = v.z * dub;
	return (len);
}

// / operator -> between vector and vector (vec / vec)
t_vec3 division_vec_dub(t_vec3 v, double dub) 
{
    t_vec3	len;

	len.x = v.x / dub;
	len.y = v.y / dub;
	len.z = v.z / dub;
	return (len);
}

// / operator -> between vector and double (vec / double)
// MIGHT NOT NEED -> don't know
t_vec3 division_vec_vec(t_vec3 u, t_vec3 v) 
{
    t_vec3	len;

	len.x = u.x / v.x;
	len.y = u.y / v.y;
	len.z = u.z / v.z;
	return (len);
}


// -------------- Other stuff we might need --------------
// This function calculates the dot product between two vectors u and v. 
// The dot product of two vectors measures the cosine of the angle between them, scaled by their lenghts (magnitudes).
double dot_product(t_vec3 u, t_vec3 v) // Don't know if I need this one 
{
    double	len;

	len = u.x * v.x + u.y * v.y + u.z * v.z;
	return (len);
}

// This function computes the cross product between two vectors u and v. 
// The cross product of two vectors results in a vector that is perpendicular to both input vectors, whose direction is determined by the right-hand rule.
// right-hand rule: (http://citadel.sjfc.edu/faculty/kgreen/vector/block1/vectors/node22.html) OR (https://www.britannica.com/science/right-hand-rule-vectors)
t_vec3 cross_product(t_vec3 u, t_vec3 v) 
{
    t_vec3	len;

	len.x = u.y * v.z - u.z * v.y;
	len.y = u.z * v.x - u.x * v.z;
	len.z = u.x * v.y - u.y * v.x;
	return (len);
}

// Calculates the length (magnitude) of a vector using the Euclidean distance formula.
// Euclidean distance formula: (https://www.cuemath.com/euclidean-distance-formula/)
double length_squared(t_vec3 vec)
{
    return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

// Returns a new vector that has the same direction as v but with a lenght (magnitude) of 1. 
// This operation effectively normalizes the vector.
// Normalized vectors are often used in calculations involving reflection and refraction rays to ensure accurate results.
t_vec3	normalize_vector(t_vec3 v)
{
    t_vec3	len;

    double normalize = length_squared(v);
    len = division_vec_dub(v, normalize);
	return (len);
}

double	distance(t_vec3 pnt1, t_vec3 pnt2)
{
	double d;

	d = sqrt(pow(pnt2.x - pnt1.x, 2) + pow(pnt2.y - pnt1.y, 2) + pow(pnt2.z - pnt1.z, 2));
	return (d);
}