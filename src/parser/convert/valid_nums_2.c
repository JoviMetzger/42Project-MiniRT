/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_nums_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 19:02:01 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 22:25:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

// vector	- 			[-1,1] xyz
int		convert_vector(t_data *data, char *str)
{
	char	**vec;
	int		x;
	int		y;
	int		z;

	vec = ft_split(str, ',');
	if (!vec)
		return (0);
	if (!vec[0] || !vec[1] || !vec[2])
		return (free_array(vec), 0);
	x = ft_atof(vec[0]);
	y = ft_atof(vec[1]);
	z = ft_atof(vec[2]);
	add_vec(data, x, y, z);
	return (free_array(vec), 1);
}


// FOV		-			[0,180]

// decimal	-			[decimals] (diameter/height)

