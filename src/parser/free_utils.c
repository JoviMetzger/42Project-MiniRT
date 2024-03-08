/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:50:09 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 16:51:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

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

void	free_close_util(char *line, int file)
{
	free(line);
	close_protect(file);
}

void	close_protect(int file)
{
	if (close(file) == -1)
		error_msg("Closing file errored");
}
