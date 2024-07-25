/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 16:33:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/13 22:24:16 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

t_colour give_light(t_data *data, t_objs *obj, t_hit_data *hit) 
{
	(void)obj;
	(void)hit;
	add_light(&data->vars, data->ray); //
	// add_light(&data->vars, data->ray, data, obj, data->hit_data);
    data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
    data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
    data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));
    return (data->vars.result);
}

// This function has shadow
bool intersect_objects(t_data *data, t_ray *ray, t_hit_data *hit) 
{
    // Iterate over all objects and check for intersections
    // Return true if an intersection is found
    // This is a placeholder for the actual intersection logic
    int i = 0;
	while (i < data->objs_i) 
	{ 
        if (intersect_sphere(ray, data->objs[i], hit)
			|| intersect_plane(ray, data->objs[i], hit)
			|| intersect_cylinder(ray, data->objs[i], hit)
			|| intersect_triangle(ray, data->objs[i], hit))
		{
            return true;
        }
		i++;
    }
    return false;
}

// // ------------ test ---------------
// // has no shadow
// bool intersect_objects(t_data *data, t_ray *ray, t_hit_data *hit) 
// {
// 	(void)hit;
//     t_hit_data temp_hit;
//     bool hit_found = false;
    
//     for (int i = 0; i < data->objs_i; i++) 
// 	{
//         if (data->objs[i]->type == E_SPHERE) 
// 		{
//             if (intersect_sphere(ray, data->objs[i], &temp_hit)) 
// 			{
//                 hit_found = true;
//             }
//         }
// 		else if (data->objs[i]->type == E_PLANE) 
// 		{
//             if (intersect_plane(ray, data->objs[i], &temp_hit)) 
// 			{
//                 hit_found = true;
//             }
//         }
// 		else if (data->objs[i]->type == E_CYLINDER)
// 		{
//             if (intersect_cylinder(ray, data->objs[i], &temp_hit))
// 			{
//                 hit_found = true;
//             }
//         }
//     }
    
//     return hit_found;
// }

// ---------------------------------------

bool check_light(t_data *data, t_objs *obj, t_hit_data *hit) 
{
    t_ray shadow_ray;

    shadow_ray.place = plus(data->vars.intersect_p, mult_vecdub(obj->normal, EPSILON));
    shadow_ray.vector = data->vars.light_dir;

    // Function that checks for intersections with all objects
    if (intersect_objects(data, &shadow_ray, hit)) 
	{
        return false; // In shadow
    }
    return true; // No intersection, not in shadow
}


