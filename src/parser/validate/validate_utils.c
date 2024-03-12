/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 17:21:34 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 17:58:40 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

int	is_caps(char *str)
{
	if (check_a(str) == 1)
		return (A);
	else if (check_l(str) == 1)
		return (L);
	else if (check_c(str) == 1)
		return (C);
	return (0);	
}

int	is_other(char *str)
{
	if (check_pl(str) == 1)
		return (pl);
	else if (check_sp(str) == 1)
		return (sp);
	else if (check_cy(str) == 1)
		return (cy);
	return (0);	
}
