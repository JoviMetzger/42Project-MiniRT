/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_other.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 23:42:49 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/19 16:07:55 by smclacke      ########   odam.nl         */
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
		return (par_err("invalid: Plane: coordinate"));
	if (!convert_coord(data, elem_str[1]))
		return (par_err("invalid: Plane: coordinate"));
	if (!is_coord(elem_str[2], 0, 0))
		return (par_err("invalid: Plane: 3D vector"));
	if (!convert_vector(data, elem_str[2]))
		return (par_err("invalid: Plane: 3D vector"));
	if (!is_rgb(elem_str[3], 0, 0))
		return (par_err("invalid: Plane: RGB | [0-255]"));
	if (!convert_rgb(data, elem_str[3]))
		return (par_err("invalid: Plane: RGB | [0-255]"));
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
		return (par_err("invalid: Sphere: coordinate"));
	if (!convert_coord(data, elem_str[1]))
		return (par_err("invalid: Sphere: coordinate"));
	if (!convert_double(data, elem_str[2], 1, 234))
		return (par_err("invalid: Sphere: diameter"));
	if (!is_rgb(elem_str[3], 0, 0))
		return (par_err("invalid: Sphere: RGB | [0-255]"));
	if (!convert_rgb(data, elem_str[3]))
		return (par_err("invalid: Sphere: RGB | [0-255]"));
	return (1);
}

// sort_cy
// /**
//  * #Identifier  #Coordinates     #3D vector    #Diameter   #Height  #R,G,B
//  * cy           50.0,0.0,20.6    0.0,0.0,1.0   14.2        21.42    10,0,255
// */
int	sort_cy(char **elem_str, t_data *data)
{
	if (!is_coord(elem_str[1], 0, 0))
		return (par_err("invalid: Cylinder: coordinate"));
	if (!convert_coord(data, elem_str[1]))
		return (par_err("invalid: Cylinder: coordinate"));
	if (!is_coord(elem_str[2], 0, 0))
		return (par_err("invalid: Cylinder: 3D vector"));
	if (!convert_vector(data, elem_str[2]))
		return (par_err("invalid: Cylinder: 3D vector"));
	if (!convert_double(data, elem_str[3], 1, 432))
		return (par_err("invalid: Cylinder: diameter"));
	if (!convert_double(data, elem_str[4], 2, 432))
		return (par_err("invalid: Cylinder: height"));
	if (!is_rgb(elem_str[5], 0, 0))
		return (par_err("invalid: Cylinder: RGB | [0-255]"));
	if (!convert_rgb(data, elem_str[5]))
		return (par_err("invalid: Cylinder: RGB | [0-255]"));
	return (1);
}
