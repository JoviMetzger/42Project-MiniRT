/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:06:08 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/08 15:28:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"


// norminette NOT DONE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



/*	Bit shifts the ints rg,b, 
 *	so that the correct colour is displayed into mlx_put_pixel();
 */
int32_t	ft_convert_rgb(int32_t r, int32_t g, int32_t b)
{
	int32_t	a;

	a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}

// void ft_put_image(t_data *data)
// {
// 	uint32_t	colour;
// 	t_hit_data	hit;
// 	int			x = 0;
// 	int			y = 0;

// 	while (y < data->mlx->height)
// 	{
// 		while (x < data->mlx->width)
// 		{
// 			data->ray = ft_create_ray(data, x, y);
// 			colour = ft_calculate_colour(data, &hit, data->ray);
// 			mlx_put_pixel(data->image, x, y, colour);
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
// 	// puts("DONE");
// }


/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// ----------- REMOVE THIS ONCE IN THE PASER ------------------------------------------

// void init_LIGHTS(t_lightS *one, t_lightS *two, t_lightS *three)
// void init_LIGHTS(t_lightS *two)
// {
	
// 	two->colour.r = 255;
// 	two->colour.g = 255;
// 	two->colour.b = 255;
// 	two->ratio = 0.7;
// 	two->place.x = 5;
// 	two->place.y = 2;
// 	two->place.z = -10;		
		
// }

// void init_LIGHTS(t_lightS *one, t_lightS *two, t_lightS *three)
// {

// 	one->colour.r = 255;
// 	one->colour.g = 0;
// 	one->colour.b = 0;
// 	one->ratio = 0.7;
// 	one->place.x = 0;
// 	one->place.y = 0;
// 	one->place.z = -7;
	
	
// 	two->colour.r = 0;
// 	two->colour.g = 255;
// 	two->colour.b = 0;
// 	two->ratio = 0.7;
// 	two->place.x = -5;
// 	two->place.y = 0;
// 	two->place.z = -10;
		
	
// 	three->colour.r = 0;
// 	three->colour.g = 0;
// 	three->colour.b = 255;
// 	three->ratio = 0.7;
// 	three->place.x = 5;
// 	three->place.y = 0;
// 	three->place.z = -10;	

// }
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/*	This function is the main loop.
 *		- It loops through each pixel and takes these steps for each pixel.
 *		- STEPS:
 *			- 1. Calculate the ray from the “eye” through the pixel, 
 *				 -> ft_create_ray();
 *			- 2. Determine which objects the ray intersects,		 
 *				 -> ft_calculate_colour();
 *			- 3. Compute a color for the closest intersection point. 
 *				 -> get_colour();
 *		- It aswell updates all necessary varabils.  
 */
void	ft_put_image(t_data *data)
{
	t_hit_data	obj_hit;
	uint32_t	colour;
	int			y;
	int			x;

	// ---------------- RM ------------------------
	/* 
	-> NOTE FOR SARAH <-
	THIS 'RM' section leaks. It is for multiple lights, but that is something that needs to be added in the parseing part.
	So I just hard coded it for now, but I am not freeing it.
	On Monday I will expalin in person <3
	*/

	// data->lightS = malloc(sizeof(t_lightS)); // Assuming t_light is the type of lightS elements
	// if (data->lightS == NULL) 
	// 	return ;
	
	// t_lightS two;
	// // t_lightS one;
	// // t_lightS three;
	// // init_LIGHTS(&one, &two, &three);
	// init_LIGHTS(&two);
	
	// data->lightS[0] = &two;
	// // data->lightS[0] = &one;
	// // data->lightS[1] = &two;
	// // data->lightS[2] = &three;
	// data->lights_i = 1; // NOTE: have a max of 4 or 5 lights!

	// printf("ADDEDlight: %f %f %f - R: %f - C: %d %d %d\n", data->lightS[0]->place.x, data->lightS[0]->place.y, data->lightS[0]->place.z, data->lightS[0]->ratio, data->lightS[0]->colour.r, data->lightS[0]->colour.g, data->lightS[0]->colour.b);
	// printf("ADDEDlight: %f %f %f - R: %f - C: %d %d %d\n", data->lightS[1]->place.x, data->lightS[1]->place.y, data->lightS[1]->place.z, data->lightS[1]->ratio, data->lightS[1]->colour.r, data->lightS[1]->colour.g, data->lightS[1]->colour.b);
	// printf("ADDEDlight: %f %f %f - R: %f - C: %d %d %d\n", data->lightS[2]->place.x, data->lightS[2]->place.y, data->lightS[2]->place.z, data->lightS[2]->ratio, data->lightS[2]->colour.r, data->lightS[2]->colour.g, data->lightS[2]->colour.b);

	// --------------------------------------------

	y = 0;
	x = 0;
	while (y < data->mlx->height)
	{
		while (x < data->mlx->width)
		{
			data->mouse.mouse_map[y][x] = -1;
			data->ray = ft_create_ray(data, x ,y);
			colour = ft_calculate_colour(data, &obj_hit);
			mlx_put_pixel(data->image, x, y, colour);
			data->mouse.mou_x = x;
			x++;
		}
		data->mouse.mou_y = y;
		x = 0;
		y++;
	}
}

/*	In this function the Shazam is happening.
 *	- ft_put_image(); 	-> is the loop that goes pixel by pixel and shoots rays.
 *	- mlx_key_hook(); 	-> is for key movement (ESC, Arrow up).
 *	- mlx_mouse_hook(); -> is for mouse movement (selcet objects). 
 */
void	ft_render(t_data *data)
{
	ft_put_image(data);
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data);
	mlx_mouse_hook(data->mlx, ft_handle_mouse_click, data);
}
