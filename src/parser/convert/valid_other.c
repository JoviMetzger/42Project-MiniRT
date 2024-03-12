/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_other.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 18:55:59 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 19:27:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

// do each validation after conversion to check numbers not string :)

// validate sp
/**
 * #Identifier     #Coordinates        #Diameter       #R,G,B
 * sp              0.0,0.0,20.6        12.6            10,0,255
*/
// int	validate_sp(char *str)
// {
// 	int		i;

// 	i = 0;
// 	// check number of elements
// 	while (str[i])
// 	{
// 		if (!is_num(str[i]) && !is_dot(str[i]) && !is_comma(str[i]))
// 			return (0);
// 	}
// 	return (1);
// }

// // validate pl
// /**
//  * #Identifier     #Coordinates        #3D vector      #R,G,B
//  * pl              0.0,0.0,-10.0       0.0,1.0,0.0     0,0,225
// */
// int	validate_pl(char *str)
// {
// 	int		i;

// 	i = 0;
// 	// check number of elements
// 	while (str[i])
// 	{
// 		if (!is_num(str[i]) && !is_dot(str[i]) && !is_comma(str[i]))
// 			return (0);
// 	}
// 	return (1);
// }

// // validate cy
// /**
//  * #Identifier     #Coordinates        #3D vector      #Diameter       #Height     #R,G,B
//  * cy              50.0,0.0,20.6       0.0,0.0,1.0     14.2            21.42       10,0,255
// */
// int	validate_cy(char *str)
// {
// 	int		i;

// 	i = 0;
// 	// check number of elements
// 	while (str[i])
// 	{
// 		if (!is_num(str[i]) && !is_dot(str[i]) && !is_comma(str[i]))
// 			return (0);
// 	}
// 	return (1);
// }
