/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quad.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 20:17:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/29 17:16:09 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	check_closest(t_hit_data *hit)
{
	if (hit->t < hit->closest_t)
	{
		hit->closest_t = hit->t;
		return (true);
	}
	return (false);
}

/**
 * @return true - intersection found
 * @return false - no intersection found
 */
bool	quadratic(t_hit_data *hit)
{
	hit->d = hit->b * hit->b - 4 * hit->a * hit->c;
	if (hit->d < 0)
		return (false);
	else
	{
		hit->root1 = (-hit->b
				+ sqrt(hit->d)) / (2.0 * hit->a);
		hit->root2 = (-hit->b
				- sqrt(hit->d)) / (2.0 * hit->a);
		if (hit->root1 < hit->root2 && hit->root1 > 0)
			hit->t = hit->root1;
		else if (hit->root2 > 0)
			hit->t = hit->root2;
		else
			return (false);
		return (true);
	}
}
