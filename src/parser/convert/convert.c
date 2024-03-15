/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 16:41:33 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 18:03:33 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	sort_into_struct(char **elem_str, t_data *data, int type)
{
	if (type == A && !sort_a(elem_str, data))
		return (0);
	else if (type == L && !sort_l(elem_str, data))
		return (0);
	else if (type == C && !sort_c(elem_str, data))
		return (0);
	// else if (type == sp && sort_sp(elem_str, data))
	// 	return (0);
	// else if (type == cy && sort_cy(elem_str, data))
	// 	return (0);
	// else if (type == pl && sort_pl(elem_str, data))
	// 	return (0);
	return (1);
}

/**
 * @brief	convert validated string data into double/int etc
 * 			as we convert, we add to t_data struct
 * 			after conversion, check converted info again:
 * 			check - ratio, format, etc but in converted form now not string
*/
static void	convert_element(char **arr, t_data *data, int type, int i)
{
	char	**elem_str;

	elem_str = ft_split(arr[i], ' ');
	if (!elem_str)
		free_arr_error("malloc failed", arr, NULL);
	if (!sort_into_struct(elem_str, data, type))
	{
		free_array(elem_str);
		free_arr_error("Unknown parser error", arr, NULL);
	}
	free_array(elem_str);
}

void	convert_input(t_data *data, char **arr)
{
	int		i;
	int		type;

	i = 0;
	type = 0;
	while (arr[i])
	{
		type = get_type(arr[i]);
		if (type == 999)
			i++;
		else if (type == 0)
			free_arr_error("Unknown parser error", arr, NULL);
		else if (type != 0 && type != 999)
		{
			convert_element(arr, data, type, i);
			i++;
		}
	}
	// validiate_numbers() // validate all data from within t_data struct (check ranges etc)
}
