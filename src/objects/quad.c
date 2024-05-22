/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quad.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 20:17:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/22 14:34:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	check_closest(t_hit_data *hit_data)
{
	if (hit_data->t < hit_data->closest_t)
	{
		hit_data->closest_t = hit_data->t;
		return (true);
	}
	return (false);
}

/**
 * @return true - intersection found
 * @return false - no intersection found
 */
bool	quadratic(t_hit_data *hit_data)
{
	hit_data->d = hit_data->b * hit_data->b - 4 * hit_data->a * hit_data->c;
	if (hit_data->d < 0)
		return (false);
	else
	{
		hit_data->root1 = (-hit_data->b
				+ sqrt(hit_data->d)) / (2.0 * hit_data->a);
		hit_data->root2 = (-hit_data->b
				- sqrt(hit_data->d)) / (2.0 * hit_data->a);
		if (hit_data->root1 < hit_data->root2 && hit_data->root1 > 0)
			hit_data->t = hit_data->root1;
		else if (hit_data->root2 > 0)
			hit_data->t = hit_data->root2;
		else
			return (false);
		return (true);
	}
}
