/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/05 18:18:13 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// assign pixels to the position of the ray-vector 
t_vec3 init_ray_pos(double pos_x, double pos_y, double pos_z)
{
    t_vec3 vec;

    vec.x = pos_x;
    vec.y = pos_y;
    vec.z = pos_z;
    return (vec);
}

// it returns the normalizes_vectors
// Altough we need the ray-vector, we assign x,y,z the pixel_x-y-z -> init_ray_pos() as the ray-vector;
t_vec3 init_vector(t_screen screen)
{
    return (normalize_vector(init_ray_pos(screen.pixel_delta_x, screen.pixel_delta_y, -1)));
}

