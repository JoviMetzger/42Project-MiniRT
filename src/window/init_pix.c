/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pix.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/12 15:29:22 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/16 15:16:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"
#include "../../header/parser.h"

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
}

static void	set_pixels(t_data *data)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (i < data->total_pix)
	{
		while (y < data->height)
		{
			while (x < data->width)
			{
				data->mouse.mouse_map[y][x] = -1;
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
}

void	init_pix(t_data *data)
{
	data->height = HEIGHT;
	data->width = WIDTH;
	data->total_pix = data->height * data->width;
	data->pix_i = 0;
	data->pix = (t_pixel **)malloc(sizeof(t_pixel *) * (data->total_pix + 1));
	if (!data->pix)
	{
		free_objects(data);
		error_msg("malloc fail in init_pix");
	}
	while (data->pix_i < data->total_pix)
	{
		data->pix[data->pix_i] = (t_pixel *)malloc(sizeof(t_pixel));
		if (!data->pix[data->pix_i])
		{
			free_all(data);
			error_msg("malloc fail in init_pix");
		}
		ft_bzero(data->pix[data->pix_i], sizeof(t_pixel));
		data->pix_i++;
	}
	data->pix[data->pix_i] = NULL;
	set_pixels(data);
}
