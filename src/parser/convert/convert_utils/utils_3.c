/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/24 20:40:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/16 21:16:34 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

void	invalid_check(t_type type, t_data *data, char **arr)
{
	if (type == 0 || type > 10)
	{
		free_light(data);
		free_arr_error("parser error", arr);
	}
}

bool	dont_skip(t_type type)
{
	if (type == E_AMBIENT || type == E_LIGHT || type == E_CAMERA)
		return (true);
	return (false);
}

bool	skip_this(t_type type)
{
	if (type == E_SPACE || type == E_PLANE || type == E_SPHERE
		|| type == E_CYLINDER || type == E_HASH || type == E_TRIANGLE
		|| type == E_SQUARE)
		return (true);
	return (false);
}
