/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 20:14:17 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/07 21:18:21 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

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
// check everything, if wrong, free arr and error
// then go through again and add info to data struct
// or is there a better way without too much messy leakage?
static void	parse_array(t_data *data, char **arr)
{
	(void)	data;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arr[i])
	{
		printf("[%i] - %s\n", i, arr[i]);
		// check identifier
		// check element count
		// check value format
		// anything wrong, free arr, error
		i++;
	}
	// reset | info good, now add to struct
	i = 0;
	// while arr, add elements to data struct
}

/**
 * @brief	reading through the file line by line, copying each
 * 			line into a 2D array of strings
 * 			if error occurs, array is freed, file is closed
 * 			error message and exit
 * 			else close file, call parse_array which adds everything
 * 			into t_data struct, then free array and return to main
*/
void	read_file(t_data *data, int file)
{
	char	*line;
	char	**arr;
	int		i;

	i = 0;
	line = get_next_line(file);
	arr = (char **)malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!arr)
		parse_error("malloc oopsie", file);
	while (line)
	{
		if (line)
		{
			arr[i] = ft_strdup(line);
			if (!arr[i])
			{
				// free_arr(arr); //  for anything that has already been made
				parse_error("malloc oopsie in while", file);
			}
			line = get_next_line(file);
			i++;
		}
	}
	close_protect(file);
	parse_array(data, arr);
	// free arr 
	// need to free line?
}
