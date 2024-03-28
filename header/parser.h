/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:29:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/19 15:53:01 by smclacke      ########   odam.nl         */
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

void		print_parser(t_data *data); // get rid later

// --- parse_input --- //
void		parse_input(int argc, char **argv, t_data *data);

// --- parser_error --- //
int			par_err(char *msg);
void		free_arr_error(char *msg, char **arr, t_elems *check);
void		free_close_parse_error(char *msg, char **ar, char *line, int file);
void		parse_error(char *msg, int file);
void 		error_msg(char *msg);

// --- parser_free --- //
void		free_array(char **arr);
void		free_close_util(char *line, int file);
void		close_protect(int file);

// --- parser_utils --- //
int			get_type(char *str);
char		**rt_malloc(char **arr, int size, int file);


// ----------- /check_elements/ ------------ //

// --- check_caps --- //
void		check_a(char **arr);
void		check_c(char **arr);
void		check_l(char **arr);

// --- check_elements --- //
void		check_elements(char **arr);

// --- check_utils --- //
int			check_pl(char *str);
int			check_sp(char *str);
int			check_cy(char *str);
void		check_dup(char **arr, int i, int type);
int			check_capital(char *str, int type);


// ----------- /convert/ ----------- //

// --- convert --- //
void		convert_input(t_data *data, char **arr);

// --- convert_caps --- //
int			sort_a(char **elem_str, t_data *data);
int			sort_l(char **elem_str, t_data *data);
int			sort_c(char **elem_str, t_data *data);

// --- convert_other --- //
int			sort_pl(char **elem_str, t_data *data);
int			sort_sp(char **elem_str, t_data *data);
int			sort_cy(char **elem_str, t_data *data);

// --- convert_nums --- //
int			is_coord(char *str, int i, int num_flag);
int			convert_coord(t_data *data, char *str);
int			is_ratio(char *str, int i, int num_flag, int dot_flag);
int			is_rgb(char *str, int i, int num_flag);
int			convert_rgb(t_data *data, char *str);

// --- convert_nums_2 --- //
int			convert_vector(t_data *data, char *str);
int			convert_fov(t_data *data, char *str);
int			convert_double(t_data *data, char *str, int flag, int type);


// --- /convert_utils/ --- //

// --- ft_atof --- //
double		ft_atof(char *str);

// --- add_info --- //
void		add_vec(t_data *data, double x, double y, double z);
void		add_coord(t_data *data, double x, double y, double z);
void		add_rgb(t_data *data, int r, int g, int b);

// --- add_coord --- //
void		coord_light(t_data *data, double x, double y, double z);
void		coord_camera(t_data *data, double x, double y, double z);
void		coord_pl(t_data *data, double x, double y, double z);
void		coord_sp(t_data *data, double x, double y, double z);
void		coord_cy(t_data *data, double x, double y, double z);

// --- add_vec --- //
void		vec_camera(t_data *data, double x, double y, double z);
void		vec_pl(t_data *data, double x, double y, double z);
void		vec_cy(t_data *data, double x, double y, double z);

// --- add_rgb --- //
void		rgb_cy(t_data *data, int r, int g, int b);
void		rgb_sp(t_data *data, int r, int g, int b);
void		rgb_pl(t_data *data, int r, int g, int b);
void		rgb_light(t_data *data, int r, int g, int b);
void		rgb_ambient(t_data *data, int r, int g, int b);

// --- convert_utils --- //
int			check_com(char *str, int i);
int			check_neg(char *str, int i);
int			coord_valid(int c);
int			ratio_valid(int c);
int			rgb_valid(int c);

// --- is_funcs --- //
int			is_valid(int c);
int			is_num(int c);
int			ft_isspace(int c);
int			is_comma(int c);
int			is_dot(int c);

// --- is_funcs_2 --- //
int			is_space(char *str);
int			valid_num(int c);
int			is_alpha(int c);
int			is_dash(int c);


// ------------ /validate/ ------------ //

// --- validate --- //
void		validate_elems(char **arr);

// --- valid_ratio --- //
int			is_valid_light(double light);
int			is_valid_rgb(int r, int g, int b);
int			is_valid_vector(double x, double y, double z);
int			is_valid_fov(int fov);

// --- validate_utils --- //
int			is_valid_no(char *str);
int			num_elems(char *str);
int			is_caps(char *str);
int			is_other(char *str);

#endif