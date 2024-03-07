/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 20:14:17 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/07 20:32:00 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// parse_array(t_data *data)

	// after creating array/list
		// find identifier
		// check correct elements (number of, value type, range)
		// add to structs
		// repeat till end of file
		// if not all needs are met, free what has been created, error
		// * error messages:
		// * 	missing element
		// * 	wrong element
		// * 	missing value
		// * 	value out of range


/**
	// read through
	// save into some array/list, then parse the array!! ---> in t_data!!
	// if something fails here, use parse_error and close file
*/
void	read_file(t_data *data, int file)
{
	char	*line;
	(void)	data;

	line = get_next_line(file);
	while (line)
	{
		if (line)
		{
			printf("-> %s\n", line);
			line = get_next_line(file);
			// add line to array in data struct
			// if fails, parser_error(msg, file)
		}
	}
	close_protect(file);
}
