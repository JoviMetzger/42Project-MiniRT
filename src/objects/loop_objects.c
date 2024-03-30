/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/30 16:15:11 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// void ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray)
// TEST FUNCTION: Would like to have a void function that safes the result into the struct, and pass that result into calculate_colour to print the pixel.
bool ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray)
{
	// (void)	obj_data;
	// (void)	ray;
    int i = 0;
	double t;

    while (i < data->objs->i)
    {
		if (data->objs->type == E_SPHERE)
		{
			if (intersect_sphere(&ray, &data->objs[i], obj_data, &t))
				return true;
		}
		// if (data->objs->type == E_CYLINDER)
		// {
		// 	if (intersect_cylinder(&ray, &data->objs[i], obj_data, &t))
		// 		return true;
		// }
		// if (data->objs->type == E_PLANE)
		// {
			// if (intersect_plane(&ray, &data->objs[i], obj_data))
			// 	return true;
		// }
        i++;
    }
	// exit(EXIT_SUCCESS);
	return false;
}
