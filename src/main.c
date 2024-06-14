/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/14 13:48:20 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"
#include "../header/miniRT.h"

void	free_all(t_data *data)
{
	free_objects(data);
	free_pixels(data);
}

// main function:
//		- 1. parse_input(); takes the '.rt' file and checks and parses 
//			 the input correctly into the structs.
//		- 2. ft_open_window(); Initializes the window/MlX.
//		- 3. ft_render(); The whole shazam is happening in here.
//		- 4. mlx_loop(); Runs the loop, so that the window stays open.	
//		- 5. mlx_terminate(); Terminate the window/MLX once done using.
//		- 6. free_objects(); Cleans up the structs that got allcoated.
int	main(int argc, char **argv)
{
	t_data	data;

	parse_input(argc, argv, &data);
	init_pix(&data);
	do_calcs(&data);
	ft_open_window(&data);
	ft_render(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_all(&data);
	return (EXIT_SUCCESS);
}
