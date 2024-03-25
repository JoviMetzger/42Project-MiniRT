/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_cap_input.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 16:41:33 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/25 13:00:00 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	sort_into_struct(char **elem_str, t_data *data)
{
	if (data->type == 1 && !sort_a(elem_str, data))
		return (0);
	if (data->type == 2 && !sort_l(elem_str, data))
		return (0);
	if (data->type == 3 && !sort_c(elem_str, data))
		return (0);
	return (1);
}

/**
 * @brief	convert validated string data into double/int etc
 * 			as we convert, we add to t_data struct
 * 			after conversion, check converted info again:
 * 			check - ratio, format, etc but in converted form now not string
*/
static void	convert_element(char **arr, t_data *data, int i)
{
	char	**elem_str;

	elem_str = ft_split(arr[i], ' ');
	if (!elem_str)
		free_arr_error("malloc failed", arr, NULL);
	if (!sort_into_struct(elem_str, data))
	{
		free_array(elem_str);
		free_arr_error(NULL, arr, NULL);
	}
	free_array(elem_str);
}

// 99 == space
void	convert_cap_input(t_data *data, char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		data->type = get_type(arr[i]);
		if (data->type == 99 || data->type == 4
			|| data->type == 5 || data->type == 6)
			i++;
		else if (data->type == 0 || data->type > 6)
			free_arr_error("parser error", arr, NULL);
		else if (data->type == 1 || data->type == 2 || data->type == 3)
		{
			convert_element(arr, data, i);
			i++;
		}
	}
}
