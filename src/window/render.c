/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:06:08 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/29 15:00:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// 1. Calculate the ray from the “eye” through the pixel, -> ft_create_ray();
// 2. Determine which objects the ray intersects, and -> ft_create_intersects();
// 3. Compute a color for the closest intersection point. -> ft_calculate_colour();
void ft_put_image(t_data *data)
{
	t_ray ray;
	t_obj_data obj_data; // maybe we don't need this.
	// uint32_t colour;
	int y = 0;
	int x = 0;

	while (x < data->mlx->width)
	{
		while (y < data->mlx->height)
		{ 
			// 1. Calculate the ray from the “eye” through the pixel,
			ray = ft_create_ray(data, x ,y); // -> ft_create_lightray() is not working yet.
			// 2. Determine which objects the ray intersects, and
			// ft_create_intersection(data, &obj_data, ray); // -> still need to create
			
			// --- TEST FUNCTION ----
			// =============================================
			if (ft_create_intersection(data, &obj_data, ray))
                mlx_put_pixel(data->image, x, y, ft_pixel(10, 0, 255)); // Pixel is inside the sphere
            else
                mlx_put_pixel(data->image, x, y, ft_pixel(0, 0, 0)); // Pixel is outside the sphere
			// =============================================

			// // 3. Compute a color for the closest intersection point.
			// colour = ft_calculate_colour(data, &obj_data, ray); // -> still need to create
			// mlx_put_pixel(data->image, x, y, colour);
			y++;
		}
		y = 0;
		x++;
	}
}

void ft_render(t_data *data)
{
	// printf("i = %i\n", data->objs->i);
	// while (data->objs->i > 0)
	// {
	// 	printf("type = %i\n", data->objs->type);
	// 	data->objs->i--;
	// }
	// exit(EXIT_SUCCESS);
	ft_put_image(data); // Shazam(MATH)
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data); // movement aka ESC

}
