/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 17:07:54 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 19:10:35 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

void	add_rgb(t_data *data, int type, int r, int g, int b)
{
	if (type == 1)
		add_to_ambient(data, r, g, b);
	else if (type == 2)
		add_to_light(data, r, g, b);
	else if (type == 4)
		add_to_pl(data, r, g, b);
	else if (type == 5)
		add_to_sp(data, r, g, b); 
	else if (type == 6)
		add_to_cy(data, r, g, b);
}

int	ratio_valid(int c)
{
	return (ft_isspace(c) || is_num(c) || is_dot(c));
}

int	rgb_valid(int c)
{
	return (ft_isspace(c) || is_num(c) || is_comma(c));
}
