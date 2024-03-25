/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 22:38:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// void ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray)
// TEST FUNCTION: Would like to have a void function that safes the result into the struct, and pass that result into calculate_colour to print the pixel.
bool ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray)
{
    int i = 0;
	double t;

    while (i < data->total_obj_num)
    {
		if (intersect_sphere(&ray, &data->objects.sphere, obj_data, &t))
			return true;
        // intersect_plane(&ray, &data->objects.plane, obj_data);
        // intersect_cylinder(&ray, &data->objects.cylinder, obj_data);
        i++;
    }
	return false;
}
