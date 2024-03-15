/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_other.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 23:42:49 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 21:48:52 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

// sort_pl
// /**
//  * #Identifier     #Coordinates        #3D vector      #R,G,B
//  * pl              0.0,0.0,-10.0       0.0,1.0,0.0     0,0,225
// */
int	sort_pl(char **elem_str, t_data *data)
{
	if (!is_coord(elem_str[1], 0, 0))
		return (0);
	if (!convert_coord(data, elem_str[1]))
		return (0);
	// 3d vector [2]
	if (!is_rgb(elem_str[3], 0, 0))
		return (0);
	if (!convert_rgb(data, elem_str[3]))
		return (0);
	return (1);
}

// sort_sp
/**
 * #Identifier     #Coordinates        #Diameter       #R,G,B
 * sp              0.0,0.0,20.6        12.6            10,0,255
*/
int	sort_sp(char **elem_str, t_data *data)
{
	if (!is_coord(elem_str[1], 0, 0))
		return (0);
	if (!convert_coord(data, elem_str[1]))
		return (0);
	// diameter [2]
	if (!is_rgb(elem_str[3], 0, 0))
		return (0);
	if (!convert_rgb(data, elem_str[3]))
		return (0);
	return (1);
}

// sort_cy
// /**
//  * #Identifier     #Coordinates        #3D vector      #Diameter       #Height     #R,G,B
//  * cy              50.0,0.0,20.6       0.0,0.0,1.0     14.2            21.42       10,0,255
// */
int	sort_cy(char **elem_str, t_data *data)
{

	if (!is_coord(elem_str[1], 0, 0))
		return (0);
	if (!convert_coord(data, elem_str[1]))
		return (0);
	// 3d vector[2]
	// diameter [3]
	// height [4]
	if (!is_rgb(elem_str[5], 0, 0))
		return (0);
	if (!convert_rgb(data, elem_str[5]))
		return (0);
	return (1);
}

