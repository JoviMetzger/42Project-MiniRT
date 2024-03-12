/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_elements.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:36:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 20:12:20 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static	int	check_invalid(char *str)
{
	int		i;

	i = 0;
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

static	void	check_present(char *str, t_elems *check)
{
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
	{
		if (check_sp(&str[i]))
			check->sp_b = true;
		else if (check_pl(&str[i]))
			check->pl_b = true;
		else if (check_cy(&str[i]))
			check->cy_b = true;
	}
}

static void	check_other_elements(char **arr)
{
	int			i;
	t_elems		*check;

	i = 0;
	check = (t_elems *)malloc(sizeof(t_elems));
	ft_bzero(check, sizeof(t_elems));
	while (arr[i])
	{
		if (check_invalid(arr[i]) == 1)
			free_arr_error("Unknown element declaration", arr, check);
		check_present(arr[i], check);
		i++;
	}
	if (!check->sp_b)
		free_arr_error("Missing element declaration (sp)", arr, check);
	if (!check->cy_b)
		free_arr_error("Missing element declaration (cy)", arr, check);
	if (!check->pl_b)
		free_arr_error("Missing element declaration (pl)", arr, check);
	free(check);
}

/**
 * @brief	check_caps_a/l/c checks that each of these mandatory
 * 			elements are declared in the file and there is only one of each
 * 			check_other_elements checks for pl, sp, cy
 * 			can have multiple of these but nothing else declared
 * 			** only checking declaration and multiples, not valid input **
*/
void	check_elements(char **arr)
{
	check_l(arr);
	check_c(arr);
	check_a(arr);
	check_other_elements(arr);
}
