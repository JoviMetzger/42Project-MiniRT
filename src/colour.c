/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 16:05:24 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/miniRT.h"

// Might or might not need the function
int32_t ft_pixel(int32_t r, int32_t g, int32_t b)
{
	int32_t a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}


uint32_t ft_calculate_colour(t_data *data, t_obj_data *obj_data, t_ray ray)
{
	(void)data;
	(void)obj_data;
	(void)ray;
    return (ft_pixel(10, 0, 255));
}