/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 15:02:19 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/07 19:49:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

static int		check_file_type(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (is_dot(arg[i]))
		{
			if (ft_strcmp(&arg[i], ".rt") == 0)
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

// read_file()
// {
	// read through
	// find identifier
	// check correct elements (number of, value type, range)
	// add to structs
	// repeat till end of file
	// if not all needs are met, free what has been created, error, return
// }

int ft_parse_input(int argc, char **argv, t_data *data)
{
	(void)	argc;
	(void)	argv;
	(void)	data;
	int		file;

	if (argc != 2)
		return (printf("Wrong number of arguments\n"), 0);
	if (!check_file_type(argv[1]))
		return (printf("wrong file type\n"), 0);
	file = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file == -1)
		return (printf("couldn't open file\n"), 0); 

	// if (!read_file(data, file))
		// return (printf("couldn't parse file\n"), 0);

	if (close(file) == -1)
		return (printf("closing file errored...\n"), 0);
	return (1);
}
