/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_obj_input.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/25 12:43:28 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/25 14:04:57 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	sort_into_struct(char **elem_str, t_data *data)
{
	if (data->type == 5 && !sort_sp(elem_str, data))
		return (0);
	if (data->type == 6 && !sort_cy(elem_str, data))
		return (0);
	if (data->type == 4 && !sort_pl(elem_str, data))
		return (0);
	return (1);
}

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
void	convert_obj_input(t_data *data, char **arr, int count)
{
	int		i;

	i = 0;
	data->objects = obj_malloc(data, arr, count);
	while (arr[i])
	{
		data->type = get_type(arr[i]);
		if (data->type == 99 || data->type == 1
			|| data->type == 2 || data->type == 3)
			i++;
		else if (data->type == 0 || data->type > 6)
		{
			free(data->objects);
			free_arr_error("parser error", arr, NULL);
		}
		else if (data->type == 4 || data->type == 5 || data->type == 6)
		{
			data->objects[data->objects->index].type = data->type;
			printf("object type = %i\n", data->objects[data->objects->index].type);
			convert_element(arr, data, i);
			i++;
			data->objects->index++;
		}
	}
}
