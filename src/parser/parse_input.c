/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 15:02:19 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/07 21:14:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

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
				error_msg("Wrong file type");
		}
		i++;
	}
	error_msg("Wrong file type");
}

void	parse_input(int argc, char **argv, t_data *data)
{
	int		file;

	file = 0;
	if (argc != 2)
		error_msg("Wrong number of arguments");
	check_file_type(argv[1]);
	file = open(argv[1], O_RDONLY, 0644);
	if (file == -1)
		error_msg("Couldn't open file");
	read_file(data, file);
}
