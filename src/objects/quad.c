/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quad.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 20:17:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/06 18:05:10 by smclacke      ########   odam.nl         */
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

bool	quadratic(t_hit_data *hit)
{
	hit->d = hit->b * hit->b - 4 * hit->a * hit->c;
	if (hit->d < 0)
		return (false);
	else
	{
		hit->d = sqrt(hit->d);
		hit->root1 = (-hit->b - hit->d) / (2.0 * hit->a);
		hit->root2 = (-hit->b + hit->d) / (2.0 * hit->a);
		if (hit->root1 > hit->root2)
		{
			double tmp = hit->root1;
			hit->root1 = hit->root2;
			hit->root2 = tmp;
		}
		if (hit->root1 < 0)
		{
			hit->root1 = hit->root2;
			if (hit->root1 < 0)
				return (false);
		}
		hit->t = hit->root1;
		return (true);
	}
}
