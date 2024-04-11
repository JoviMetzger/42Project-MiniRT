/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/11 15:52:58 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Calculate the reflection direction using the incident ray direction and surface normal
// Reflection direction = Incident direction - 2 * (Incident direction . Normal) * Normal
t_vec3 ft_reflect(t_vec3 incident, t_vec3 normal) 
{
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
	// printf("\n--- OBJ ---\na: %f\nb: %f\nc: %f\nd: %f\nroot1: %f\nroot2: %f\nt: %f\n", obj_data->a, obj_data->b, obj_data->c, obj_data->d, obj_data->root1, obj_data->root2, obj_data->t);
	// printf("TYPE: %f %f %f\n", data->objs->center.x, data->objs->center.y, data->objs->center.z);

	t_colour	colour;
	int		i = 0;
	double closest_t = DBL_MAX; // Initialize closest intersection distance to a large value

	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_SPHERE)
		{
			if (intersect_sphere(&ray, data->objs[i], obj_data))
			{
				// Check if the intersection point is closer than previous intersections
                if (obj_data->t < closest_t)
                {
                    closest_t = obj_data->t; // Update closest intersection distance
					// colour = get_sphere_colour(data, obj_data, ray, data->objs[i]);
					colour = get_sphere_checherboard(data, obj_data, ray, data->objs[i]);	// will be moved
					// colour = get_sphere_bumpmap(data, obj_data, ray, data->objs[i]);	// will be moved
                }
			}
		}
		// else if (data->objs[i]->type == E_PLANE)
		// {
		// 	if (obj_data->t < closest_t)
        //     {
        //         closest_t = obj_data->t;
		// 		colour = get_plane_colour(data, obj_data, ray, data->objs[i]);
		// 	}
		// }
		// else if (data->objs[i]->type == E_CYLINDER)
		// {
		// 	if (obj_data->t < closest_t)
        //     {
        //         closest_t = obj_data->t;
		// 		colour = get_cylinder_colour(data, obj_data, ray, data->objs[i]);
		// 	}
		// }
		i++;

	}
	if (closest_t != DBL_MAX)
        return (ft_convert_rgb(colour.r, colour.g, colour.b));
    else
        return (ft_convert_rgb(0, 0, 0)); // No intersection found, return black
}
