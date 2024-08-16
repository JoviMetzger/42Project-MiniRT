/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 16:35:20 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/16 20:51:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	num_elems(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i])
			count++;
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (count);
}

int	is_caps(char *str)
{
	if (check_capital(str, 'A') == 1)
		return (A);
	else if (check_capital(str, 'L') == 1)
		return (L);
	else if (check_capital(str, 'C') == 1)
		return (C);
	return (0);
}

static int	check_no_elems(char *str, int type)
{
	if (type == 8)
		return (1);
	else if (type == 1 && (num_elems(str) != 3))
		return (par_err("invalid: Abiement: number of arguments"));
	else if (type == 3 && (num_elems(str) != 4))
		return (par_err("invalid: Camera: number of arguments"));
	else if (type == 2 && (num_elems(str) != 4))
		return (par_err("invalid: Light: number of arguments"));
	else if (type == 5 && (num_elems(str)))
		return (par_err("invalid: Sphere: number of arguments"));
	else if (type == 4 && (num_elems(str) != 3))
		return (par_err("invalid: Plane: number of arguments"));
	else if (type == 6 && (num_elems(str) != 5))
		return (par_err("invalid: Cylinder: number of arguments"));
	else if (type == 9 && (num_elems(str) != 5))
		return (par_err("invalid: Triangle: number of arguments"));
	else if (type == 10 && (num_elems(str) != 5)) // check this for square
		return (par_err("invalid: Square: number of arguments"));
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
		type = get_type(arr[i]);
		if (type == 0)
			free_arr_error("unknown parser error", arr);
		if (type == 4 || type == 5 || type == 6 || type == 9 || type == 10)
			count++;
		if (!check_no_elems(arr[i], type))
			free_arr_error(NULL, arr);
		i++;
	}
	return (count);
}
