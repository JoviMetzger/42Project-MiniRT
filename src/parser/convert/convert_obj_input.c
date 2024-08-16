/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_obj_input.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/25 12:43:28 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/16 21:43:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

// /**
//  * #Identifier   #Coordinates: center normal edge1  edge2  #Edge_length    #R,G,B
// */
int	sort_sq(char **elem_str, t_data *data)
{
	if (!is_coord(elem_str[1], 0, 0))
		return (par_err("invalid: Square: coordinate"));
	if (!convert_coord(data, elem_str[1]))
		return (par_err("invalid: Square: coordinate"));
	if (!is_coord(elem_str[2], 0, 0))
		return (par_err("invalid: Square: 3D vector"));
	if (!convert_vector(data, elem_str[2]))
		return (par_err("invalid: Square: 3D vector"));
	if (!is_coord(elem_str[3], 0, 0))
		return (par_err("invalid: Square: 3D edge coordinate"));
	data->objs[data->objs_i]->point_flag = 0;
	if (!convert_coord(data, elem_str[3]))
		return (par_err("invalid: Square: 3D edge coordinate"));
	if (!is_coord(elem_str[4], 0, 0))
		return (par_err("invalid: Square: 3D edge coordinate"));
	data->objs[data->objs_i]->point_flag = 1;
	if (!convert_coord(data, elem_str[4]))
		return (par_err("invalid: Square: 3D edge coordinate"));
	if (!convert_double(data, elem_str[5], 3))
		return (par_err("invalid: Square: edge length"));
	if (!is_rgb(elem_str[6], 0, 0))
		return (par_err("invalid: Square: RGB | [0-255]"));
	if (!convert_rgb(data, elem_str[6]))
		return (par_err("invalid: Square: RGB | [0-255]"));
	return (1);
}

static int	sort_into_struct(char **elem_str, t_data *data)
{
	if (data->type == E_SPHERE && !sort_sp(elem_str, data))
		return (0);
	if (data->type == E_CYLINDER && !sort_cy(elem_str, data))
		return (0);
	if (data->type == E_PLANE && !sort_pl(elem_str, data))
		return (0);
	if (data->type == E_TRIANGLE && !sort_tr(elem_str, data))
		return (0);
	if (data->type == E_SQUARE && !sort_sq(elem_str, data))
		return (0);
	return (1);
}

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

static void	init_objs(t_data *data, char **arr)
{
	data->objs[data->objs_i] = object_malloc(data, arr);
	data->objs[data->objs_i]->type = data->type;
}

/**
 * @brief 7 == space, 1, 2 + 3 == A L C, 8 == HASH 
 */
void	convert_obj_input(t_data *data, char **arr, int count)
{
	int		i;

	i = 0;
	data->objs = obj_malloc(data, arr, count);
	while (arr[i])
	{
		data->type = get_type(arr[i]);
		if (data->type == 7 || data->type == 1
			|| data->type == 2 || data->type == 3 || data->type == 8)
			i++;
		else if (data->type == 0 || data->type > 10)
		{
			free_objects(data);
			free_arr_error("parser error", arr);
		}
		else if (data->type == 4 || data->type == 5
			|| data->type == 6 || data->type == 9 || data->type == 10)
		{
			init_objs(data, arr);
			convert_element(arr, data, i);
			i++;
			data->objs_i++;
		}
	}
	data->objs[data->objs_i] = NULL;
}
