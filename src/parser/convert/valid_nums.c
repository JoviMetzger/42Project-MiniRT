/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_nums.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 18:26:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 21:47:48 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

// coordinates -		can be negative [decimals] xyz
int		is_coord(char *str, int i, int num_flag)
{
	if (!check_neg(str, 0))
		return (0);
	if (!check_com(str, 0))
		return (0);
	while (str[i])
	{
		while (str[i] && (is_num(str[i]) || is_dash(str[i]) || is_dot(str[i])))
			i++;
		num_flag++;
		if (str[i] && is_comma(str[i]))
			i++;
		if (str[i] && !coord_valid(str[i]))
			return (0);
	}
	if (num_flag != 3)
		return (0);
	return (1);
}

int	convert_coord(t_data *data, char *str)
{
	char	**coord;
	int		i;
	int		x;
	int		y;
	int		z;

	i = 0;
	coord = ft_split(str, ',');
	if (!coord)
		return (0);
	if (!coord[0] || !coord[1] || !coord[2])
		return (free_array(coord), 0);
	x = ft_atof(coord[0]);
	y = ft_atof(coord[1]);
	z = ft_atof(coord[2]);
	add_coord(data, x, y, z);
	return (free_array(coord), 1);
}

// light	-			can't be negative [0.0,1.0]
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

// r g b	- 			[0 - 255] no decimals or negatives
int	is_rgb(char *str, int i, int num_flag)
{
	if (!check_com(str, 0))
		return (0);
	while (str[i])
	{
		while (str[i] && is_num(str[i]))
		{
			num_flag++;
			i++;
		}
		if (num_flag > 3)
			return (0);
		if (is_comma(str[i]))
			num_flag = 0;
		if (str[i] && !rgb_valid(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	convert_rgb(t_data *data, char *str)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb)
		return (0);
	if (!rgb[0] || !rgb[1] || !rgb[2])
		return (free_array(rgb), 0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	add_rgb(data, r, g, b);
	return (free_array(rgb), 1);
}
