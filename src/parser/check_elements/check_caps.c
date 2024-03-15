/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_caps.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:25:52 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 18:24:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	check_cap_valid(char **arr, int type)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (arr[i])
	{
		if (check_capital(arr[i], type) == 1)
		{
			flag = 1;
			if (arr[i + 1])
			{
				check_dup(arr, (i + 1), type);
				break ;
			}
		}
		i++;
	}
	return (flag);
}

/**
 * @brief	ensure we have the Light element
 * 			and they is only one declared
*/
void	check_l(char **arr)
{
	int		type;
	int		flag;

	type = 'L';
	flag = check_cap_valid(arr, type);
	if (flag == 0)
		free_arr_error("Missing Light element (L)", arr, NULL);
}

/**
 * @brief	ensure we have the Camera element
 * 			and they is only one declared
*/
void	check_c(char **arr)
{
	int		type;
	int		flag;

	type = 'C';
	flag = check_cap_valid(arr, type);
	if (flag == 0)
		free_arr_error("Missing Camera element (C)", arr, NULL);
}

/**
 * @brief	ensure we have the Ambient lighting element
 * 			and they is only one declared
*/
void	check_a(char **arr)
{
	int		type;
	int		flag;

	type = 'A';
	flag = check_cap_valid(arr, type);
	if (flag == 0)
		free_arr_error("Missing Ambient Light element (A)", arr, NULL);
}
