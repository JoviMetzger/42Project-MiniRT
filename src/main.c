/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/15 18:15:20 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"
#include "../header/miniRT.h"

int main(int argc, char **argv)
{
    t_data data;

	parse_input(argc, argv, &data);

	printf("L = %i | %i | %i\n", data.light.colour.r, data.light.colour.g, data.light.colour.b);
	printf("A = %i | %i | %i\n", data.ambient.colour.r, data.ambient.colour.g, data.ambient.colour.b);
	printf("sp = %i | %i | %i\n", data.objects.sphere.colour.r, data.objects.sphere.colour.g, data.objects.sphere.colour.b);
	printf("pl = %i | %i | %i\n", data.objects.plane.colour.r, data.objects.plane.colour.g, data.objects.plane.colour.b);
	printf("cy = %i | %i | %i\n", data.objects.cylinder.colour.r, data.objects.cylinder.colour.g, data.objects.cylinder.colour.b);
	// ft_open_window(&data); // Open window
	// ft_render(&data); // the whole shazam!

	// mlx_loop(data.mlx);		// loop
	// mlx_terminate(data.mlx); // terminate

	return (EXIT_SUCCESS);
}
