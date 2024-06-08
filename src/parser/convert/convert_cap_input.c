/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_cap_input.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 16:41:33 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/08 16:01:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	sort_into_struct(char **elem_str, t_data *data)
{
	if (data->type == E_AMBIENT && !sort_a(elem_str, data))
		return (0);
	if (data->type == E_LIGHT && !sort_l(elem_str, data))
		return (0);
	if (data->type == E_CAMERA && !sort_c(elem_str, data))
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
		free_arr_error("malloc failed", arr);
	if (!sort_into_struct(elem_str, data))
	{
		free_array(elem_str);
		free_arr_error(NULL, arr);
	}
	free_array(elem_str);
}

static t_lightS	*light_malloc(t_data *data, char **arr)
{
	data->lightS[data->lights_i] = (t_lightS *)malloc(sizeof(t_lightS));
	if (!data->lightS[data->lights_i])
	{
		free_lights(data);
		free_arr_error("parser error", arr);
	}
	ft_bzero(data->lightS[data->lights_i], sizeof(t_lightS));
	return (data->lightS[data->lights_i]);
}

void	convert_cap_input(t_data *data, char **arr, int count)
{
	int		i;

	i = 0;
	data->lightS = lt_malloc(data, arr, count);
	while (arr[i])
	{
		data->type = get_type(arr[i]);
		if (data->type == E_SPACE || data->type == E_PLANE
			|| data->type == E_SPHERE || data->type == E_CYLINDER
			|| data->type == E_HASH || data->type == E_TRIANGLE)
			i++;
		else if (data->type == 0 || data->type > 9)
		{
			// free_lights(data);
			free_arr_error("parser error", arr);
		}
		if (data->type == E_AMBIENT || data->type == E_LIGHT
			|| data->type == E_CAMERA)
		{
			if (data->type == E_LIGHT)
			{	
				data->lightS[data->lights_i] = light_malloc(data, arr);
				convert_element(arr, data, i);
				data->lights_i++;
			}
			else
				convert_element(arr, data, i);
			i++;
		}
	}
	data->lightS[data->lights_i] = NULL;
}
