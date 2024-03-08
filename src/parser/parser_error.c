/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:30:59 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 15:50:35 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

void	close_protect(int file)
{
	if (close(file) == -1)
		error_msg("Closing file errored");
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
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

void error_msg2(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}
