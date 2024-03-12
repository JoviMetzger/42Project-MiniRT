/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:29:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 16:46:00 by smclacke      ########   odam.nl         */
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

typedef struct s_elems
{
	bool	sp_b;
	bool	pl_b;
	bool	cy_b;
}		t_elems;

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
// --- check_utils --- //
int			check_a(char *str);
int			check_c(char *str);
int			check_l(char *str);
int			check_sp(char *str);
int			check_cy(char *str);

// --- check_elements --- //
void		check_elements(char **arr);

// --- validate --- //

// --- convert --- //

// --- parser_error --- //
void		free_arr_error(char *msg, char **arr, t_elems *check);
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
