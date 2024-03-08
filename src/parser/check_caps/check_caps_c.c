/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_caps_c.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:54:53 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 17:00:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	check_c(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == 'C')
		return (1);
	return (0);
}	

/**
 * @brief	ensure we have the Camera element
 * 			and they is only one declared
*/
void	check_caps_c(char **arr)
{
	int		i;
	int		flag;


	i = 0;
	flag = 0;
	while (arr[i])
	{
		if (check_c(arr[i]) == 1)
		{
			if (arr[i + 1])
			{
				i++;
				while (arr[i])
				{
					if (check_c(arr[i]) == 1)
						free_arr_error("Duplicate Camera element", arr);
					i++;
				}
				break ;
			}
		}
		i++;
	}
}
