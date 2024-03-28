/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 14:43:34 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/27 15:49:03 by jmetzger      ########   odam.nl         */
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

// Window
# define WIDTH 1920
# define HEIGHT 1080

// Math stuff
# define M_PI 3.14159265358979323846 // This is a constant representing the value of pi.

// --- Structs ---
// Vector - position - coordinates
typedef struct s_vec3
{
    double	x;  // x-axis (left-right)
    double	y;  // y-axis (up-down)
    double	z;  // z-axis (forward-back forwrd)
}   t_vec3;

// -------------------------------------------------------------
// Colour - RGB
typedef struct s_colour
{
    int     r;  // red
    int     g;  // green
    int     b;  // blue
}   t_colour;

// -------------------------------------------------------------
// Object1: sphere
typedef struct s_sphere
{
    t_colour            colour;
    t_vec3              center;
    double              diameter;
}   t_sphere;

// Object2: plane
typedef struct s_plane
{
    t_colour        colour;
    t_vec3          center;
    t_vec3          vector;
}   t_plane;

// Object3: cylinder
typedef struct s_cylinder
{
    t_colour            colour;
    t_vec3              center;
    t_vec3              vector;
    double              diameter;
    double              height;
}   t_cylinder;

// Struct for objects
typedef struct s_objects
{
    t_sphere     sphere;
    t_plane      plane;
    t_cylinder   cylinder;
    // t_cone       cone; // BONUS
    struct s_objects    *next;
}   t_objects;

// -------------------------------------------------------------
// Struct for camera
typedef struct s_camera
{
    t_vec3      place;
    t_vec3      vector;
    int         FOV; //field of view
}   t_camera;

// -------------------------------------------------------------
// Struct for ambient - background
typedef struct s_ambient 
{
    t_colour    colour;
    double      ratio;
}   t_ambient;

// -------------------------------------------------------------
// Struct for light
typedef struct s_light 
{
    t_colour    colour;
    t_vec3      place;
    double      ratio;
}   t_light;

// -------------------------------------------------------------
// Screen struct
typedef struct s_screen
{
    double  viewport_w;
    double  viewport_h;
    double  img_ratio;
    double  pixel_delata_x;
    double  pixel_delata_y;
}   t_screen;

// -------------------------------------------------------------
// Main struct
typedef struct s_data
{
	mlx_image_t	*image;
	mlx_t		*mlx;
	t_objects	objects;
	t_camera	camera;
	t_ambient	ambient;
	t_light		light;
    t_screen    screen;
	int			type;
    double      matrix[16]; // representation for 4x4 matrices. Each element of the array corresponds to a specific position in the matrix, following a specific order. 
    int     total_obj_num; //RM
}	t_data;

// -------------------------------------------------------------
// Ray struct (standing alone)
typedef struct s_ray
{
    t_vec3  place;
    t_vec3  vector;
}   t_ray;

// -------------------------------------------------------------
// Object data struct (standing alone)
typedef struct s_obj_data 
{
    double  a;
    double  b;
    double  c;
    double  d;
    double  root1;
    double  root2;
    double t;

}   t_obj_data;

// --- Functions --- 
// Window Functions
void ft_put_image(t_data *data);
void ft_open_window(t_data *data);
void ft_render(t_data *data);
void ft_key_action(mlx_key_data_t keydata, t_data *data);

// Ray Functions
t_ray ft_create_ray(t_data *data, int x, int y);
void store_ray_matrix(t_data *data);
t_vec3 init_vector(t_data *data, t_screen screen);

// Lightray Functions
void ft_create_lightray(t_data *data, t_obj_data *obj_data, t_ray *lightray);

// Colour Functions
int32_t ft_get_rgb(int32_t r, int32_t g, int32_t b);
uint32_t ft_calculate_colour(t_data *data, t_obj_data *obj, t_ray ray);

// Operators
t_vec3 plus(t_vec3 u, t_vec3 v);
t_vec3 minus(t_vec3 u, t_vec3 v);
t_vec3 mult_vecvec(t_vec3 u, t_vec3 v);
t_vec3 mult_vecdub(t_vec3 v, double dub);
t_vec3 division_vec_dub(t_vec3 v, double dub);
t_vec3 division_vec_vec(t_vec3 u, t_vec3 v); // might remove this
t_vec3 cross_product(t_vec3 u, t_vec3 v);
double dot_product(t_vec3 u, t_vec3 v);
double length_squared(t_vec3 vec);
t_vec3	normalize_vector(t_vec3 v);

// Objects Functions
void ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray);
// bool ft_create_intersection(t_data *data, t_obj_data *obj_data, t_ray ray);
bool intersect_sphere(t_ray *ray, t_sphere *sphere, t_obj_data *obj_data);
void intersect_plane(t_ray *ray, t_plane *plane, t_obj_data *obj_data);
void intersect_cylinder(t_ray *ray, t_cylinder *cylinder, t_obj_data *obj_data);

#endif