/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quad.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 20:17:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/30 17:53:32 by smclacke      ########   odam.nl         */
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
	obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;
	if (obj_data->d < 0)
        return (false);	// No intersection
	else 
    {
        obj_data->root1 = (-obj_data->b + sqrt(obj_data->d)) / (2.0 * obj_data->a);
        obj_data->root2 = (-obj_data->b - sqrt(obj_data->d)) / (2.0 * obj_data->a);
        if (obj_data->root1 < obj_data->root2 && obj_data->root1 > 0)
            obj_data->t = obj_data->root1;
        else if (obj_data->root2 > 0)
            obj_data->t = obj_data->root2;
		else
			return (false);
        return (true); // Intersection found
    }
}
