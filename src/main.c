/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/25 15:40:31 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"
#include "../header/miniRT.h"

int main(int argc, char **argv)
{
    t_data data;

	parse_input(argc, argv, &data);

	print_parser(&data);
	
	// needs to be part of the clean up
	free(data.objs);
	// ft_open_window(&data); // Open window
	// ft_render(&data); // the whole shazam!

	// mlx_loop(data.mlx);		// loop
	// mlx_terminate(data.mlx); // terminate

	return (EXIT_SUCCESS);
}
