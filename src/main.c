/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/19 19:30:26 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"
#include "../header/miniRT.h"

void	free_all(t_data *data)
{
	free_objects(data);
	free_light(data);
	free_pixels(data);
}

/* main function:
 *		- 1. parse_input(); takes the '.rt' file and checks and parses 
 *			 the input correctly into the structs.
 *		- 2. init_pix(); The whole shazam is happening in here.
 *			 Calculates all pixels. 3 Main steps happen in here.
 *		     - STEPS:
 *		     	- 1. Calculate the ray from the “eye” through the pixel, 
 *		     		 -> ft_create_ray();
 *		     	- 2. Determine which objects the ray intersects,		 
 *		     		 -> ft_calculate_colour();
 *		     	- 3. Compute a color for the closest intersection point. 
 *		     		 -> get_colour(); 
 *		- 3. ft_open_window(); Initializes the window/MlX.
 *		- 4. ft_render(); Prints the pixels.
 *		- 5. mlx_loop(); Runs the loop, so that the window stays open.	
 *		- 6. mlx_terminate(); Terminate the window/MLX once done using.
 *		- 7. free_all(); Cleans up the structs that got allcoated.
 */
int	main(int argc, char **argv)
{
	t_data	data;

	parse_input(argc, argv, &data);
	printf("Loading...\n");
	init_pix(&data);
	do_calcs(&data);
	ft_open_window(&data);
	ft_render(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_all(&data);
	return (EXIT_SUCCESS);
}
