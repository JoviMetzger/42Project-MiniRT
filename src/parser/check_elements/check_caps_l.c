/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_caps_l.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:54:39 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 19:50:00 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

int	check_l(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == 'L')
	{
		if (!str[i + 1] || (str[i + 1] && !ft_isspace(str[i + 1])))
			return (0);
		return (1);
	}
	return (0);
}

static void	check_dup(char **arr, int i)
{
	while (arr[i])
	{
		if (check_l(arr[i]) == 1)
			free_arr_error("Duplicate Light element (L)", arr, NULL);
		i++;
	}
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
			flag = 1;
			if (arr[i + 1])
			{
				check_dup(arr, (i + 1));
				break ;
			}
		}
		i++;
	}
	if (flag == 0)
		free_arr_error("Missing Light element (L)", arr, NULL);
}
