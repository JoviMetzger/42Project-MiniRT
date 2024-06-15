/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 16:33:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/15 13:43:26 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

t_colour give_light(t_data *data)
{
	add_light(data->vars, data->ray);
	data->vars->result.r = fmin(255, fmax(0, data->vars->result.r));
	data->vars->result.g = fmin(255, fmax(0, data->vars->result.g));
	data->vars->result.b = fmin(255, fmax(0, data->vars->result.b));
	return (data->vars->result);
}

uint32_t	get_light(t_data *data)
{
	t_colour	light;

	light = give_light(data);
	return (ft_convert_rgb(light.r, light.g, light.b));
}

bool	in_light(t_data *data, t_hit_data *hit, int i)
{
	(void)	hit;
	int		tmp_i;
	double	max_hit;
	double	closest_hit;
	
	tmp_i = 0;
	max_hit = DBL_MAX;
	closest_hit = 0;
	if (data->pix[i]->hit_b == true && data->pix[i]->hit_t != DBL_MAX)
	{
		while (tmp_i < data->total_pix)
		{
			if (data->pix[tmp_i]->hit_t < max_hit)
				closest_hit = data->pix[tmp_i]->hit_t;
			tmp_i++;
		}
		if (data->pix[i]->hit_t <= closest_hit)
			return (true);
	}
	return (false);
}
