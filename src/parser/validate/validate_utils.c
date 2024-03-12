/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 17:21:34 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 20:15:46 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

int	is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}

int	is_valid_no(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		while (str[i] && is_alpha(str[i]))
			i++;
		if (!is_num(str[i]) && !is_dot(str[i])
			&& !is_comma(str[i]) && !ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	num_elems(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i])
			count++;
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (count);
}

int	is_caps(char *str)
{
	if (check_capital(str, 'A') == 1)
		return (A);
	else if (check_capital(str, 'L') == 1)
		return (L);
	else if (check_capital(str, 'C') == 1)
		return (C);
	return (0);
}

int	is_other(char *str)
{
	if (check_pl(str) == 1)
		return (pl);
	else if (check_sp(str) == 1)
		return (sp);
	else if (check_cy(str) == 1)
		return (cy);
	return (0);
}
