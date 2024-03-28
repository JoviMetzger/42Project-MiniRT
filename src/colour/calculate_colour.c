/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/28 17:18:21 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// 
int32_t ft_convert_rgb(int32_t r, int32_t g, int32_t b)
{
	int32_t a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}

// t_colour get_ambient(t_colour colour, double ratio)
// {
	
// }

/* lighting: 
 *	(https://learnopengl.com/Advanced-Lighting/Advanced-Lighting)
 *	(https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model)
 *	(https://en.wikipedia.org/wiki/Phong_reflection_model)
 */
uint32_t ft_calculate_colour(t_data *data, t_obj_data *obj_data, t_ray ray)
{
	(void)ray;
	(void)data;
	// printf("\n--- OBJ ---\na: %f\nb: %f\nc: %f\nd: %f\nroot1: %f\nroot2: %f\nt: %f\n", obj_data->a, obj_data->b, obj_data->c, obj_data->d, obj_data->root1, obj_data->root2, obj_data->t);


	// t_ray lightray;
	// t_colour	colour;
	// t_colour	ambient;

	// // ft_create_lightray(data, obj_data, &lightray);
	// ambient = get_ambient(data->ambient.colour, data->ambient.ratio);
	
	if (obj_data->d >= 0.0)
		return (ft_convert_rgb(10, 0, 255)); // Pixel is inside the sphere
	else
		return (ft_convert_rgb(0, 0, 0)); // Pixel is outside the sphere
}
