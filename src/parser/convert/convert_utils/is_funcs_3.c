/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_funcs_3.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 13:58:32 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/10 13:59:46 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

int	is_hash(int c)
{
	return (c == '#');
}

int	hash_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_hash(str[i]))
			return (1);
		i++;
	}
	return (0);
}
