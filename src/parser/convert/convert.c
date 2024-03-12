/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 16:41:33 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 22:01:24 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

// use split by space for this, careful with memory!
// void		convert_input(char **arr)
// {
//		// piece by piece, convert and add to struct
//		// check again validity of input
// }

/**
 * @brief	convert validated string data into double/int etc
 * 			as we convert, we add to t_data struct
 * 			after conversion, check converted info again:
 * 			check - ratio, format, etc but in converted form now not string
*/
void	convert_input(t_data *data, char **arr)
{
	char	**elem_str;
	int		amount;
	int		i;
	
	i = 0;
	while (arr[i])
	{
		amount = input_count(arr[i]);
		elem_str = (char **)malloc(sizeof(char *) * (amount + 1));
		if (!elem_strs)
			free_arr_error("malloc failed convert_input()", arr, NULL);
		i++;
	}
	
	// convert_elems(t_data *data, char **arr);
	// convert + add as we goo
	// check again all info is valid, ratio, format...
}

void	convert_input(t_data *data, char **arr)
{
	(void) data;
	int		i;
	int		type;

	i = 0;
	type = 0;
	// for each element, make array, convert input, add to data struct
	// free secondary array each time
	// if error, free made array, free arr, error, exit
	while (arr[i])
	{
		type = is_caps(arr[i]);
		if (type)
			convert_element(arr, type, i);
		else
		{
			type = is_other(arr[i]);
			convert_element(arr, type, i);
		}
		i++;
	}
	// free arr
	// validate all data
}
