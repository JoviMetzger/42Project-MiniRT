/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/27 13:36:01 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Might or might not need the function
int32_t ft_pixel(int32_t r, int32_t g, int32_t b)
{
	int32_t a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}


uint32_t ft_calculate_colour(t_data *data, t_obj_data *obj_data, t_ray ray)
{
	(void)data;
	(void)ray;
	
	if (obj_data->d >= 0.0)
	{
		// printf("\n--- YES ---\na: %f\nb: %f\nc: %f\nd: %f\nroot1: %f\nroot2: %f\nt: %f\n", obj_data->a, obj_data->b, obj_data->c, obj_data->d, obj_data->root1, obj_data->root2, obj_data->t);
		return (ft_pixel(10, 0, 255)); // Pixel is inside the sphere
	}
	else
	{
		// printf("\n--- NO ---\na: %f\nb: %f\nc: %f\nd: %f\nroot1: %f\nroot2: %f\nt: %f\n", obj_data->a, obj_data->b, obj_data->c, obj_data->d, obj_data->root1, obj_data->root2, obj_data->t);
		return (ft_pixel(0, 0, 0)); // Pixel is outside the sphere
	}
	
}