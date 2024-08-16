/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 19:37:55 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/16 18:28:34 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

t_light	**lt_malloc(t_data *data, char **arr, int count)
{
	data->light_i = 0;
	data->light = (t_light **)malloc(sizeof(t_light *) * (count + 1));
	if (!data->light)
		free_arr_error("parser error", arr);
	return (data->light);
}

void	free_light(t_data *data)
{
	int		i;

	i = 0;
	if (data->light)
	{
		while (data->light[i])
		{
			free(data->light[i]);
			i++;
		}
		free(data->light);
	}
}

int	count_light(char **arr)
{
	int	i;
	int	type;
	int	count;

	i = 0;
	type = 0;
	count = 0;
	while (arr[i])
	{
		type = get_type(arr[i]);
		if (type == 0 || type < 0 || type > 9)
			free_arr_error("unknown parser error", arr);
		if (type == 2)
			count++;
		i++;
	}
	if (count > 4)
		return (0);
	return (count);
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
