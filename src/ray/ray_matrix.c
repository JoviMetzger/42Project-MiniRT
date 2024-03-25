/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_matrix.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/25 17:17:33 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// --> SORRY FOR ALL THE COMMENTS <---
// --> I LOVE ALL THE COMMENTS <---

/*
 * - each column represents a coordinate axis (x, y, z, w)
 * - each row represents a transformation operation (translation, rotation, scaling, etc.)
 * 
 *            .x  .y  .z  .w
 *          | 00  01  02  03 | 
 *          | 04  05  06  07 |
 *      ->  | 08  09  10  11 | <-  --- transformation and scaling applied to the z-axis.
 *          | 12  13  14  15 |
 */
t_vec3 compute_forward(double *matrix, t_ray ray_start_point)
{
    matrix[8] = ray_start_point.vector.x;
    matrix[9] = ray_start_point.vector.y;
    matrix[10] = ray_start_point.vector.z;
    matrix[11] = 0;

    return (ray_start_point.vector);
}


/*
 * - each column represents a coordinate axis (x, y, z, w)
 * - each row represents a transformation operation (translation, rotation, scaling, etc.)
 * 
 *            .x  .y  .z  .w
 *      ->  | 00  01  02  03 | <-  --- transformation and scaling applied to the x-axis.
 *          | 04  05  06  07 |
 *          | 08  09  10  11 |
 *          | 12  13  14  15 |
 */
// 0.707 helps in making the condition less sensitive to slight variations while still capturing the general intent of the code, which is to detect when the forward vector is not primarily pointing vertically.
t_vec3 compute_right(double *matrix, t_vec3 forward)
{
    t_vec3 right;
    t_vec3 tmp;

    // setting tmp to default values
    tmp.x = 0;
    tmp.y = 1;
    tmp.z = 0; 

    // The y component represents the vertical direction in a standard 3D coordinate system.
    if (fabs(forward.y) == 1)
    {
        // If y is  exactly 1 or -1, it implies that the forward direction is almost purely vertical.
        tmp.z = -forward.y;
        tmp.y = 0;
    }
    else if (fabs(forward.y) > 0.707) // threshold value 0.707 is chosen because it corresponds to the sine and cosine of approximately 45 degrees in a unit circle. 
    {
        // is greater than 0.707 (approximately 45 degrees from the vertical), the forward direction is not purely vertical. 
        // In this case, the right vector may need to be adjusted to ensure it's perpendicular to both the forward vector and the upward direction. 
        tmp.x = 1;
        if (forward.y < 0)
            tmp.x = -1;
        tmp.y = 0;
    }
    right = cross_product(tmp, forward);
    matrix[0] = right.x;
    matrix[1] = right.y;
    matrix[2] = right.z;
    matrix[3] = 0;

    return (right);
}


/*
 * - each column represents a coordinate axis (x, y, z, w)
 * - each row represents a transformation operation (translation, rotation, scaling, etc.)
 * 
 *            .x  .y  .z  .w
 *          | 00  01  02  03 | 
 *      ->  | 04  05  06  07 | <-  --- transformation and scaling applied to the y-axis.
 *          | 08  09  10  11 |
 *          | 12  13  14  15 |
 */
void compute_up(double *matrix, t_vec3 forward, t_vec3 right)
{
    t_vec3 up;
    up = cross_product(forward, right);
    matrix[4] = up.x;
    matrix[5] = up.y;
    matrix[6] = up.z;
    matrix[7] = 0;
}


/*
 * - each column represents a coordinate axis (x, y, z, w)
 * - each row represents a transformation operation (translation, rotation, scaling, etc.)
 * 
 *            .x  .y  .z  .w
 *          | 00  01  02  03 | 
 *          | 04  05  06  07 |
 *          | 08  09  10  11 |
 *      ->  | 12  13  14  15 | <-  --- represent the translation components.
 */
void translation_components(double *matrix, t_ray ray)
{
    matrix[12] = ray.place.x;
    matrix[13] = ray.place.y;
    matrix[14] = ray.place.z;
    matrix[15] = 1;
}


// Using a 4x4 matrix 
// (https://semath.info/src/determinant-four-by-four.html)
// (https://byjus.com/maths/determinant-of-4x4-matrix/)
// (https://www.vedantu.com/maths/determinant-of-4x4-matrix)
// (https://www.superprof.co.uk/resources/academic/maths/linear-algebra/determinants/4x4-determinant.html)
// (https://testbook.com/maths/determinant-of-4x4-matrix)
/*
 *  | m11  m12  m13  m14 |       | 01  02  03  04 |      | 00  01  02  03 |    
 *  | m21  m22  m23  m24 |  ->   | 05  06  07  08 |  ->  | 04  05  06  07 |
 *  | m31  m32  m33  m34 |       | 09  10  11  12 |      | 08  09  10  11 |
 *  | m41  m42  m43  m44 |       | 13  14  15  16 |      | 12  13  14  15 |
 *      - example -                - array[16] -           - positions -
 * 
 *  In the context of computer graphics and transformations, each row of the matrix often represents a transformation operation (translation, rotation, scaling, etc.), while each column represents a coordinate axis (x, y, z, w).
 *  
 *  m11, m12, m13, m14: These elements typically represent the transformation and scaling applied to the x-axis.
 *  m21, m22, m23, m24: These elements represent the transformation and scaling applied to the y-axis.
 *  m31, m32, m33, m34: These elements represent the transformation and scaling applied to the z-axis.
 *  m41, m42, m43, m44: These elements represent the translation components.
 *  
 *  The elements along the diagonal from the top-left to the bottom-right (m11, m22, m33, m44) are often referred to as the "main diagonal" or simply the "diagonal" of the matrix.
 *  
 *  In 3D graphics, the fourth column (m14, m24, m34) and fourth row (m41, m42, m43) are often used for translation components. The fourth row is usually [0 0 0 1], where the last element, m44, is set to 1.
 *  
 */
void create_matrix(double *matrix, t_ray ray_start_point)
{
    t_vec3  forward;
    t_vec3  right;

    // computes the forward direction vector of a ray and stores its components in the specified matrix.
    forward = compute_forward(matrix, ray_start_point); // Returns the forward vector.
    // computes the right direction vector based on the forward vector and stores the components of the right vector in the specified matrix.
    right = compute_right(matrix, forward); //  Returns the right vector.
    // computes the up direction vector based on the forward and right vectors and stores the components of the up vector in the specified matrix.
    compute_up(matrix, forward, right); 
    translation_components(matrix, ray_start_point);


}

void store_ray_matrix(t_data *data)
{
    // first need camera 'eye' so we know from where we are shooting the rays.
    t_ray ray_start_point;
    ray_start_point.place = data->camera.place;
    ray_start_point.vector = data->camera.vector;
    create_matrix(data->matrix, ray_start_point);
    
    // printf("------ First Row:\n%f\n%f\n%f\n%f\n------ second Row:\n%f\n%f\n%f\n%f\n------ Third Row:\n%f\n%f\n%f\n%f\n------ Fourth Row:\n%f\n%f\n%f\n%f\n------\n\n\n", data->matrix[0], data->matrix[1], data->matrix[2], data->matrix[3], data->matrix[4], data->matrix[5], data->matrix[6], data->matrix[7], data->matrix[8], data->matrix[9], data->matrix[10], data->matrix[11], data->matrix[12], data->matrix[13], data->matrix[14], data->matrix[15]);
}