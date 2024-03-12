/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_nums.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 18:26:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 19:02:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

/**

light	-			[0.0,1.0]

r g b	- 			[0 - 255] no decimals

vector	- 			[-1,1] xyz

coordinates -		[decimals] xyz

FOV		-			[0,180]

decimal	-			[decimals] (diameter/height)

*/

// is light
// is rgb
// is vector



int	is_rbg(char *str)
{
	(void) str;
	return (1);
}

int	is_light(char *str)
{
	int		i;

	i = 0;
	printf("str = %s\n", str);
	// while (str[i])
	// {
		
	// }
	return (1);
}
