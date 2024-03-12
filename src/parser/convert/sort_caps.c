/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_caps.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 23:42:42 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/13 00:28:39 by smclacke      ########   odam.nl         */
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
	(void) data;
	double		ratio;

	ratio = ft_atof(elem_str[1]);
	printf("ratio = %f\n", ratio);
	
	//////// RGB   ///////////
	// convert_rgb(elem_str[2]); // create this func when i can use data...
	
	// solution for now for rgb
	char	**rgb;
	int			r;
	int			g;
	int			b;

	
	rgb = ft_split(elem_str[2], ',');
	if (!rgb)
		printf("oopies\n");
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_array(rgb);
	printf("r = %i, g = %i, b = %i\n", r, g, b);
	
	
	return (1);
}
