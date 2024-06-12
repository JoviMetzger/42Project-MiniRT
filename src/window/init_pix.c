/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pix.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/12 15:29:22 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/12 17:04:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

int	do_calcs(t_data *data)
{
	t_hit_data	obj_hit;
	uint32_t	colour;
	int i = 0;

	while (i < data->total_pix)
	{
		data->ray = ft_create_ray(data, data->pix[i]->x, data->pix[i]->y);
		colour = ft_calculate_colour(data, &obj_hit);
		data->pix[i]->colour = colour;
		// hit_per_pix ... WE COULD DO ANYTHING HEHEHEH
		i++;
	}

	
	// int p = 0;
	// while (p < data->total_pix)
	// {
	// 	printf("pix colour = %d\n", data->pix[p]->colour);
	// 	p++;
	// }
	
	// exit(0);
	return (0);
}

static void	set_pixels(t_data *data)
{
	int i = 0;
	int x = 0;
	int j = 0;
	int y = 0;
	while (i < data->total_pix)
	{
		while (y < data->height)
		{
			while (x < data->width)
			{
				data->pix[j]->y = y;
				data->pix[j]->x = x;
				x++;
				j++;
			}
			x = 0;
			y++;
		}
		i = j;
	}

	// int	p = 0;
	// while (p < data->total_pix)
	// {
	// 	printf("pix[%i] = %i %i \n", p, data->pix[p]->x, data->pix[p]->y);
	// 	p++;
	// }
}

void	init_pix(t_data *data)
{
	data->height = HEIGHT;
	data->width = WIDTH;
	data->total_pix = data->height * data->width;
	data->pix_i = 0;
	data->pix = (t_pixel **)malloc(sizeof(t_pixel *) * (data->total_pix + 1));
	if (!data->pix)
		return ; // add pixel error, msg + free everything
	while (data->pix_i < data->total_pix)
	{
		data->pix[data->pix_i] = (t_pixel *)malloc(sizeof(t_pixel));
		if (!data->pix[data->pix_i])
			return ;  // add pixel error, msg + free everything
		ft_bzero(data->pix[data->pix_i], sizeof(t_pixel));
		data->pix_i++;
	}
	set_pixels(data);
	do_calcs(data);
}
