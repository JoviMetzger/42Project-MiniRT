/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 15:20:47 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/25 14:04:48 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

int	get_type(char *str)
{
	if (check_capital(str, 'A') == 1)
		return (1);
	if (check_capital(str, 'L') == 1)
		return (2);
	if (check_capital(str, 'C') == 1)
		return (3);
	if (check_pl(str) == 1)
		return (4);
	if (check_sp(str) == 1)
		return (5);
	if (check_cy(str) == 1)
		return (6);
	if (ft_strcmp(str, " ") == 0 || is_space(str))
		return (99);
	return (0);
}

char	**rt_malloc(char **arr, int size, int file)
{
	arr = (char **)malloc(sizeof(char *) * size + 1);
	if (!arr)
		parse_error("malloc failure", file);
	return (arr);
}

t_objects	*obj_malloc(t_data *data, char **arr, int size)
{
	data->objects = (t_objects *)malloc(sizeof(t_objects) * (size + 1));
	if (!data->objects)
		free_arr_error("parser error", arr, NULL);
	ft_bzero(data->objects, sizeof(data->objects));
	return (data->objects);
}
