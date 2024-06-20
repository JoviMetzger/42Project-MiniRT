/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_calcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 16:14:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/20 14:33:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

void	do_calcs(t_data *data)
{
	t_hit_data	hit;
	int			i = 0;

	while (i < data->total_pix)
	{
		data->ray = ft_create_ray(data, data->pix[i]->x, data->pix[i]->y);
		ft_calculate_colour(data, &hit, i);
		data->mouse.mou_y = data->pix[i]->y;
		data->mouse.mou_x = data->pix[i]->x;
		data->pix[i]->hit_t = hit.t;
		i++;
	}
	// i = 0;
	// while (i < data->total_pix)
	// {
	// 	if (data->pix[i]->hit_b == true)
	// 	{
	// 		data->pix[i]->colour = data->pix[i]->light;
	// 		// if in shadow
	// 			// data->pix[i]->colour = data->pix[i]->ambient;
	// 	}
	// 	i++;
	// }
}
