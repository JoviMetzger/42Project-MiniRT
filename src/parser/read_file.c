/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 20:14:17 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 17:00:47 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

/**
 * @brief	while input is in string format, check it's validity
 * 			Ambient light, Light and Camera must be declared and only once
 * 			all other elements (sp, cy, pl) must have correct values
 * 			if error/invalid, free in check function, error and exit
*/
static void	check_input(char **arr)
{
	check_elements(arr);
	validate_elems(arr);
}

/**
 * @brief	convert validated string data into double/int etc
 * 			during AND after conversion, check converted info again:
 * 			check - ratio, format, etc but in converted form now not string
 * @note	probabaly just convert and add to structs ...
*/
static void	convert_input(t_data *data, char **arr)
{
	(void) arr;
	(void) data;

	// convert_elems(t_data *data, char **arr);
	// convert + add as we goo
	// check again all info is valid, ratio, format...
	return ;
}

/**
 * @brief	takes array of strings from read_file()
 * 			checks the elements and values are correct
 * 			converts from string to double/int etc..
 * 			adds them to the t_data struct
 * 			if something wrong, function will free, error and exit
 * 			willnot return here if error
*/
static void	parse_array(t_data *data, char **arr)
{
	check_input(arr);
	convert_input(data, arr);
}

/**
 * @brief	read through the file line by line, copying each
 * 			line into a 2D array of strings (arr)
 * 			if error occurs, array and line is freed, file is closed,
 * 			error message and exit
 * 			else close file, call parse_array which checks input, converts it
 * 			and adds everything into t_data struct, 
 * 			then frees array and line and returns to main to continue
 * 			rt_malloc is protected :)
*/
void	read_file(t_data *data, int file)
{
	char	*line;
	char	**arr;
	int		i;

	i = 0;
	line = get_next_line(file);
	arr = rt_malloc(NULL, BUFF_SIZE, file);
	while (line)
	{
		if (line)
		{
			arr[i] = ft_strdup(line);
			if (!arr[i])
				free_close_parse_error("malloc failure", arr, line, file);
			free(line);
			line = get_next_line(file);
			i++;
		}
	}
	arr[i] = NULL;
	free_close_util(line, file);
	parse_array(data, arr);
	free_array(arr);
}
