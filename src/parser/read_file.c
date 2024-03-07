/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 20:14:17 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/07 21:24:11 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * @brief	takes array of strings from read_file()
 * 			checks the elements and values are correct
 * 			adds them to the t_data struct
 * 			if invalid, frees array, error message and exit
 * @todo	figure out approach, check error and memory handling, norm
*/
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
 * 			if error occurs, array is freed, file is closed,
 * 			error message and exit
 * 			else close file, call parse_array which adds everything
 * 			into t_data struct, then free array and return to main
 * @todo	freeing and norm
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
