/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/22 14:46:48 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/12 17:16:48 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// --- Libraries ---
# include "../libraries/libft/libft.h"
# include "../libraries/mlx42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <limits.h>

// --- Colours ---
# define BLACK "\033[30;1m"
# define WHITE "\033[37;1m"
# define RED "\033[31;1m"
# define BLUE "\033[34;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define RESET "\033[0m"

// Window
# define WIDTH 1200
# define HEIGHT 1500

// --- Math stuff ---
# define M_PI 3.14159265358979323846
# define EPSILON 0.000001
# define DBL_MAX 1.79769e+308

// --- Enum ---
// Element type enums, includes space for parser
typedef enum e_type
{
	E_AMBIENT = 1,
	E_LIGHT = 2,
	E_CAMERA = 3,
	E_PLANE = 4,
	E_SPHERE = 5,
	E_CYLINDER = 6,
	E_SPACE = 7,
	E_HASH = 8,
	E_TRIANGLE = 9
}	t_type;

// --- Structs ---
// -------------------------------------------------------------
// Vector - position - coordinates
//		x-axis (left-right)
//		y-axis (up-down)
//		z-axis (forward-back forwrd)
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;


// Colour - RGB
// 		r -> red
// 		g -> green
// 		b -> blue
typedef struct s_colour
{
	int		r;
	int		g;
	int		b;
}	t_colour;

// -------------------------------------------------------------
// Struct for camera
//		fov - field of view
typedef struct s_camera
{
	t_vec3		place;
	t_vec3		vector;
	int			fov;
}	t_camera;

// -------------------------------------------------------------
// Struct for ambient - constant light source (No spotlight)
typedef struct ambient
{
	t_colour	colour;
	double		ratio;
}	t_ambient;

typedef struct s_light
{
	t_colour	colour;
	t_vec3		place;
	double		ratio;
}	t_light;

// -------------------------------------------------------------
// Screen struct
typedef struct s_screen
{
	double		viewport_w;
	double		viewport_h;
	double		img_ratio;
	double		pixel_delta_x;
	double		pixel_delta_y;
}	t_screen;

// -------------------------------------------------------------
// Mouse movemnet struct
typedef struct s_mouse
{
	mlx_image_t		*highlight_img;
	int16_t			**mouse_map;
	uint32_t		window_h;
	uint32_t		window_w;
	int				mou_y;
	int				mou_x;
	bool			selected;
}	t_mouse;


// -------------------------------------------------------------
// Ray struct (standing alone)
typedef struct s_ray
{
	t_vec3	place;
	t_vec3	vector;
}	t_ray;

// -------------------------------------------------------------
// Struct for objects, each object has this struct
// array of structs in data struct
typedef struct s_objs
{
	t_type				type;
	double				obj_t;
	t_vec3				hit_pos;
	double				distance;
	t_colour			colour;
	t_vec3				center;
	t_vec3				vector;
	t_vec3				tmp_normal;
	t_vec3				normal;
	double				diameter;
	double				height;
	double				height_half;
	double				radius;
	t_vec3				top;
	t_vec3				base;
	t_vec3				edge[2];
	t_vec3				point[3];
	int					point_flag;
	mlx_texture_t		*texture;
	int16_t				i_am;	// what obj num this is, basicly ID	
	int					i;		// iterate through the different obj patterns (checkerboard, normal ...) -> resrets to 0 after 2 iterations.
	int					what_pattern; //what patten that object currently has.
}	t_objs;

// -------------------------------------------------------------
// Object data struct (standing alone)
// -> saves the calculations of the intersections
typedef struct s_hit_data
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec3	o_c;
	t_vec3	c_c;
	t_vec3	norm_vec;
	double	root1;
	double	root2;
	t_vec3	hit_pos;
	t_vec3	to_center;
	t_vec3	from_center;
	t_vec3	vector_cross;
	double	t;
	double	tmp_t;
	double	closest_t;
}	t_hit_data;

// -------------------------------------------------------------
// Struct for all colour variables (standing alone)
typedef struct s_colour_vars
{
	t_colour	result;
	t_light		*curr_light;
	t_vec3		intersect_p;
	t_vec3		normal;
	t_vec3		ref_dir;
	t_vec3		view_dir;
	t_vec3		light_dir;
	double		ambient_ratio;
	double		spec_intensity;
	double		spec_power;
	double		diff_fact;
	double		spec_fact;
	t_colour	ambient;
	t_colour	diffuse;
	t_colour	specular;
	t_colour	base;	
}	t_colour_vars;

typedef struct s_pixel
{
	// what do i need per pixel?
	// double	hit_t;
	// t_data	ray; // ?
	// light?
	
	uint32_t	colour;
	int			x;	
	int			y;	
}			t_pixel;


// -------------------------------------------------------------
// Main struct
typedef struct s_data
{
	t_colour_vars	vars;
	mlx_image_t		*image;
	mlx_t			*mlx;
	t_pixel			**pix;
	int				pix_i;
	int				total_pix;
	int				height;
	int				width;
	t_objs			**objs;
	t_hit_data		*hit_data;
	int				objs_i;
	t_camera		camera;
	t_ambient		ambient;
	int				light_i;
	t_light			**light;
	t_ray			ray;
	t_screen		screen;
	t_type			type;	// parser util which gets overwritten for each element, objects do have a type
	t_mouse			mouse;
	int16_t			i_am; // what object is currently seleted
}	t_data;

// -------------------------------------------------------------
// Struct for the checkerboard variables (standing alone)
typedef struct s_checkerboard
{
	double	theta;
	double	phi;
	double	u;
	double	v;
	double	square_u;
	double	square_v;
}	t_checkerboard;

// --- Functions --- 
// Window Functions
int			do_calcs(t_data *data);
void		init_pix(t_data *data);
void		ft_put_image(t_data *data);
void		ft_open_window(t_data *data);
void		ft_render(t_data *data);

// Movement Functions
void		ft_key_action(mlx_key_data_t keydata, t_data *data);
void		ft_handle_mouse_click(mouse_key_t key, action_t act,
				modifier_key_t m, void *_data);
void		init_mouse_map(t_data *data);

// Ray Functions
t_ray		ft_create_ray(t_data *data, int x, int y);

// Colour Functions
uint32_t	ft_calculate_colour(t_data *data, t_hit_data *obj);
void		add_light(t_colour_vars *colour, t_ray ray);
t_colour	get_colour(t_data *data, t_hit_data *obj_hit, t_objs *obj);
t_vec3		get_surface_normal(t_vec3 intersection_point, t_objs *obj);
t_colour	get_base_colour(t_objs *obj, t_colour_vars colour);
t_colour 	give_light(t_data *data);
bool		check_light(t_data *data, t_objs *obj, t_hit_data *hit);
// void		add_light(t_colour_vars *colour, t_ray ray);
// void		specular_light(t_colour_vars *colour, t_ray ray);
// void		diffuse_light(t_colour_vars *colour);
t_vec3		ft_reflect(t_vec3 incident, t_vec3 normal);
int32_t		ft_convert_rgb(int32_t r, int32_t g, int32_t b);

// Colour Functions Bonus
t_colour	get_sphere_checkerboard(t_vec3 normal);

// Operators
t_vec3		plus_vecdub(t_vec3 u, double v);
t_vec3		plus(t_vec3 u, t_vec3 v);
t_vec3		minus(t_vec3 u, t_vec3 v);
t_vec3		mult_vecvec(t_vec3 u, t_vec3 v);
t_vec3		mult_vecdub(t_vec3 v, double dub);
t_vec3		division_vec_dub(t_vec3 v, double dub);
t_vec3		division_vec_vec(t_vec3 u, t_vec3 v);
t_vec3		cross_product(t_vec3 u, t_vec3 v);
t_vec3		normalize(t_vec3 v);
double		dot_product(t_vec3 u, t_vec3 v);
double		length_squared(t_vec3 vec);
double		distance(t_vec3 pnt1, t_vec3 pnt2);
double		vec_length(t_vec3 v1, t_vec3 v2);
double		pythagoras(double a, double b);
double		vec_length(t_vec3 v1, t_vec3 v2);

// Objects Functions
bool		tap_top(t_hit_data *hit, t_objs *cyl, t_ray *ray);
bool		boop_bottom(t_hit_data *hit, t_objs *cyl, t_ray *ray);
void		cyl_normal(t_ray *ray, t_objs *cyl, t_hit_data *hit);
bool		cut_ends_hit_bod(t_hit_data *hit, t_objs *cyl, t_ray *ray);
void		set_points(t_hit_data *hit, t_ray *ray, t_objs *cyl);
bool		bodyody(t_hit_data *hit, t_objs *cyl, t_ray *ray);
bool		intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *hit);
bool		intersect_cyl_plane(t_ray *ray, t_objs *plane, t_hit_data *hit);
bool		intersect_plane(t_ray *ray, t_objs *plane, t_hit_data *hit);
bool		intersect_sphere(t_ray *ray, t_objs *sphere, t_hit_data *hit);
bool		intersect_triangle(t_ray *ray, t_objs *tri, t_hit_data *hit);
bool		check_closest(t_hit_data *hit);
bool		quadratic(t_hit_data *hit);

#endif
