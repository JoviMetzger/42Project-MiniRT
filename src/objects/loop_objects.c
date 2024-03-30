/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/30 18:09:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

//
void ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray)
{
    int i = 0;

	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_SPHERE)
		{
            if (intersect_sphere(&ray, data->objs[i], obj_data))
                return ;
		}
        // // 'if' OR 'if/else if'????
        // if (data->objs->type == E_PLANE)
		// {
        //     if (intersect_plane(&ray, &data->objs[i], obj_data))
        //         return ;
		// }
        // if (data->objs->type == E_CYLINDER)
		// {
        //     if (intersect_cylinder(&ray, &data->objs[i], obj_data))
        //         return ;
		// }
        i++;
    }
    return ;
}
