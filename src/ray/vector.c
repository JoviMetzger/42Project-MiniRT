/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 22:38:08 by smclacke      ########   odam.nl         */
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

/* 'new' is calculated as a weighted sum of the components of the old_vector, 
 * with the weights determined by the corresponding elements of the matrix, 
 * plus an additional value multiplied by the appropriate element in the fourth column of the matrix.
 */
t_vec3  matrix_math(double *matrix, t_vec3 old)
{
    t_vec3 new;
    
    // new = (dot_product(old_vec * row_matrix) + 0 * fourth_element_of_matrix
    new.x = (old.x * matrix[0] + old.y * matrix[4] + old.z * matrix[8]) + 0 * matrix[12];   // the first row of the matrix.
	new.y = (old.x * matrix[1] + old.y * matrix[5] + old.z * matrix[9]) + 0 * matrix[13];   // the second row of the matrix.
	new.z = (old.x * matrix[2] + old.y * matrix[6] + old.z * matrix[10]) + 0 * matrix[14];  // the third row of the matrix.
	return (new);

}

t_vec3 init_vector(t_data *data, t_screen screen)
{
    // // ==== TESTING ========
    // t_vec3 testRay = init_ray_pos(screen.pixel_delata_x, screen.pixel_delata_y, 1);
    // printf ("TEST - init ray:\n----------------\nvec x: %f\nvec y: %f\nvec z: %f\n\n", testRay.x, testRay.y, testRay.z);

    // t_vec3 testMatrix = matrix_math(data->matrix, init_ray_pos(screen.pixel_delata_x, screen.pixel_delata_y, 1));
    // printf ("TEST - Matrix ray:\n----------------\nvec x: %f\nvec y: %f\nvec z: %f\n\n", testMatrix.x, testMatrix.y, testMatrix.z);

    // t_vec3 testPrinting = normalize_vector(matrix_math(data->matrix, init_ray_pos(screen.pixel_delata_x, screen.pixel_delata_y, 1)));
    // printf ("TEST - init vector:\n----------------\nvec x: %f\nvec y: %f\nvec z: %f\n\n", testPrinting.x, testPrinting.y, testPrinting.z);
    // exit(0);
    // // =====================

    // it returns the normalizes_vectors (scale it and assings a value to each vec3 (xyz)) of the 'matrix calculation';
    // the 'matrix calculation' takes the matrix and the ray-vector;
    // Altough we need the ray-vector we assign x,y,z the pixel_x-y-z -> init_ray_pos() as the ray-vector;
    // matrix-calculation calculates then the ray.
    return (normalize_vector(matrix_math(data->matrix, init_ray_pos(screen.pixel_delata_x, screen.pixel_delata_y, 1))));
}