/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 16:41:33 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 23:32:58 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static void	sort_into_struct(char **elem_str, int type)
{
	int		i;

	i = 0;
	printf("type = %i\n", type);
	while (elem_str[i])
	{
		printf("str = %s\n", elem_str[i]);
		i++;
	}
}

/**
 * @brief	convert validated string data into double/int etc
 * 			as we convert, we add to t_data struct
 * 			after conversion, check converted info again:
 * 			check - ratio, format, etc but in converted form now not string
*/
static void	convert_element(char **arr, int type, int i)
{
	char	**elem_str;

	elem_str = ft_split(arr[i], ' ');
	if (!elem_str)
		free_arr_error("malloc failed", arr, NULL);
	sort_into_struct(elem_str, type);
	free_array(elem_str);
}

void	convert_input(t_data *data, char **arr)
{
	(void) data;
	int		i;
	int		type;
	int		flag;

	i = 0;
	type = 0;
	flag = 0;
	// for each element, make array, convert input, add to data struct
	// free secondary array each time
	// if error, free made array, free arr, error, exit
	while (arr[i])
	{
		type = get_type(arr[i]);
		printf("type first = %i\n", type);
		if (type == 999)
			i++;
		else if (type == 0)
			free_arr_error("Unknow parser error", arr, NULL);
		else if (type != 0 && type != 999)
		{
			convert_element(arr, type, i);
			i++;
		}
	}
	// validiate_numbers() // validate all data from within t_data struct
}
