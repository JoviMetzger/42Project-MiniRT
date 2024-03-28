/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:06:08 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/28 15:17:24 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// 1. Calculate the ray from the “eye” through the pixel,	 -> ft_create_ray();
// 2. Determine which objects the ray intersects,			 -> ft_create_intersecttions();
// 3. Compute a color for the closest intersection point.	 -> ft_calculate_colour();
void ft_put_image(t_data *data)
{
	t_ray ray;
	t_obj_data obj_data; // maybe we don't need this. -> can add "a,b,c,d,root1,root2,t" in obj struct
	uint32_t colour;
	int y = 0;
	int x = 0;

	while (x < data->mlx->width)
	{
		while (y < data->mlx->height)
		{ 
			ray = ft_create_ray(data, x ,y);
			ft_create_intersection(data, &obj_data, ray);			
			colour = ft_calculate_colour(data, &obj_data, ray); // eVerYTinG iN heRE iS jUSt ME gOiNg "hhhUUUUUhhhhhh?????????????" -> aka. cat meme (https://www.youtube.com/watch?v=xVWeRnStdSA)
			mlx_put_pixel(data->image, x, y, colour);
			y++;
		}
		y = 0;
		x++;
	}
}

void ft_render(t_data *data)
{
	ft_put_image(data); // Shazam(MATH)
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data); // movement aka ESC

}
