/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 22:38:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"
#include "../header/miniRT.h"

// =========== RM ===================
void RM_parse_input(int argc, char **argv, t_data *data)
{
    (void)argc;
    (void)argv;

	data->total_obj_num = 1;
    // Ambient lightning (A): 
    data->ambient.ratio = 0.2;
    data->ambient.colour.r = 255;
    data->ambient.colour.g = 255;
    data->ambient.colour.b = 255;

    // Camera (C): 
    data->camera.place.x = 0; // -50.0;
    data->camera.place.y = 0;
    data->camera.place.z = 0; //20;
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
    data->objects.sphere.center.z = -5.0; //20.6;
    data->objects.sphere.diameter = 2; //12.6;
    data->objects.sphere.colour.r = 10;
    data->objects.sphere.colour.g = 0;
    data->objects.sphere.colour.b = 255;

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
// ===============================================

// main function:
int main(int argc, char **argv)
{
    t_data data;

	// parse_input(argc, argv, &data);

	RM_parse_input(argc, argv, &data);
	
	ft_open_window(&data); // Open window
	ft_render(&data); // the whole shazam!

	mlx_loop(data.mlx);		// loop
	mlx_terminate(data.mlx); // terminate

	return (EXIT_SUCCESS);
}
