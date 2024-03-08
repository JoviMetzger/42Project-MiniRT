/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 16:27:41 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"
#include "../header/miniRT.h"

int main(int argc, char **argv)
{
    t_data data;

	parse_input(argc, argv, &data); // if we return, all input is in t_data :)

	// ft_open_window(&data); // Open window
	// ft_render(&data); // the whole shazam!

	// mlx_loop(data.mlx);		// loop
	// mlx_terminate(data.mlx); // terminate

	return (EXIT_SUCCESS);
}
