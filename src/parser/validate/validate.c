/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 16:35:20 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 17:59:01 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	check_caps(char *str)
{
	if (is_caps(str) == A)
	{
		if (!validate_a(str))
			return (0);
	}
	else if (is_caps(str) == L)
	{
		if (!validate_l(str))
			return (0);
	}
	else if (is_caps(str) == C)
	{
		if (!validate_c(str))
			return (0);
	}
	return (1);
}

static int	check_other(char *str)
{
	if (is_other(str) == pl)
	{
		if (!validate_pl(str))
			return (0);
	}
	else if (is_other(str) == sp)
	{
		if (!validate_sp(str))
			return (0);
	}
	else if (is_other(str) == cy)
	{
		if (!validate_cy(str))
			return (0);
	}
	return (1);
}

/**
 * @brief	ensure each elements has the correct number of 
 * 			specifications
 * 			check that these specifications are formatted correctly
 * 			(commas, decimals, number of digits etc)
 * 			size/ratio etc will be checked after conversion
 * 			anything found that shouldn't be there, error and exit
*/
void	validate_elems(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (is_caps(arr[i]))
		{
			if (!check_caps(arr[i]))
				free_arr_error("Element format error", arr, NULL);
		}
		if (is_other(arr[i]))
		{
			if (!check_other(arr[i]))
				free_arr_error("Element format error", arr, NULL);
		}
		i++;
	}
}
