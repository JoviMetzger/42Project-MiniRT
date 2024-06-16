/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_calcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 16:14:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/16 18:37:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

static bool	intersect_light(t_data *data)
{
	(void) data;
	return (true);
	// return (false);
}

/**
 * light array: are we creating multiple light rays, then checking the intersection?
 * or are we checking if the pixel is hit directly by any of the lights?
 * where do i loop the light array? - im confused
 */

void	do_calcs(t_data *data)
{
	int			i = 0;
	t_hit_data	hit;

	while (i < data->total_pix)
	{
		data->ray = ft_create_ray(data, data->pix[i]->x, data->pix[i]->y);
		ft_calculate_colour(data, &hit, i);
		data->mouse.mou_y = data->pix[i]->y;
		data->mouse.mou_x = data->pix[i]->x;
		data->pix[i]->hit_t = hit.t;
		i++;
	}
	i = 0;
	while (i < data->total_pix)
	{
		int j = 0;
		if (data->pix[i]->hit_b == true)
		{
			data->pix[i]->colour = data->pix[i]->ambient;
			while (j < data->light_i)
			{
// light is already save in pixel, but need to check if (a) light is hitting obj pixel directly 
				if (intersect_light(data))
					data->pix[i]->colour = data->pix[i]->light;
				j++;
			}
		}
		else
			data->pix[i]->colour = data->pix[i]->black;
		i++;
	}
}
