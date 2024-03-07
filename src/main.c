/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/07 19:29:54 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/miniRT.h"

int main(int argc, char **argv)
{
    t_data data;

	if (!ft_parse_input(argc, argv, &data)) // Check file Input & supstract the values to the struct.
	{
		// clean up needed? - or if fails when reading file, free what
		// was made and just error out
		return (EXIT_FAILURE);
	}

	// ft_open_window(&data); // Open window
	// ft_render(&data); // the whole shazam!

	// mlx_loop(data.mlx);		// loop
	// mlx_terminate(data.mlx); // terminate
	return (EXIT_SUCCESS);
}
