/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/27 13:35:02 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// 
void ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray)
{
    int i = 0;

    while (i < data->total_obj_num)
    {
		intersect_sphere(&ray, &data->objects.sphere, obj_data);
        /* it works like this ^, but because intersect_sphere/intersect_plane/intersect_cylinder are bools we need to do something with it??
         * If we do, we can do something like: bool result = intersect_sphere(&ray, &data->objects.sphere, obj_data); and do something with result.
         *
         * aka. intersect_plane/intersect_cylinder don't need to be bools they can be void aswell.
         */
        
        // intersect_plane(&ray, &data->objects.plane, obj_data);
        // intersect_cylinder(&ray, &data->objects.cylinder, obj_data);
        i++;
    }
}
