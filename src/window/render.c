/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:06:08 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/12 17:16:01 by smclacke      ########   odam.nl         */
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

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// ----------- REMOVE THIS ONCE IN THE PASER ------------------------------------------

// void init_light(t_light *one, t_light *two, t_light *three)
// void init_light(t_light *two)
// {
	
// 	two->colour.r = 255;
// 	two->colour.g = 255;
// 	two->colour.b = 255;
// 	two->ratio = 0.7;
// 	two->place.x = 5;
// 	two->place.y = 2;
// 	two->place.z = -10;		
		
// }

// void init_light(t_light *one, t_light *two, t_light *three)
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


	// ---------------- RM ------------------------
	/* 
	-> NOTE FOR SARAH <-
	THIS 'RM' section leaks. It is for multiple light, but that is something that needs to be added in the parseing part.
	So I just hard coded it for now, but I am not freeing it.
	On Monday I will expalin in person <3
	*/

	// data->light = malloc(sizeof(t_light)); // Assuming t_light is the type of light elements
	// if (data->light == NULL) 
	// 	return ;
	
	// t_light two;
	// // t_light one;
	// // t_light three;
	// // init_light(&one, &two, &three);
	// init_light(&two);
	
	// data->light[0] = &two;
	// // data->light[0] = &one;
	// // data->light[1] = &two;
	// // data->light[2] = &three;
	// data->light_i = 1; // NOTE: have a max of 4 or 5 light!

	// printf("ADDEDlight: %f %f %f - R: %f - C: %d %d %d\n", data->light[0]->place.x, data->light[0]->place.y, data->light[0]->place.z, data->light[0]->ratio, data->light[0]->colour.r, data->light[0]->colour.g, data->light[0]->colour.b);
	// printf("ADDEDlight: %f %f %f - R: %f - C: %d %d %d\n", data->light[1]->place.x, data->light[1]->place.y, data->light[1]->place.z, data->light[1]->ratio, data->light[1]->colour.r, data->light[1]->colour.g, data->light[1]->colour.b);
	// printf("ADDEDlight: %f %f %f - R: %f - C: %d %d %d\n", data->light[2]->place.x, data->light[2]->place.y, data->light[2]->place.z, data->light[2]->ratio, data->light[2]->colour.r, data->light[2]->colour.g, data->light[2]->colour.b);

	// --------------------------------------------



/////////////////////////////////////////////////////////////////////////////////////////

// OG PUT IMAGE
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
// void	ft_put_image(t_data *data)
// {
// 	t_hit_data	obj_hit;
// 	uint32_t	colour;
// 	int			y;
// 	int			x;

// 	y = 0;
// 	x = 0;
// 	while (y < data->mlx->height)
// 	{
// 		while (x < data->mlx->width)
// 		{
// 			data->mouse.mouse_map[y][x] = -1;
// 			data->ray = ft_create_ray(data, x ,y);
// 			colour = ft_calculate_colour(data, &obj_hit); // move to a loop where pixels are saved, give put func the pixels here
// 			mlx_put_pixel(data->image, x, y, colour);
// 			data->mouse.mou_x = x;
// 			x++;
// 		}
// 		data->mouse.mou_y = y;
// 		x = 0;
// 		y++;
// 	}
// }

// POSSIBLE PUT IMAGE
// new put image if pixels already pre calculated
void	ft_put_image(t_data *data)
{
	data->pix_i = 0;
	while (data->pix_i < data->total_pix)
	{
		data->mouse.mouse_map[data->pix[data->pix_i]->y][data->pix[data->pix_i]->x] = -1;
		mlx_put_pixel(data->image, data->pix[data->pix_i]->x, data->pix[data->pix_i]->y, data->pix[data->pix_i]->colour);
		data->mouse.mou_x = data->pix[data->pix_i]->x;
		data->pix_i++;
	}
	// puts("DONEE");
}

// static void	check_pix(t_data *data)
// {
// 	int p = 0;

// 	while (p < data->total_pix)
// 	{
// 	 	printf("pix[%i] = %i %i  ", p, data->pix[p]->x, data->pix[p]->y);
// 		printf("pix colour = %d\n", data->pix[p]->colour);
// 		p++;
// 	}
// }


/*	In this function the Shazam is happening.
 *	- ft_put_image(); 	-> is the loop that goes pixel by pixel and shoots rays.
 *	- mlx_key_hook(); 	-> is for key movement (ESC, Arrow up).
 *	- mlx_mouse_hook(); -> is for mouse movement (selcet objects). 
 */
void	ft_render(t_data *data)
{
	// check_pix(data);
	// exit(0);
	ft_put_image(data);
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data);
	mlx_mouse_hook(data->mlx, ft_handle_mouse_click, data);
}
