/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_nums_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 19:02:01 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/19 15:22:06 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

// vector	- 			[-1,1] xyz
int		convert_vector(t_data *data, char *str)
{
	char		**vec;
	double		x;
	double		y;
	double		z;

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
int	convert_fov(t_data *data, char *str)
{
	int		i;
	int		fov;

	i = 0;
	while (str[i])
	{
		if (str[i] && !valid_num(str[i]))
			return (0);
		i++;
	}
	fov = ft_atoi(str);
	data->camera.FOV = fov;
	return (1);
}

// FLAG 1 = diameter, FLAG 2 = height
// decimal	-			[decimals] (diameter/height) 
// - similar to ratio, try just use one func and send flag for which data type etc
int	convert_double(t_data *data, char *str, int flag, int type)
{
	double	ratio;

	if (!is_ratio(str, 0, 0, 0))
		return (0);
	ratio = ft_atof(str);
	if (flag == 1)
	{
		if (type == 234)
		{
			data->objects.sphere.diameter = ratio;
				return (1);
		}
		else if (type == 432)
		{
			data->objects.cylinder.diameter = ratio;
				return (1);
		}
	}
	else if (flag == 2)
	{
		data->objects.cylinder.height = ratio;
			return (1);
	}
	return (0);
}
