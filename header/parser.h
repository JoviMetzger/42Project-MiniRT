/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:29:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/12 20:21:28 by smclacke      ########   odam.nl         */
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

// --- parser_error --- //
void		free_arr_error(char *msg, char **arr, t_elems *check);
void		free_close_parse_error(char *msg, char **ar, char *line, int file);
void		parse_error(char *msg, int file);
void 		error_msg2(char *msg);

// --- parser_utils --- //
int			is_num(int c);
int			ft_isspace(int c);
int			is_comma(int c);
int			is_dot(int c);
char		**rt_malloc(char **arr, int size, int file);

// --- free_utils --- //
void		free_array(char **arr);
void		free_close_util(char *line, int file);
void		close_protect(int file);


// ----------- /check_elements/ ------------ //

// --- check_caps --- //
void		check_a(char **arr);
void		check_c(char **arr);
void		check_l(char **arr);

// --- check_utils --- //
int			check_pl(char *str);
int			check_sp(char *str);
int			check_cy(char *str);
void		check_dup(char **arr, int i, int type);
int			check_capital(char *str, int type);

// --- check_elements --- //
void		check_elements(char **arr);


// ------------ /validate/ ------------ //

// --- validate --- //
void		validate_elems(char **arr);

// --- validate_utils --- //
int			is_alpha(int c);
int			is_valid_no(char *str);
int			num_elems(char *str);
int			is_caps(char *str);
int			is_other(char *str);


// ----------- /convert/ ----------- //

// --- convert --- //
void		convert_input(t_data *data, char **arr);

// --- validate_caps --- //
int			validate_a(char *str);
int			validate_c(char *str);
int			validate_l(char *str);

// --- validate_other --- //
int			validate_sp(char *str);
int			validate_cy(char *str);
int			validate_pl(char *str);

// --- valid_nums --- //
int			is_rbg(char *str);
int			is_light(char *str);

// --- valid_nums_2 --- //


#endif
