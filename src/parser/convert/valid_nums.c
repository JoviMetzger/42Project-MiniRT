/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_nums.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 18:26:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 19:11:29 by smclacke      ########   odam.nl         */
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

// coordinates -		[decimals] xyz
// coords


// light	-			[0.0,1.0]
int	is_ratio(char *str, int i, int num_flag, int dot_flag)
{
	while (str[i])
	{
		while (str[i] && is_num(str[i]))
		{
			num_flag++;
			i++;
		}
		if (str[i] && is_dot(str[i]))
		{
			dot_flag++;
			i++;
		}
		if (str[i] && !ratio_valid(str[i]))
			return (0);
	}
	if (dot_flag != 1 || num_flag < 2)
		return (0);
	return (1);
}

// r g b	- 			[0 - 255] no decimals
int	is_rgb(char *str, int i, int num_flag, int com_flag)
{
	while (str[i])
	{
		while (str[i] && is_num(str[i]))
		{
			num_flag++;
			i++;
		}
		if (num_flag > 3)
			return (0);
		if (str[i] && is_comma(str[i]))
			com_flag++;
		if (com_flag > 2)
			return (0);
		num_flag = 0;
		if (str[i] && !rgb_valid(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	convert_rgb(t_data *data, char *str, int type)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 0;
	b = 0;
	rgb = ft_split(str, ',');
	if (!rgb)
		return (0);
	if (!rgb[0] || !rgb[1] || !rgb[2])
		return (free_array(rgb), 0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	add_rgb(data, type, r, g, b);
	return (free_array(rgb), 1);
}
