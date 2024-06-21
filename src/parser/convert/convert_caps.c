/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_caps.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 23:42:42 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/21 15:54:14 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

/*
 * #Identifier     #Coordinates        #Ratio      #R,G,B
 * L               -40.0,50.0,0.0      0.6         10,0,255
*/
int	sort_l(char **elem_str, t_data *data)
{
	double	ratio;

	if (!is_coord(elem_str[1], 0, 0))
		return (par_err("invalid: Light: coordinate"));
	if (!convert_coord(data, elem_str[1]))
		return (par_err("invalid: Light: coordinate"));
	if (!is_ratio(elem_str[2], 0, 0))
		return (par_err("invalid: Light: light ratio | [0.0,1.0]"));
	ratio = ft_atof(elem_str[2]);
	if (!is_valid_light(ratio))
		return (par_err("invalid: Light: light ratio | [0.0,1.0]"));
	data->light[data->light_i]->ratio = ratio;
	if (!is_rgb(elem_str[3], 0, 0))
		return (par_err("invalid: Light: RGB | [0-255]"));
	if (!convert_rgb(data, elem_str[3]))
		return (par_err("invalid: Light: RGB | [0-255]"));
	return (1);
}

/**
 * #Identifier    #Coordinates         #3D vector     #FOV
 * C              -50.0,0,20           0,0,1          70
 * 
 * FOV : Horizontal field of view in degrees in range [0,180]: 70
*/
int	sort_c(char **elem_str, t_data *data)
{
	if (!is_coord(elem_str[1], 0, 0))
		return (par_err("invalid: Camera: coordinate"));
	if (!convert_coord(data, elem_str[1]))
		return (par_err("invalid: Camera: coordinate"));
	if (!is_coord(elem_str[2], 0, 0))
		return (par_err("invalid: Camera: 3D vector"));
	if (!convert_vector(data, elem_str[2]))
		return (par_err("invalid: Camera: 3D vector"));
	if (!convert_fov(data, elem_str[3]))
		return (par_err("invalid: Camera: FOV"));
	return (1);
}

/**
 * #Identifier     #Ratio        #R,G,B
 * A               0.2           255,255,255
*/
int	sort_a(char **elem_str, t_data *data)
{
	double		ratio;

	if (!is_ratio(elem_str[1], 0, 0))
		return (par_err("invalid: Ambient: light ratio | [0.0,1.0]"));
	ratio = ft_atof(elem_str[1]);
	if (!is_valid_light(ratio))
		return (par_err("invalid: Ambient: light ratio | [0.0,1.0]"));
	data->ambient.ratio = ratio;
	if (!is_rgb(elem_str[2], 0, 0))
		return (par_err("invalid: Ambient: RGB | [0-255]"));
	if (!convert_rgb(data, elem_str[2]))
		return (par_err("invalid: Ambient: RGB | [0-255]"));
	return (1);
}
