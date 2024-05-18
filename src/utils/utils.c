/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/13 14:42:03 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Calculate the reflection direction using the incident ray direction and surface normal
// Reflection direction = Incident direction - 2 * (Incident direction . Normal) * Normal
t_vec3	ft_reflect(t_vec3 incident, t_vec3 normal)
{
	return minus(incident, mult_vecdub(normal, 2 * dot_product(incident, normal)));
}

int32_t	ft_convert_rgb(int32_t r, int32_t g, int32_t b)
{
	int32_t	a;

	a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}