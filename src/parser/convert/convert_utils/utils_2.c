/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 19:37:55 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/08 13:07:17 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

// util for textures
char	*give_null(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	str[i] = '\0';
	return (str);
}

void	cyl_cals(t_data *data)
{
	data->objs[data->objs_i]->top = minus(data->objs[data->objs_i]->center,
			mult_vecdub(data->objs[data->objs_i]->vector,
				data->objs[data->objs_i]->height_half / 2));
	data->objs[data->objs_i]->base = minus(data->objs[data->objs_i]->center,
			mult_vecdub(data->objs[data->objs_i]->vector,
				-(data->objs[data->objs_i]->height_half / 2)));
}
