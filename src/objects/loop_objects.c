/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/30 17:37:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// void ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray)
// TEST FUNCTION: Would like to have a void function that safes the result into the struct, and pass that result into calculate_colour to print the pixel.
bool ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray, int i)
{
	(void)	obj_data;
	(void)	ray;

	if (!data->objs[i])
		return (false);
	int		type = data->objs[i]->type;

	printf("type = %i\n", type);
	// (void)	i;
    // int i = 0;
	// double t;

    // while (i < data->objs->i)
    // {
		// if (data->objs[i])
		// {
		// if (data->objs[i].type)
		// {
		// 	if (data->objs[i].type == E_SPHERE)
		// 	{
		// 		printf("sphere\n");
		// 		return true;
		// 		// if (intersect_sphere(&ray, &data->objs[i], obj_data, &t))
		// 			// return true;
		// 	}
		// 	if (data->objs[i].type == E_CYLINDER)
		// 	{
		// 		printf("cylinder\n");
		// 		return true;
		// 		// if (intersect_cylinder(&ray, &data->objs[i], obj_data, &t))
		// 			// return true;
		// 	}
		// 	else
		// 		return false;
		// }
		// else
		// 	return false ;
		// if (data->objs->type == E_PLANE)
		// {
			// if (intersect_plane(&ray, &data->objs[i], obj_data))
			// 	return true;
		// }
    //     i++;
    // }
	// exit(EXIT_SUCCESS);
	return false;
}
