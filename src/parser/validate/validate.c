/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 16:35:20 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 20:34:13 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	check_no_elems(char *str, int type)
{
	if (type == A && (num_elems(str) != 3))
		return (0);
	if (type == C && (num_elems(str) != 4))
		return (0);
	if (type == L && (num_elems(str) != 4))
		return (0);
	if (type == sp && (num_elems(str) != 4))
		return (0);
	if (type == pl && (num_elems(str) != 4))
		return (0);
	if (type == cy && (num_elems(str) != 6))
		return (0);
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
	int		type;

	i = 0;
	type = 0;
	while (arr[i])
	{
		if (!is_valid_no(arr[i]))
			free_arr_error("Invalid character", arr, NULL);
		type = is_caps(arr[i]);
		if (type)
		{
			if (!check_no_elems(arr[i], type))
				free_arr_error("Invalid number of arguments", arr, NULL);
		}
		else
		{
			type = is_other(arr[i]);
			if (!check_no_elems(arr[i], type))
				free_arr_error("Invalid number of arguments", arr, NULL);
		}
		i++;
	}
}
