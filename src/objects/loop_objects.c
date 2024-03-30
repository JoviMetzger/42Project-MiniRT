/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/30 17:53:36 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * incase for testing...
 * 		printf("coords = %f,%f,%f\n", data->objs[i]->center.x, data->objs[i]->center.y, data->objs[i]->center.z);
		printf("diameter = %f\n", data->objs[i]->diameter);
		printf("r = %i, g = %i, b = %i\n", data->objs[i]->colour.r,data->objs[i]->colour.g, data->objs[i]->colour.b);
		exit(EXIT_SUCCESS);
*/

// void ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray)
// TEST FUNCTION: Would like to have a void function that safes the result into the struct, and pass that result into calculate_colour to print the pixel.
bool ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray)
{
	// (void)	obj_data;
	// (void)	ray;
	int		i = 0;
	double t;

	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_SPHERE)
		{
			printf("sphere\n");
			if (intersect_sphere(&ray, data->objs[i], obj_data, &t))
				return true;
		}
		if (data->objs[i]->type == E_CYLINDER)
		{
			printf("cylinder\n");
			if (intersect_cylinder(&ray, data->objs[i], obj_data, &t))
				return true;
		}
			// if (data->objs[i]->type == E_PLANE)
			// {
			// 	if (intersect_plane(&ray, &data->objs[i], obj_data))
			// 		return true;
			// }
		i++;
	}
	return false;
}
