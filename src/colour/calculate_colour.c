/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/04 20:54:57 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

//
t_vec3 ft_reflect(t_vec3 incident, t_vec3 normal) 
{
    // Calculate the reflection direction using the incident ray direction and surface normal
    // Reflection direction = Incident direction - 2 * (Incident direction . Normal) * Normal
    return minus(incident, mult_vecdub(normal, 2 * dot_product(incident, normal)));
}

// 
int32_t ft_convert_rgb(int32_t r, int32_t g, int32_t b)
{
	int32_t a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}

/* lighting: 
 *	(https://learnopengl.com/Advanced-Lighting/Advanced-Lighting)
 *	(https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model)
 *	(https://en.wikipedia.org/wiki/Phong_reflection_model)
 */
uint32_t ft_calculate_colour(t_data *data, t_obj_data *obj_data, t_ray ray)
{
	t_colour	colour;
	int		i = 0;

	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_PLANE)
		{
			if (intersect_plane(&ray, data->objs[i], obj_data))
			{
				colour = get_plane_colour(data, obj_data, ray, data->objs[i]);
				return (ft_convert_rgb(colour.r, colour.g, colour.b));
			}
		}
		else if (data->objs[i]->type == E_SPHERE)
		{
			if (intersect_sphere(&ray, data->objs[i], obj_data))
			{
				colour = get_sphere_colour(data, obj_data, ray, data->objs[i]);
				return (ft_convert_rgb(colour.r, colour.g, colour.b));
			}
		}
		else if (data->objs[i]->type == E_CYLINDER)
		{
			if (intersect_norm_cylinder(&ray, data->objs[i], obj_data))
			{
				colour = get_cylinder_colour(data, obj_data, ray, data->objs[i]);
				return (ft_convert_rgb(colour.r, colour.g, colour.b));
			}
			// if (intersect_infi_cylinder(&ray, data->objs[i], obj_data))
			// {
			// 	colour = get_cylinder_colour(data, obj_data, ray, data->objs[i]);
			// 	return (ft_convert_rgb(colour.r, colour.g, colour.b));
			// }
		}
		i++;

	}
	return (ft_convert_rgb(0, 0, 0));
}
