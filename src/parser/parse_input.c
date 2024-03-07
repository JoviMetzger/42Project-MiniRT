/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 15:02:19 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/07 15:29:59 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// int ft_parse_input(int argc, char **argv, t_data *data)
// {
// 	(void)	argc;
// 	(void)	argv;
// 	(void)	data;
	
// 	// if (argc != 2)
// 	// {
// 	// 	printf("Wrong number of arguments\n");
// 	// 	return (0);
// 	// }
// 	// if (argv[1]) != .rt file, error
// 	// read .rt file...
// 	return (1);
// }

void ft_parse_input(int argc, char **argv, t_data *data)
{
    (void)argc;
    (void)argv;

    // check_file() // Check valid input and put everything in the struct.
    data->viewport_H = 600;
    data->viewport_W = 800;

    // Ambient lightning (A): 
    data->ambient.ratio = 0.2;
    data->ambient.colour.r = 255;
    data->ambient.colour.g = 255;
    data->ambient.colour.b = 255;

    // Camera (C): 
    data->camera.place.x = -50.0;
    data->camera.place.y = 0;
    data->camera.place.z = 20;
    data->camera.vector.x = 0;
    data->camera.vector.y = 0;
    data->camera.vector.z = 1;
    data->camera.FOV = 70;

    // Light (L):
    data->light.place.x = -40.0;
    data->light.place.y = 50.0;
    data->light.place.z = 0.0;
    data->light.ratio = 0.6;
    data->light.colour.r = 10;
    data->light.colour.g = 0;
    data->light.colour.b = 255;

    // Sphere (sp):
    data->objects.sphere.center.x = 0.0;
    data->objects.sphere.center.y = 0.0;
    data->objects.sphere.center.z = 20.6;
    data->objects.sphere.diameter = 12.6;
    data->objects.sphere.colour.r = 10;
    data->objects.sphere.colour.g = 0;
    data->objects.sphere.colour.b = 255;
    // printf("\nHERE\n\n");
    // printf("Sphere: %f\n", data->objects.sphere.center.x);
    // printf("Sphere: %f\n", data->objects.sphere.center.y);
    // printf("Sphere: %f\n", data->objects.sphere.center.z);
    // printf("Sphere: %f\n", data->objects.sphere.diameter);
    // printf("Sphere: %f\n", data->objects.sphere.colour.r);
    // printf("Sphere: %f\n", data->objects.sphere.colour.g);
    // printf("Sphere: %f\n", data->objects.sphere.colour.b);


    // Plane (pl): 
    data->objects.plane.center.x = 0.0;
    data->objects.plane.center.y = 0.0;
    data->objects.plane.center.z = -10.0;
    data->objects.plane.vector.x = 0.0;
    data->objects.plane.vector.y = 1.0;
    data->objects.plane.vector.z = 0.0;    
    data->objects.plane.colour.r = 0;
    data->objects.plane.colour.g = 0;
    data->objects.plane.colour.b = 255;

    // Cylinder (cy):
    data->objects.cylinder.center.x = 50.0;
    data->objects.cylinder.center.y = 0.0;
    data->objects.cylinder.center.z = 20.6;
    data->objects.cylinder.vector.x = 0.0;
    data->objects.cylinder.vector.y = 0.0;
    data->objects.cylinder.vector.z = 1.0;
    data->objects.cylinder.diameter = 14.2;
    data->objects.cylinder.height = 21.42;
    data->objects.cylinder.colour.r = 10;
    data->objects.cylinder.colour.g = 0;
    data->objects.cylinder.colour.b = 255;
}