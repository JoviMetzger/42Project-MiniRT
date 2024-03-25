/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 17:07:54 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/19 14:57:54 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

int	check_com(char *str, int i)
{
	int	flag;

	flag = 0;
	while (str[i])
	{
		if (str[i] && is_comma(str[i]))
			flag++;
		i++;
	}
	if (flag != 2)
		return (0);
	return (1);
}

int	check_neg(char *str, int i)
{
	while (str[i])
	{
		if (str[i] && is_dash(str[i]))
		{
			if ((str[i + 1] && !is_num(str[i + 1]))
				|| !str[i + 1])
				return (0);
		}
		i++;
	}
	return (1);
}

int	coord_valid(int c)
{
	return (ft_isspace(c) || is_num(c) || is_dot(c) || is_dash(c)
		|| is_comma(c));
}

int	ratio_valid(int c)
{
	return (ft_isspace(c) || is_num(c) || is_dot(c));
}

int	rgb_valid(int c)
{
	return (ft_isspace(c) || is_num(c) || is_comma(c));
}
