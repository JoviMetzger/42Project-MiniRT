/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quad.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 20:17:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/15 20:24:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	check_closest(t_obj_data *obj_data)
{
	if (obj_data->t < obj_data->closest_t)
	{
		obj_data->closest_t = obj_data->t;
		return (true);
	}
	return (false);
}

bool	quadratic(t_obj_data *obj_data)
{
	if (obj_data->d < 0)
        return (false);	// No intersection
	obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2.0 * obj_data->a);
	obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2.0 * obj_data->a);
	if (obj_data->root1 < obj_data->root2)
		obj_data->t = obj_data->root1;
	else
		obj_data->t = obj_data->root2;
	if (obj_data->t <= 0)
		return (false);
	return (true); // Intersection found
}
