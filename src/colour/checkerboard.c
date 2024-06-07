/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkerboard.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/07 16:28:06 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Gives the correct value into the colour struct and returns it.
static t_colour	ft_colour(int r, int g, int b)
{
	t_colour	colour;

	colour.r = r;
	colour.g = g;
	colour.b = b;
	return (colour);
}

/*	This function calculates the checkerboard for an sphere.
 *		- First we need to calculate theta and phi.
 *				- theta : Angle in the x-z plane.
 *				- phi 	: Angle from the positive y-axis.
 *		- Normalize theta and phi to [0, 1].
 *				- u : Theta ranges from -pi to pi.
 *				- v : Phi ranges from 0 to pi.
 *		- Scale coordinates by number of squares.
 *			- num_squares can be adjusted for more or less squares.
 *		- Determine color based on checkerboard pattern.
 *			- Result can only be 1 or 0.
 *			- 1 : is black, so the colour will be {0, 0, 0};
 *			- 0 : is not black, so colour will be {255, 255, 255}; (white)
 *					- It is possible to give it the colour of the sphere.
 */
t_colour	get_sphere_checkerboard(t_vec3 normal)
{
	t_checkerboard	check_var;
	bool			is_black;
	int				num_squares;

	num_squares = 10;
	check_var.theta = atan2(normal.z, normal.x);
	check_var.phi = acos(normal.y);
	check_var.u = (check_var.theta + M_PI) / (2 * M_PI);
	check_var.v = check_var.phi / M_PI;
	check_var.square_u = check_var.u * num_squares;
	check_var.square_v = check_var.v * num_squares;
	is_black = ((int)floor(check_var.square_u) % 2
			== (int)floor(check_var.square_v) % 2);
	if (is_black)
		return (ft_colour(0, 0, 0));
	else
		return (ft_colour(255, 255, 255));
}
