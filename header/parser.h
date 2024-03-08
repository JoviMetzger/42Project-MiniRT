/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:29:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 15:54:55 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PARSER_H
# define PARSER_H

# include "miniRT.h"
# include <sys/stat.h>
# include <fcntl.h>

# ifndef BUFF_SIZE
#  define BUFF_SIZE 100
# endif

# define A 1
# define L 2
# define C 3
# define pl 4
# define sp 5
# define cy 6

// --- parse_input --- //
void		parse_input(int argc, char **argv, t_data *data);

// --- read_file --- //
void		read_file(t_data *data, int file);

// --- check_caps --- //
void		check_caps(char **arr);

// --- check_input --- //


// --- parser_error --- //
void		close_protect(int file);
void		free_array(char **arr);
void		free_close_parse_error(char *msg, char **ar, char *line, int file);
void		parse_error(char *msg, int file);
void 		error_msg2(char *msg);

// --- parser_utils --- //
int			ft_isspace(int c);
int			is_dot(int c);
void		free_close_util(char *line, int file);
char		**rt_malloc(char **arr, int size, int file);

#endif
