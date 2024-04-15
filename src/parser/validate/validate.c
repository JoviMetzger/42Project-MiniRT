/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 16:35:20 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/15 21:40:43 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	check_no_elems(char *str, int type)
{
	if (type == 8)
		return (1);
	else if (type == 'A' && (num_elems(str) != 3))
		return (par_err("invalid: Abiement: number of arguments"));
	else if (type == 'C' && (num_elems(str) != 4))
		return (par_err("invalid: Camera: number of arguments"));
	else if (type == 'L' && (num_elems(str) != 4))
		return (par_err("invalid: Light: number of arguments"));
	else if (type == 5 && (num_elems(str) != 4))
		return (par_err("invalid: Sphere: number of arguments"));
	else if (type == 4 && (num_elems(str) != 4))
		return (par_err("invalid: Plane: number of arguments"));
	else if (type == 6 && (num_elems(str) != 6))
		return (par_err("invalid: Cylinder: number of arguments"));
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
int	validate_elems(char **arr)
{
	int		i;
	int		type;
	int		count;

	i = 0;
	type = 0;
	count = 0;
	while (arr[i])
	{
		if (!is_valid_no(arr[i]))
			free_arr_error("invalid character", arr);
		type = get_type(arr[i]);
		if (type == 0)
			free_arr_error("unknown parser error", arr);
		if (type == 4 || type == 5 || type == 6)
			count++;
		if (!check_no_elems(arr[i], type))
			free_arr_error(NULL, arr);
		i++;
	}
	return (count);
}
