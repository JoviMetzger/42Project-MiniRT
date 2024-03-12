/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:27:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 20:33:33 by smclacke      ########   odam.nl         */
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
	if (is_dash(c) || is_num(c) || is_dot(c)
		|| ft_isspace(c) || is_comma(c))
		return (1);
	return (0);
}
