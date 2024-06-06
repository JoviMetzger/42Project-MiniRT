/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 14:43:34 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/06 21:29:38 by jmetzger      ########   odam.nl         */
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

// --- Colours ---
# define BLACK "\033[30;1m"
# define WHITE "\033[37;1m"
# define RED "\033[31;1m"
# define BLUE "\033[34;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define RESET "\033[0m"

// --- Window ---
# define WIDTH 1920
# define HEIGHT 1080

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
}				t_type;

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

// -------------------------------------------------------------
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
// Struct for objects, each object has this struct
//		- center, point1, point2, 
//		  point3, point_flag, vector, 
//		  diameter, height	-> (for intersection calculation); 
//		- type 				-> (what type of obj);
//		- colour 			-> (colour of obj);
//		- what_pattern 		-> (what patten that obj currently has); 
//		- i_am 				-> (what obj num this is, basicly ID);
//		- i 				-> (iterate through the different obj patterns,
//							   Resrets to 0 after 2 iterations);
//		- *texture (for texture); ????????????????
typedef struct s_objs
{
	t_type				type;
	t_colour			colour;
	t_vec3				center;
	t_vec3				vector;
	t_vec3				point1;
	t_vec3				point2;
	t_vec3				point3;
	int					point_flag;
	double				diameter;
	double				height;
	int16_t				i_am;
	int					what_pattern; 
	int					i;
	mlx_texture_t		*texture; // ??? we still need this?
	// mlx_image_t			*text_img; // we still need this ???
}	t_objs;

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

// -------------------------------------------------------------
// Struct for light
typedef struct s_light  // RM THIS ONE once it's fixed
{                       // RM
	t_colour	colour; // RM
	t_vec3		place;  // RM
	double		ratio;  // RM
}	t_light;            // RM

typedef struct s_lightS // WE need this one // without the s
{
	t_colour	colour;
	t_vec3		place;
	double		ratio;
}	t_lightS;

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
	int 			mou_y;
	int				mou_x;
	bool			selected;
}   t_mouse;

// -------------------------------------------------------------
// Ray struct
typedef struct s_ray
{
	t_vec3	place;
	t_vec3	vector;
}	t_ray;

// -------------------------------------------------------------
// Main struct
//		- **objs, camera, ambient,
//		  **light, screen, type, 
//		  mouse, ray		-> (all kind of structs);
//		- *image, *mlx		-> (MLX structs);
//		- objs_i, lights_i	-> (how many obj & lights we have);
//		- i_am				-> (what object is currently seleted);
typedef struct s_data
{
	mlx_image_t		*image;
	mlx_t			*mlx;
	t_objs			**objs;
	t_camera		camera;
	t_ambient		ambient;
	t_light			light;	//Rm this one
	t_lightS		**lightS; // WE only need this one
	t_screen		screen;
	t_type			type;
	t_mouse			mouse;
	t_ray			ray;
	int				objs_i;
	int 			lights_i; 
	int16_t			i_am;
}	t_data;

// -------------------------------------------------------------
// Object data struct (standing alone)
//		-> saves the calculations of the intersections
typedef struct s_obj_hit
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

}	t_obj_hit;

// -------------------------------------------------------------
// Struct for all colour variables (standing alone)
typedef	struct s_colour_vars
{
	t_colour	result;
	t_lightS	*curr_light;
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

// --- Functions --- 
// Window Functions
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
uint32_t	ft_calculate_colour(t_data *data, t_obj_hit *obj, t_ray ray);
t_colour	get_colour(t_data *data, t_obj_hit *obj_hit, t_ray ray, t_objs *obj);
t_vec3		get_surface_normal(t_vec3 intersection_point, t_objs *obj);
t_colour	get_base_colour(t_objs *obj, t_colour_vars colour);

// Colour Functions Bonus
t_colour	get_sphere_checkerboard(t_vec3 normal);
t_colour	get_plane_checkerboard(t_objs *plane, t_vec3 normal);
t_colour	get_cylinder_checkerboard(t_vec3 normal);

// Operators
t_vec3 		plus_vecdub(t_vec3 u, double v);
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

// Objects Functions
bool		check_closest(t_obj_hit *obj_hit);
bool		quadratic(t_obj_hit *obj_hit);
bool		check_caps(t_obj_hit *obj, t_objs *cyl, t_ray *ray);
bool		check_roots(t_obj_hit *obj, t_objs *cyl, t_ray *ray);
bool		intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_hit *obj_hit);
bool		intersect_plane(t_ray *ray, t_objs *plane, t_obj_hit *obj_hit);
bool		intersect_plane_for_colour(t_ray *ray, t_objs *plane, t_obj_hit *obj_hit);
bool		intersect_sphere(t_ray *ray, t_objs *sphere, t_obj_hit *obj_hit);
bool		intersect_triangle(t_ray *ray, t_objs *tri, t_obj_hit *obj_hit);


// Utils
t_vec3		ft_reflect(t_vec3 incident, t_vec3 normal);
int32_t		ft_convert_rgb(int32_t r, int32_t g, int32_t b);

#endif