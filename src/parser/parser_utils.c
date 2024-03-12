/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 15:20:47 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 19:06:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

int		is_num(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (c);
	return (0);
}

int	is_comma(int c)
{
	return (c == ',');
}

int	is_dot(int c)
{
	return (c == '.');
}

char	**rt_malloc(char **arr, int size, int file)
{
	arr = (char **)malloc(sizeof(char *) * size + 1);
	if (!arr)
		parse_error("malloc failure", file);
	return (arr);
}
