/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/28 15:13:59 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

//
bool ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray)
{
    int i = 0;

    while (i < data->objs->i)
    {
		if (data->objs->type == E_SPHERE)
		{
            if (intersect_sphere(&ray, &data->objs[i], obj_data))
                return (true);
		}
        // intersect_plane(&ray, &data->objs[i], obj_data);
        // intersect_cylinder(&ray, &data->objs[i], obj_data);
        i++;
    }
    return (false);
}
