/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 21:46:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"
#include "../header/miniRT.h"

int main(int argc, char **argv)
{
    t_data data;

	parse_input(argc, argv, &data);

	printf("\tA\n");
	printf("A ratio = %f\n", data.ambient.ratio);
	printf("A rgb = %i %i %i\n\n", data.ambient.colour.r, data.ambient.colour.g, data.ambient.colour.b);
	printf("----------------------------------\n");
	printf("\tC\n");
	printf("C coords = %f %f %f\n\n", data.camera.place.x, data.camera.place.y, data.camera.place.z);
	printf("----------------------------------\n");
	printf("\tL\n");
	printf("L ratio = %f\n", data.light.ratio);
	printf("L rgb = %i %i %i\n", data.light.colour.r, data.light.colour.g, data.light.colour.b);
	printf("L coords = %f %f %f\n\n", data.light.place.x, data.light.place.y, data.light.place.z);
	printf("----------------------------------\n");
	printf("\tsp\n");
	printf("sp rgb = %i %i %i\n\n", data.objects.sphere.colour.r, data.objects.sphere.colour.g, data.objects.sphere.colour.b);
	printf("----------------------------------\n");
	printf("\tpl\n");
	printf("pl rgb = %i %i %i\n\n", data.objects.plane.colour.r, data.objects.plane.colour.g, data.objects.plane.colour.b);
	printf("----------------------------------\n");
	printf("\tcy\n");
	printf("cy rgb = %i %i %i\n\n", data.objects.cylinder.colour.r, data.objects.cylinder.colour.g, data.objects.cylinder.colour.b);
	// ft_open_window(&data); // Open window
	// ft_render(&data); // the whole shazam!

	// mlx_loop(data.mlx);		// loop
	// mlx_terminate(data.mlx); // terminate

	return (EXIT_SUCCESS);
}
