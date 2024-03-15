/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 16:35:20 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 18:31:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	check_no_elems(char *str, int type)
{
	if (type == 'A' && (num_elems(str) != 3))
		return (0);
	else if (type == 'C' && (num_elems(str) != 4))
		return (0);
	else if (type == 'L' && (num_elems(str) != 4))
		return (0);
	else if (type == 5 && (num_elems(str) != 4))
		return (0);
	else if (type == 4 && (num_elems(str) != 4))
		return (0);
	else if (type == 6 && (num_elems(str) != 6))
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
		type = get_type(arr[i]);
		if (type == 0)
			free_arr_error("Unknow parser error", arr, NULL);
		if (!check_no_elems(arr[i], type))
			free_arr_error("Invalid number of arguments", arr, NULL);
		i++;
	}
}
