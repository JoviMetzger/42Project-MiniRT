/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
<<<<<<< HEAD:zom_notes/dont_need_files/loop_objects.c
/*   Updated: 2024/04/02 15:39:26 by smclacke      ########   odam.nl         */
=======
/*   Updated: 2024/03/30 19:34:56 by jmetzger      ########   odam.nl         */
>>>>>>> main:src/objects/loop_objects.c
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// DON'T NEED THIS!!!!!
// // if sphere, intersect, then get sphere colour, then return colour...
// //
// void ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray)
// {
//     int i = 0;

<<<<<<< HEAD:zom_notes/dont_need_files/loop_objects.c
/** 
 * @todo you can also go away
*/

// if sphere, intersect, then get sphere colour, then return colour...
//
// void ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray)
// {
//     int i = 0;

=======
>>>>>>> main:src/objects/loop_objects.c
// 	while (i < data->objs_i)
// 	{
// 		if (data->objs[i]->type == E_SPHERE)
// 		{
//             if (intersect_sphere(&ray, data->objs[i], obj_data))
//                 return ;
// 		}
//         // // 'if' OR 'if/else if'????
//         // if (data->objs->type == E_PLANE)
// 		// {
//         //     if (intersect_plane(&ray, &data->objs[i], obj_data))
//         //         return ;
// 		// }
//         // if (data->objs->type == E_CYLINDER)
// 		// {
//         //     if (intersect_cylinder(&ray, &data->objs[i], obj_data))
//         //         return ;
// 		// }
//         i++;
//     }
//     return ;
// }
