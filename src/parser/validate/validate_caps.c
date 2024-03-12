/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_caps.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 18:54:25 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 18:59:24 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

/**
 * #Identifier     #Ratio        #R,G,B
 * A               0.2           255,255,255
*/
int	validate_a(char *str)
{
	int		i;
	char	**arr;

	i = 0;
	arr = ft_split(str, ' ');
	if(!arr)
	{
		printf("malloc fail\n");
		return (0);
	}
	if (ft_strcmp(arr[0], "A") != 0)
		return (free_array(arr), 0);
	if (!is_light(arr[1]))
		return (free_array(arr), 0);
	if (!is_rbg(arr[2]))
		return (free_array(arr), 0);
	else
		printf("check good\n");
	free_array(arr);
	return (1);
}

// validate C
/**
 * #Identifier    #Coordinates         #3D vector     #FOV
 * C              -50.0,0,20           0,0,1          70
*/
int	validate_c(char *str)
{
	printf("str = %s\n", str);
	return (1);
}

// validate L
/*
 * #Identifier     #Coordinates        #Ratio      #R,G,B
 * L               -40.0,50.0,0.0      0.6         10,0,255
*/
int	validate_l(char *str)
{
	printf("str = %s\n", str);
	return (1);
}

