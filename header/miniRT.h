/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 14:43:34 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/11 16:39:52 by smclacke      ########   odam.nl         */
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
# include <float.h> // apparently invalid by norm
# include <math.h>

// --- Colours ---
# define BLACK "\033[30;1m"
# define WHITE "\033[37;1m"
# define RED "\033[31;1m"
# define BLUE "\033[34;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define RESET "\033[0m"

// Window
# define WIDTH 1920
# define HEIGHT 1080

// Math stuff
// This is a constant representing the value of pi.
# define M_PI 3.14159265358979323846
# define EPSILON 0.000001

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
}				t_type;

// --- Structs ---
// -------------------------------------------------------------
// Vector - position - coordinates
typedef struct s_vec3
{
	double	x; // x-axis (left-right)
	double	y; // y-axis (up-down)
	double	z; // z-axis (forward-back forwrd)  
}	t_vec3;

// -------------------------------------------------------------
// For getting colour purposes..
typedef	struct s_colour_vars
{
	double		ambient_intensity;
	double		diffuse_intensity;
	double		spec_intensity;
	double		spec_power;
	t_vec3		inter_point; // intersect_point
	t_vec3		normal;
	double		ambient_red;
	double		ambient_green;
	double		ambient_blue;
	double		diffuse_red;
	double		diffuse_green;
	double		diffuse_blue;
	t_vec3		light_dir;
	double		diffuse_factor;
	t_vec3		view_dir;
	t_vec3		reflection_dir;
	double		spec_factor;
	double		spec_red;
	double		spec_green;
	double		spec_blue;
	double		final_red;
	double		final_green;
	double		final_blue;
	
}			t_colour_vars;

// -------------------------------------------------------------
// Colour - RGB
typedef struct s_colour
{
	int		r; // redfov
	int		g; // green
	int		b; // blue
}	t_colour;

// -------------------------------------------------------------
// Struct for objects, each object has this struct
// array of structs in data struct
typedef struct s_objs
{
	t_type				type;
	t_colour			colour;
	t_vec3				center;
	t_vec3				point1;
	t_vec3				point2;
	t_vec3				point3;
	int					point_flag;
	t_vec3				vector;
	double				diameter;
	double				height;
	mlx_texture_t		*texture;
	// mlx_image_t			*text_img;
}	t_objs;

// -------------------------------------------------------------
// Struct for camera
typedef struct s_camera
{
	t_vec3		place;
	t_vec3		vector;
	int			fov; //field of view
}	t_camera;

// -------------------------------------------------------------
// Struct for ambient - background
typedef struct ambient
{
	t_colour	colour;
	double		ratio;
}	t_ambient;

// -------------------------------------------------------------
// Struct for light
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
    int16_t		**mouse_map;
	int 		mouse_y;
	int			mouse_x;
	uint32_t	window_h;
	uint32_t	window_w;
}   t_mouse;

// -------------------------------------------------------------
// Main struct
typedef struct s_data
{
	mlx_image_t	*image;
	mlx_t		*mlx;
	t_objs		**objs;
	int			objs_i;
	t_camera	camera;
	t_ambient	ambient;
	t_light		light;
	t_screen	screen;
	t_type		type;		// parser util which gets overwritten for each element, objects do have a type
	t_mouse		mouse;
}	t_data;

// -------------------------------------------------------------
// Ray struct (standing alone)
typedef struct s_ray
{
	t_vec3	place;
	t_vec3	vector;
}	t_ray;

// -------------------------------------------------------------
// Object data struct (standing alone)
// -> saves the calculations of the intersections
typedef struct s_obj_data
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	root1;
	double	root2;
	double	t;
	double	tmp_t;
	double	height_half;
	double	hit1;
	double	hit2;
	double	radius;
	double	closest_t;

}	t_obj_data;

// --- Functions --- 
// Window Functions
void		ft_put_image(t_data *data);
void		ft_open_window(t_data *data);
void		ft_render(t_data *data);

// Movement Functions
void ft_key_action(mlx_key_data_t keydata, t_data *data);
void ft_handle_mouse_click(mouse_key_t btn, action_t act, modifier_key_t m, void *p);
void init_mouse_map(t_data *data);

// Ray Functions
t_ray		ft_create_ray(t_data *data, int x, int y);
void		store_ray_matrix(t_data *data);
void		ft_create_lightray(t_data *data, t_ray *lightray);

// Colour Functions
uint32_t	ft_calculate_colour(t_data *data, t_obj_data *obj, t_ray ray);
t_colour	get_colour(t_data *data, t_obj_data *obj_data,
				t_ray ray, t_objs *cylinder);
t_vec3		ft_reflect(t_vec3 incident, t_vec3 normal);
int32_t		ft_convert_rgb(int32_t r, int32_t g, int32_t b);

// Colour Functions Bonus
t_colour get_sphere_checkerboard(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere);
t_colour get_sphere_bumpmap(t_data *data, t_obj_data *obj_data, t_ray ray, t_objs *sphere);

// Vector Functions
t_vec3		init_vector(t_screen screen);

// Operators
t_vec3 		plus_vecdub(t_vec3 u, double v);
t_vec3		plus(t_vec3 u, t_vec3 v);
t_vec3		minus(t_vec3 u, t_vec3 v);
t_vec3		mult_vecvec(t_vec3 u, t_vec3 v);
t_vec3		mult_vecdub(t_vec3 v, double dub);
t_vec3		division_vec_dub(t_vec3 v, double dub);
t_vec3		division_vec_vec(t_vec3 u, t_vec3 v); // might remove this
t_vec3		cross_product(t_vec3 u, t_vec3 v);
double		dot_product(t_vec3 u, t_vec3 v);
double		length_squared(t_vec3 vec);
t_vec3		normalize_vector(t_vec3 v);
double		distance(t_vec3 pnt1, t_vec3 pnt2);

// Objects Functions
bool		check_closest(t_obj_data *obj_data);
bool		quadratic(t_obj_data *obj_data);
bool		check_roots(t_obj_data *obj, t_objs *cyl, t_ray *ray);
bool		intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj_data);
bool		intersect_plane(t_ray *ray, t_objs *plane, t_obj_data *obj_data);
bool		intersect_sphere(t_ray *ray, t_objs *sphere, t_obj_data *obj_data);
bool		intersect_triangle(t_ray *ray, t_objs *tri, t_obj_data *obj_data);


#endif