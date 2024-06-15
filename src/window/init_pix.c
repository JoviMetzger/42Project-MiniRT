/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pix.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/12 15:29:22 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/15 16:28:01 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"
#include "../../header/parser.h"

void	do_calcs(t_data *data)
{
	t_hit_data	hit;
	uint32_t	ambient_colour;
	// uint32_t	light;
	t_colour	light;
	int 		i;

	// get initial hits
	i = 0;
	while (i < data->total_pix)
	{
		data->ray = ft_create_ray(data, data->pix[i]->x, data->pix[i]->y);
		data->pix[i]->ray = data->ray;
		ambient_colour = ft_calculate_colour(data, &hit, i);
		data->pix[i]->ambient_colour = ambient_colour;
		data->pix[i]->colour = ambient_colour;
		data->mouse.mou_y = data->pix[i]->y;
		data->mouse.mou_x = data->pix[i]->x;
		data->pix[i]->hit_t = hit.t;
		// data->pix[i]->light_ray.place = plus(data->vars->intersect_p, mult_vecdub(data->vars->normal, EPSILON));
		data->pix[i]->light_ray.place = data->light[0]->place;
		data->pix[i]->light_ray.vector = normalize(minus(data->pix[i]->light_ray.place, data->vars->intersect_p));
		// data->pix[i]->inter_p = data->vars->intersect_p;
		// data->pix[i]->light_dir = data->vars->light_dir;
		i++;
	}
	// get direct light
	i = 0;
	// create light
	while (i < data->total_pix)
	{
		if (in_light(data, &hit, i))
		{
			data->vars->curr_light = data->light[0]; // while loop for more lights
			// printf("light_place: %f %f %f\n", data->pix[i]->light_ray.place.x, data->pix[i]->light_ray.place.y, data->pix[i]->light_ray.place.z);
			// printf("light_vector: %f %f %f\n", data->pix[i]->light_ray.vector.x, data->pix[i]->light_ray.vector.y, data->pix[i]->light_ray.vector.z);
			// // printf("inter point; %f %f %f\n", data->pix[i]->inter_p.x, data->pix[i]->inter_p.y, data->pix[i]->inter_p.z);
			// printf("original_ray place: %f %f %f\n", data->pix[i]->ray.place.x, data->pix[i]->ray.place.y, data->pix[i]->ray.place.z);
			// printf("original_ray vector: %f %f %f\n", data->pix[i]->ray.vector.x, data->pix[i]->ray.vector.y, data->pix[i]->ray.vector.z);
			// printf("original inter point; %f %f %f\n", data->vars->intersect_p.x, data->vars->intersect_p.y, data->vars->intersect_p.z);
			// exit(0);
			light = give_light(data, i);
			data->pix[i]->colour = ft_convert_rgb(light.r, light.g, light.b);
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
