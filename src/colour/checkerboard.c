/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkerboard.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/06 19:58:29 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"


// ------------------ for Sphere -> IS WORKING ----------------------------------------
t_colour get_sphere_checkerboard(t_vec3 normal)
{
    int			num_squares;
    t_colour	colour;
	bool		is_black;
	    
	num_squares = 10;
    double theta = atan2(normal.z, normal.x); 	// Angle in the x-z plane
    double phi = acos(normal.y);                // Angle from the positive y-axis
    
    // Normalize theta and phi to [0, 1]
    double u = (theta + M_PI) / (2 * M_PI); // Theta ranges from -pi to pi
    double v = phi / M_PI;                  // Phi ranges from 0 to pi
    
    // Scale coordinates by number of squares
    double square_u = u * num_squares;
    double square_v = v * num_squares;
    
    // Determine color based on checkerboard pattern
    is_black = ((int)floor(square_u) % 2 == (int)floor(square_v) % 2);
    
    if (is_black) 
	{
        colour.r = 0;
        colour.g = 0;
        colour.b = 0;
    } 
	else 
	{
        colour.r = 255;
        colour.g = 255;
        colour.b = 255;
    }
    
    return colour;
}

// ------------------ for Plane -> NOT WORKING ----------------------------------------
t_colour get_plane_checkerboard(t_objs *plane, t_vec3 normal)
{
    t_colour colour;
    bool is_black;

    // Generate two orthogonal vectors on the plane
    t_vec3 arbitrary = {1.0, 0.0, 0.0};
    if (fabs(plane->center.x) > 0.9) 
        arbitrary = (t_vec3){0.0, 1.0, 0.0};

    t_vec3 u = cross_product(normal, arbitrary);
    t_vec3 v = cross_product(normal, u);

    u = normalize(u);
    v = normalize(v);

    // Convert point_on_plane to the plane's local coordinates
	t_vec3 local_point = minus(plane->center, normal);
    double u_coord = dot_product(local_point, u);
    double v_coord = dot_product(local_point, v);

    // Scale coordinates by number of squares
    int num_squares = 10;
    double square_u = u_coord * num_squares;
    double square_v = v_coord * num_squares;

    // Determine color based on checkerboard pattern
    is_black = ((int)floor(square_u) % 2 == (int)floor(square_v) % 2);

	printf("u_coord: %f, v_coord: %f\n", u_coord, v_coord);
	printf("square_u: %f, square_v: %f\n", square_u, square_v);
	printf("is_black: %d\n", is_black);

    if (is_black)
    {
		printf("BLACK\n");
        colour.r = 0;
        colour.g = 0;
        colour.b = 0;
    }
    else
    {
		printf("WHITE\n");
        colour.r = 255;
        colour.g = 255;
        colour.b = 255;
    }

    return colour;
}

// t_colour get_plane_checkerboard(t_vec3 point_on_plane, t_objs *plane)
// {
//     t_colour colour;
//     bool is_black;

//     // Convert point_on_plane to the plane's local coordinates
//     double u_coord = dot_product(minus(point_on_plane, plane->center), plane->vector);
//     double v_coord = dot_product(minus(point_on_plane, plane->center), plane->vector);

//     // Scale coordinates by number of squares
//     int num_squares = 10;
//     double square_u = u_coord * num_squares;
//     double square_v = v_coord * num_squares;

//     // Determine color based on checkerboard pattern
//     is_black = ((int)floor(square_u) % 2 == (int)floor(square_v) % 2);

//     if (is_black)
//     {
// 		printf("HERE\n");
//         colour.r = 0;
//         colour.g = 255;
//         colour.b = 255;
//     }
//     else
//     {
// 		printf("Whsa\n");
//         colour.r = 255;
//         colour.g = 0;
//         colour.b = 0;
//     }

//     return colour;
// }

// ------------------ for Cylinder-> NOT WORKING ----------------------------------------
t_colour get_cylinder_checkerboard(t_vec3 normal)
{
	(void)normal;
    t_colour colour;
	    
	colour.r = 255;
	colour.g = 255;
	colour.b = 255;
    
    return colour;
}