/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_elements.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:36:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/15 21:49:51 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

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

static	int	check_invalid(char *str)
{
	int		i;

	i = 0;
	if (hash_str(str))
		return (0);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
	{
		if (str[i] != 'A' && str[i] != 'L' && str[i] != 'C'
			&& !check_sp(&str[i]) && !check_pl(&str[i])
			&& !check_cy(&str[i]))
			return (1);
	}
	return (0);
}

static void	check_other_elements(char **arr)
{
	int			i;

	i = 0;
	while (arr[i])
	{
		if (check_invalid(arr[i]) == 1)
			free_arr_error("unknown element declaration", arr);
		i++;
	}
}

/**
 * @brief	check_caps_a/l/c checks that each of these mandatory
 * 			elements are declared in the file and there is only one of each
 * 			check_other_elements checks for pl, sp, cy
 * 			can have multiple of these OR NONE OF THEM OR A COMBO :)
 * 			** only checking declaration and multiples, not valid input **
*/
void	check_elements(char **arr)
{
	check_l(arr);
	check_c(arr);
	check_a(arr);
	check_other_elements(arr);
}
