/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_caps_l.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:54:39 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 17:00:51 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	check_l(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == 'L')
		return (1);
	return (0);
}	

/**
 * @brief	ensure we have the Light element
 * 			and they is only one declared
*/
void	check_caps_l(char **arr)
{
	int		i;
	int		flag;


	i = 0;
	flag = 0;
	while (arr[i])
	{
		if (check_l(arr[i]) == 1)
		{
			if (arr[i + 1])
			{
				i++;
				while (arr[i])
				{
					if (check_l(arr[i]) == 1)
						free_arr_error("Duplicate Light element", arr);
					i++;
				}
				break ;
			}
		}
		i++;
	}
}
