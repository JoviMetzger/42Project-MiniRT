/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:36:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 17:08:54 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

// check if elements - sp pl cy are there
// check for other shit, error on other shit
// can change this easily if we add elements later :)

// static void	check_other_elements(char **arr)
// {
	
// }

void	check_elements(char **arr)
{
	check_caps_a(arr);
	check_caps_l(arr);
	check_caps_c(arr);
	// check_other_elements(arr);
}
