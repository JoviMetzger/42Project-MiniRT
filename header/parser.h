/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:29:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 16:56:50 by smclacke      ########   odam.nl         */
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

// --- check_caps_a --- //
void		check_caps_a(char **arr);
// --- check_caps_c --- //
void		check_caps_c(char **arr);
// --- check_caps_l --- //
void		check_caps_l(char **arr);

// --- check_input --- //


// --- parser_error --- //
void		free_arr_error(char *msg, char **arr);
void		free_close_parse_error(char *msg, char **ar, char *line, int file);
void		parse_error(char *msg, int file);
void 		error_msg2(char *msg);

// --- parser_utils --- //
int			ft_isspace(int c);
int			is_dot(int c);
char		**rt_malloc(char **arr, int size, int file);

// --- free_utils --- //
void		free_array(char **arr);
void		free_close_util(char *line, int file);
void		close_protect(int file);

#endif
