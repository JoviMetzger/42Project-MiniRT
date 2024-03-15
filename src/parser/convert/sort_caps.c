/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_caps.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 23:42:42 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 16:39:44 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

// init + malloc structs? should A C L be pointers in the data struct??
	// data->ambient = (t_ambient *)malloc(sizeof(t_ambient));
	// if (!data->ambient)
	// 	return (0);
	// data->ambient.ratio = ratio;
	// printf("data ambient ratio = %f\n", data->ambient.ratio);
	// exit(EXIT_SUCCESS);

// sort_a
// sort_c
// sort_l

int	sort_a(char **elem_str, t_data *data)
{
	// (void)	data;
	/////////// RATIO ///////////
	double		ratio;

	ratio = ft_atof(elem_str[1]);
	printf("A ratio = %f\n", ratio);
	data->ambient.ratio = ratio;
	printf("struct ratio = %f\n", data->ambient.ratio);
	// /////////// RATIO ///////////
	

	
	// //////// RGB   ///////////
	// // convert_rgb(elem_str[2]); // create this func when i can use data...
	
	// // solution for now for rgb
	// char	**rgb;
	// int			r;
	// int			g;
	// int			b;

	
	// rgb = ft_split(elem_str[2], ',');
	// /// also check we get three strings back
	// r = ft_atoi(rgb[0]);
	// g = ft_atoi(rgb[1]);
	// b = ft_atoi(rgb[2]);
	// free_array(rgb);
	// printf("A r = %i, A g = %i, A b = %i\n", r, g, b);
	//////// RGB   ///////////
	
	
	return (1);
}

int	sort_l(char **elem_str, t_data *data)
{
	(void) data;
	//////// COORDS ///////////
	// convert_coords(elem_str[2]); // create this func when i can use data...
	// t_pos3 struct
	
	char	**coords;
	double	x;
	double	y;
	double	z;
	
	coords = ft_split(elem_str[1], ',');
	/// also check we get three strings back
	x = ft_atof(coords[0]);
	y = ft_atof(coords[1]);
	z = ft_atof(coords[2]);
	free_array(coords);
	printf("L x = %f, L y = %f, L z = %f\n", x, y, z);
	//////// COORDS ///////////


	/////////// RATIO ///////////
	double	ratio;

	ratio = ft_atof(elem_str[2]);
	printf("L ratio = %f\n", ratio);
	/////////// RATIO ///////////

	//////// RGB   ///////////
	// convert_rgb(elem_str[2]); // create this func when i can use data...
	
	// solution for now for rgb
	char	**rgb;
	int			r;
	int			g;
	int			b;

	rgb = ft_split(elem_str[3], ',');
	/// also check we get three strings back
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_array(rgb);
	printf("L r = %i, L g = %i, L b = %i\n", r, g, b);
	//////// RGB   ///////////
	
	return (1);
}
