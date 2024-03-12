/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_a.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 17:37:17 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 18:03:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

int	validate_a(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		if (str[i] && str[i] == 'A')
			i++;
		if (!ft_isspace(str[i]) && str[i] != 'A')
			
	}
	return (1);
}
