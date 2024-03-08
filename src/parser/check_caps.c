/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_caps.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:25:52 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 15:40:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

/**
 * @brief	ensure we have the Ambient lighting, Camera and Light elements
 * 			and they are only declared once
*/
void	check_caps(char **arr)
{
	int		i;
	bool	a_flag;
	bool	c_flag;
	bool	l_flag;
	(void)	arr;


	i = 0;
	a_flag = false;
	c_flag = false;
	l_flag = false;
	printf("we are gunna check the caps\n");
	// while (arr[i])
	// {
	// 	while (is_space())
	// }
}
