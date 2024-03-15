/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_caps.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 23:42:42 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 18:05:52 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

	//////// COORDS ///////////
	// convert_coords(elem_str[2]); // create this func when i can use data...
	// t_pos3 struct
	
	// char	**coords;
	// double	x;
	// double	y;
	// double	z;
	
	// coords = ft_split(elem_str[1], ',');
	// /// also check we get three strings back
	// x = ft_atof(coords[0]);
	// y = ft_atof(coords[1]);
	// z = ft_atof(coords[2]);
	// free_array(coords);
	// printf("L x = %f, L y = %f, L z = %f\n", x, y, z);
	//////// COORDS ///////////

/*
 * #Identifier     #Coordinates        #Ratio      #R,G,B
 * L               -40.0,50.0,0.0      0.6         10,0,255
*/
int	sort_l(char **elem_str, t_data *data)
{
	double	ratio;

	//coords
	if (!is_ratio(elem_str[2], 0, 0, 0))
		return (0);
	ratio = ft_atof(elem_str[2]);
	data->light.ratio = ratio;
	if (!is_rbg(elem_str[3], 0, 0, 0))
		return (0);
	if (!convert_rgb(data, elem_str[3], 'L'))
		return (0);
	return (1);
}

/**
 * #Identifier    #Coordinates         #3D vector     #FOV
 * C              -50.0,0,20           0,0,1          70
*/
int	sort_c(char **elem_str, t_data *data)
{
	// coords
	// 3d vector
	// fov
}

/**
 * #Identifier     #Ratio        #R,G,B
 * A               0.2           255,255,255
*/
int	sort_a(char **elem_str, t_data *data)
{
	double		ratio;

	if (!is_ratio(elem_str[1], 0, 0, 0))
		return (0);
	ratio = ft_atof(elem_str[1]);
	data->ambient.ratio = ratio;
	if (!is_rbg(elem_str[2], 0, 0, 0))
		return (0);
	if (!convert_rgb(data, elem_str[2], 'A'))
		return (0);
	return (1);
}
