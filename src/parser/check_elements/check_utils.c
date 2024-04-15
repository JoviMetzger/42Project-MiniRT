/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 17:30:17 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/15 19:46:32 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

int	check_pl(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] + 1)
	{
		if (str[i] == 'p' && str[i + 1] == 'l')
		{
			if (!str[i + 2] || (str[i + 2] && !ft_isspace(str[i + 2])))
				return (0);
			return (1);
		}
	}
	return (0);
}

int	check_sp(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] + 1)
	{
		if (str[i] == 's' && str[i + 1] == 'p')
		{
			if (!str[i + 2] || (str[i + 2] && !ft_isspace(str[i + 2])))
				return (0);
			return (1);
		}
	}
	return (0);
}

int	check_cy(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] + 1)
	{
		if (str[i] == 'c' && str[i + 1] == 'y')
		{
			if (!str[i + 2] || (str[i + 2] && !ft_isspace(str[i + 2])))
				return (0);
			return (1);
		}
	}
	return (0);
}

void	check_dup(char **arr, int i, int type)
{
	while (arr[i])
	{
		if (check_capital(arr[i], type) == 1)
			free_arr_error("duplicate element", arr);
		i++;
	}
}

int	check_capital(char *str, int type)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == type)
	{
		if (!str[i + 1] || (str[i + 1] && !ft_isspace(str[i + 1])))
			return (0);
		return (1);
	}
	return (0);
}
