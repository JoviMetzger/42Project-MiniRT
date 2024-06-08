/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 19:37:55 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/08 15:58:01 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

t_lightS	**lt_malloc(t_data *data, char **arr, int count)
{
	data->lights_i = 0;
	data->lightS = (t_lightS **)malloc(sizeof(t_lightS *) * (count + 1));
	if (!data->lightS)
		free_arr_error("parser error", arr);
	return (data->lightS);
}

void	free_lights(t_data *data)
{
	int		i;

	i = 0;
	if (data->lightS && data->lightS[i])
	{
		while (data->lightS[i])
		{
			free(data->lightS[i]);
			i++;
		}
	}
	free(data->lightS);
}

int	count_lights(char **arr)
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
	if (count > 3)
		return (0);
	return (count);
}

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
