/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 15:20:47 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/07 20:18:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// some space for funny lil funcs
// value checking funcs

// is R G B format etc

int		is_dot(int c)
{
	return (c == '.');
}

void	close_protect(int file)
{
	if (close(file) == -1)
		error_msg("Closing file errored");
}
