/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/28 12:28:48 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"
#include "../header/miniRT.h"

// main function:
int main(int argc, char **argv)
{
    t_data data;

	parse_input(argc, argv, &data);

	ft_open_window(&data); // Open window
	ft_render(&data); // the whole shazam!

	mlx_loop(data.mlx);		// loop
	mlx_terminate(data.mlx); // terminate

	free(data.objs);

	return (EXIT_SUCCESS);
}
