/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 16:35:20 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 17:02:31 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

// check elem format (name declaration)
// check info for each elem (no. of info for each correct)
// check format for each piece of info (commas, decimals...)

/**
 * @brief	ensure each elements has the correct number of 
 * 			specifications
 * 			check that these specifications are formatted correctly
 * 			anything found that shouldn't be there, error and exit
*/
void	validate_elems(char **arr)
{
	check_no_info(arr);
	check_formats(arr);
}
