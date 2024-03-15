/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:27:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 18:33:19 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

int	is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}

int	is_dash(int c)
{
	return (c == '-');
}

int	is_valid(int c)
{
	if (!is_dash(c) && !is_num(c) && !is_dot(c)
		&& !ft_isspace(c) && !is_comma(c))
		return (0);
	return (1);
}

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

int	get_type(char *str)
{
	if (check_capital(str, 'A') == 1)
		return (1);
	else if (check_capital(str, 'L') == 1)
		return (2);
	else if (check_capital(str, 'C') == 1)
		return (3);
	else if (check_pl(str) == 1)
		return (4);
	else if (check_sp(str) == 1)
		return (5);
	else if (check_cy(str) == 1)
		return (6);
	else if (ft_strcmp(str, " ") == 0 || is_space(str))
		return (999);
	return (0);
}
