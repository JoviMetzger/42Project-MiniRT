/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:30:59 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 15:34:01 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

void	free_arr_error(char *msg, char **arr, t_elems *check)
{
	if (check)
		free(check);
	free_array(arr);
	error_msg(msg);
}

void	free_close_parse_error(char *msg, char **ar, char *line, int file)
{
	close_protect(file);
	free_array(ar);
	free(line);
	error_msg(msg);
}

void	parse_error(char *msg, int file)
{
	close_protect(file);
	error_msg(msg);
}

void	error_msg2(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}
