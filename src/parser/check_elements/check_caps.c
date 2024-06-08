/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_caps.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:25:52 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/08 13:15:39 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	check_cap_valid(char **arr, int type)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (type == 'L')
		return (1);
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
		free_arr_error("missing Light element (L)", arr);
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
		free_arr_error("missing Camera element (C)", arr);
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
		free_arr_error("missing Ambient Light element (A)", arr);
}
