/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 15:02:19 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/14 21:14:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

static void	init_colour(t_data *data)
{
	data->vars = (t_colour_vars *)malloc(sizeof(t_colour_vars));
	if (!data->vars)
		exit(42); // handle correly TODO
	ft_bzero(data->vars, sizeof(t_colour_vars));
	data->vars->ambient_ratio = data->ambient.ratio;
	data->vars->spec_intensity = 0.2;
	data->vars->spec_power = 32;
	data->vars->ambient.r = data->vars->ambient_ratio * data->ambient.colour.r;
	data->vars->ambient.g = data->vars->ambient_ratio * data->ambient.colour.g;
	data->vars->ambient.b = data->vars->ambient_ratio * data->ambient.colour.b;
	data->vars->result.r = data->vars->ambient.r;
	data->vars->result.g = data->vars->ambient.g;
	data->vars->result.b = data->vars->ambient.b;
}

/**
 * @brief	takes array of strings from read_file()
 * 			checks the elements and values are correct
 * 			converts from string to double/int etc..
 * 			adds them to the t_data struct
 * 			if something wrong, function will free, error and exit
 * 			will not return here if error
 * @brief	(check elements + validate_elems) 
 * 			while input is in string format, check it's validity
 * 			Ambient light, Light and Camera must be declared and only once
 * 			all other elements (sp, cy, pl) must be declared, poss multi
 * 			if error/invalid, free in check function, error and exit
 * 			number of arguments and characters checked before conversion
*/
static void	parse_array(t_data *data, char **arr)
{
	int			obj_count;
	int			light_count;

	check_elements(arr);
	obj_count = validate_elems(arr);
	light_count = count_light(arr);
	if (light_count == 0)
		free_arr_error("Can have between 1 and 4 light!", arr);
	convert_cap_input(data, arr, light_count);
	convert_obj_input(data, arr, obj_count);
	init_colour(data);
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
static void	read_file(t_data *data, int file)
{
	char	*line;
	char	**arr;
	int		i;

	i = 0;
	line = get_next_line(file);
	arr = rt_malloc(NULL, BUFF_SIZE, file);
	while (line && i < BUFF_SIZE)
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

static void	check_file_type(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (is_dot(arg[i]))
		{
			if (ft_strcmp(&arg[i], ".rt") == 0)
				return ;
			else
				error_msg("wrong file type");
		}
		i++;
	}
	error_msg("wrong file type");
}

void	parse_input(int argc, char **argv, t_data *data)
{
	int		file;

	file = 0;
	ft_bzero(data, sizeof(t_data));
	if (argc != 2)
		error_msg("wrong number of arguments");
	data->i_am = -1;
	check_file_type(argv[1]);
	file = open(argv[1], O_RDONLY, 0644);
	if (file == -1)
		error_msg("couldn't open file");
	read_file(data, file);
	init_mouse_map(data);
}
