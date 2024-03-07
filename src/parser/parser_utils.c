/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 15:20:47 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/07 19:42:26 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// some space for funny lil funcs
// value checking funcs

// is R G B format

int		is_dot(int c)
{
	return (c == '.');
}
