/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_calcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 16:14:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/16 17:46:11 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"


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
		if (data->pix[i]->hit_b == true)
		{
			// if not in shadow... colour = light;
			// else just give ambient
			// data->pix[i]->colour = data->pix[i]->ambient;
			data->pix[i]->colour = data->pix[i]->light;
		}
		else
			data->pix[i]->colour = data->pix[i]->black;
		i++;
	}
	// if pixel->light != 0, yes, a light hits it so change pixel->colour to the one with light
	// if pixel is in ANY light, then give the light... 
	// we have black, ambient and light saved, now while loop to give light to correct pixel
	// i = 0;
	// while (i < data->total_pix)
	// {
	// 	if (data->pix[i]->hit_b == true)
	// 		data->pix[i]->colour = data->pix[i]->light;
	// 	else
	// 		data->pix[i]->colour = data->pix[i]->black;
	// 	i++;
	// }
}
