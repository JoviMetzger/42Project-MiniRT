/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_funcs_2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 14:59:56 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/19 15:04:16 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && !ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid_num(int c)
{
	return (ft_isspace(c) || is_num(c));
}

int	is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}

int	is_dash(int c)
{
	return (c == '-');
}
