/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quad.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 20:17:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/30 17:12:59 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	check_closest(t_obj_hit *obj_hit)
{
	if (obj_hit->t < obj_hit->closest_t)
	{
		obj_hit->closest_t = obj_hit->t;
		return (true);
	}
	return (false);
}

/**
 * @return true - intersection found
 * @return false - no intersection found
 */
bool	quadratic(t_obj_hit *obj_hit)
{
	obj_hit->d = obj_hit->b * obj_hit->b - 4 * obj_hit->a * obj_hit->c;
	if (obj_hit->d < 0)
        return (false);
	else 
    {
        obj_hit->root1 = (-obj_hit->b + sqrt(obj_hit->d)) / (2.0 * obj_hit->a);
        obj_hit->root2 = (-obj_hit->b - sqrt(obj_hit->d)) / (2.0 * obj_hit->a);
        if (obj_hit->root1 < obj_hit->root2 && obj_hit->root1 > 0)
            obj_hit->t = obj_hit->root1;
        else if (obj_hit->root2 > 0)
            obj_hit->t = obj_hit->root2;
		else
			return (false);
        return (true);
    }
}
