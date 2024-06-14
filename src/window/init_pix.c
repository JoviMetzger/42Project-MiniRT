/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pix.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/12 15:29:22 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/14 20:18:34 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"
#include "../../header/parser.h"

void	free_pixels(t_data *data)
{
	int	i;

	i = 0;
	if (data->pix && data->pix[i])
	{
		while (data->pix[i])
		{
			free(data->pix[i]);
			i++;
		}
	}
	free(data->pix);
}

void	do_calcs(t_data *data)
{
	t_hit_data	hit;
	uint32_t	ambient_colour;
	uint32_t	light;
	int 		i;

	i = 0;
	while (i < data->total_pix)
	{
		data->ray = ft_create_ray(data, data->pix[i]->x, data->pix[i]->y);
		data->pix[i]->ray = data->ray;
		ambient_colour = ft_calculate_colour(data, &hit, i);
		data->pix[i]->colour = ambient_colour;
		data->pix[i]->hit_t = hit.t;
		i++;
	}
	i = 0;
	while (i < data->total_pix)
	{
		data->ray = data->pix[i]->ray;
		if (in_light(data, &hit, i) == true)
		{	
			light = get_light(data);
			data->pix[i]->colour = light;
		}
		i++;
	}
}

static void	set_pixels(t_data *data)
{
	int i;
	int x;
	int j;
	int y;

	i = 0;
	x = 0;
	j = 0;
	y = 0;
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
	set_pixels(data);
}
