/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_utils_2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 17:30:17 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 17:58:19 by smclacke      ########   odam.nl         */
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
