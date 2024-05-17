/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:06:08 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/17 14:52:24 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

void init_LIGHTS(t_lightS *one, t_lightS *two, t_lightS *three)
{

	one->colour.r = 255;
	one->colour.g = 0;
	one->colour.b = 0;
	one->ratio = 0.7;
	one->place.x = 0;
	one->place.y = 0;
	one->place.z = -7;
	
	
	two->colour.r = 0;
	two->colour.g = 255;
	two->colour.b = 0;
	two->ratio = 0.7;
	two->place.x = -5;
	two->place.y = 0;
	two->place.z = -10;
		
	
	three->colour.r = 0;
	three->colour.g = 0;
	three->colour.b = 255;
	three->ratio = 0.7;
	three->place.x = 5;
	three->place.y = 0;
	three->place.z = -10;	

}

// 1. Calculate the ray from the “eye” through the pixel,	 -> ft_create_ray();
// 2. Determine which objects the ray intersects,			 -> ft_create_intersecttions();
// 3. Compute a color for the closest intersection point.	 -> ft_calculate_colour();
void ft_put_image(t_data *data)
{
	t_obj_data obj_data;
	uint32_t colour;
	int y = 0;
	int x = 0;

	// ---------------- RM ------------------------

	data->lightS = malloc(sizeof(t_lightS)); // Assuming t_light is the type of lightS elements
	if (data->lightS == NULL) 
		return ;
	
	t_lightS one;
	t_lightS two;
	t_lightS three;
	init_LIGHTS(&one, &two, &three);
	
	data->lightS[0] = &one;
	data->lightS[1] = &two;
	data->lightS[2] = &three;
	data->lights_i = 3;

	printf("ADDEDlight: %f %f %f - R: %f - C: %d %d %d\n", data->lightS[0]->place.x, data->lightS[0]->place.y, data->lightS[0]->place.z, data->lightS[0]->ratio, data->lightS[0]->colour.r, data->lightS[0]->colour.g, data->lightS[0]->colour.b);
	printf("ADDEDlight: %f %f %f - R: %f - C: %d %d %d\n", data->lightS[1]->place.x, data->lightS[1]->place.y, data->lightS[1]->place.z, data->lightS[1]->ratio, data->lightS[1]->colour.r, data->lightS[1]->colour.g, data->lightS[1]->colour.b);
	printf("ADDEDlight: %f %f %f - R: %f - C: %d %d %d\n", data->lightS[2]->place.x, data->lightS[2]->place.y, data->lightS[2]->place.z, data->lightS[2]->ratio, data->lightS[2]->colour.r, data->lightS[2]->colour.g, data->lightS[2]->colour.b);

	// --------------------------------------------
	
	while (y < data->mlx->height)
	{
		while (x < data->mlx->width)
		{ 
			data->mouse.mouse_map[y][x] = -1;
			data->ray = ft_create_ray(data, x ,y);		
			colour = ft_calculate_colour(data, &obj_data, data->ray);
			mlx_put_pixel(data->image, x, y, colour);
			data->mouse.mouse_x = x;
			x++;
		}
		data->mouse.mouse_y = y;
		x = 0;
		y++;
	}
	puts("DONE BITCHES!!!!");
}

void ft_render(t_data *data)
{

	ft_put_image(data); // Shazam(MATH)
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data); // movement aka ESC
    mlx_mouse_hook(data->mlx, ft_handle_mouse_click, data); // Mouse click event  
}
