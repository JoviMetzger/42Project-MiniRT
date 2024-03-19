/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_ratio.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:26:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/19 16:09:33 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

// coords (no ratio?)
// diameter (?)
// heighter (?)

// light [0.0,1.0] (no negative)
int	is_valid_light(double light)
{
	if (light < 0.0 || light > 1.0)
		return (0);
	return (1);
}

// rgb [0-255]
int	is_valid_rgb(int r, int g, int b)
{
	if (r > 255 || r < 0)
		return (0);
	if (g > 255 || g < 0)
		return (0);
	if (b > 255 || b < 0)
		return (0);
	return (1);
}

// vector [-1,1]
int	is_valid_vector(double x, double y, double z)
{
	if (x > 1 || x < -1)
		return (0);
	if (y > 1 || y < -1)
		return (0);
	if (z > 1 || z < -1)
		return (0);
	return (1);
}

// FOV [0,180]
int	is_valid_fov(int fov)
{
	if (fov < 0 || fov > 180)
		return (0);
	return (1);
}
