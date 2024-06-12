/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pix.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/12 15:29:22 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/12 15:40:14 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

static int	do_calcs(t_data *data)
{
	// t_hit_data	obj_hit;
	// uint32_t	colour;

	data->pix_i = 0; // start at first pixel again
	
	// data->pix[data->pix_i]->x = 0;	// everything already bezeroed
	// data->pix[data->pix_i]->y = 0;
	while (data->pix[data->pix_i]->y < data->height)
	{
		while (data->pix[data->pix_i]->x < data->width)
		{
			// data->ray = ft_create_ray(data, data->pix[data->pix_i]->x, data->pix[data->pix_i]->y);
			// colour = ft_calculate_colour(data, &obj_hit);
			// data->pix[data->pix_i]->colour = colour;
			// printf("pix x = %i\n", data->pix[data->pix_i]->x);
			data->pix_i++;
			data->pix[data->pix_i]->x++;
		}
		// printf("pix y = %i\n", data->pix[data->pix_i]->y);
		data->pix_i++;
		data->pix[data->pix_i]->y++;
	}
	// exit(0);
	return (0);
}


	// printf("total = %i\n", total_pix);
	// printf("height = %i\n", data->height);
	// printf("width = %i\n", data->width);
	// exit(0);
void	init_pix(t_data *data)
{
	data->height = data->mlx->height;
	data->width = data->mlx->width;
	int			total_pix = data->height * data->width; // do this in init area with malloc
	
	data->pix_i = 0;
	data->pix = (t_pixel **)malloc(sizeof(t_pixel *) * (total_pix + 1));
	if (!data->pix)
		return ; // add pixel error, msg + free everything
	
	while (data->pix_i < total_pix)
	{
		data->pix[data->pix_i] = (t_pixel *)malloc(sizeof(t_pixel));
		if (!data->pix[data->pix_i])
			return ;  // add pixel error, msg + free everything
		ft_bzero(data->pix[data->pix_i], sizeof(t_pixel));
		data->pix_i++;
	}
	exit(0);
	do_calcs(data);
}
