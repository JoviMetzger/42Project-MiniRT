/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 20:14:17 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 16:23:48 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

/**
 * @brief	while input is in string format, check it's validity
 * 			Ambient light, Light and Camera must be declared and only once
 * 			all other elements (sp, cy, pl) must have correct values
 * 			if error/invalid, free in check function, error and exit
*/
// static void	check_input(char **arr)
// {
// 	check_caps(arr);
// 	// check_cap_vals(arr);
// 	// check_other(arr);
// 	// check_invalid(arr);
// }

// /**
//  * @brief	convert validated string data into double/int etc
// */
// static void	convert_input(char **arr)
// {
// 	(void)	arr;
// 	return ;
// }

// /**
//  * @brief	add converted and validated input into t_data struct
// */
// static void	add_input(t_data *data, char **arr)
// {
// 	(void)	arr;
// 	(void)	data;
// 	// init data (?)
// 	return ;
// }

// /**
//  * @brief	takes array of strings from read_file()
//  * 			checks the elements and values are correct
//  * 			converts from string to double/int etc..
//  * 			adds them to the t_data struct
//  * 			if something wrong, function will free, error and exit
//  * 			willnot return here if error
// */
// static void	parse_array(t_data *data, char **arr)
// {
// 	check_input(arr);
// 	convert_input(arr);
// 	add_input(data, arr);
// }

// if still necessary for testing :)
// static	void	print_array(char **arr)
// {
// 	int		i = 0;

// 	while (arr[i])
// 	{
// 		printf("[%i] %s\n", i, arr[i]);
// 		i++;
// 	}
// }

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
	(void)	data;

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
	// print_array(arr);
	// parse_array(data, arr);
	free_array(arr);
}
