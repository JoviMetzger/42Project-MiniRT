/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/06 15:24:56 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"
#include "../header/miniRT.h"

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
	ft_open_window(&data);
	ft_render(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_objects(&data);
	return (EXIT_SUCCESS);
}
