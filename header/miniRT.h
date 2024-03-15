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
# define M_PI 3.14159265358979323846 // This is a constant representing the value of pi. -> i am pretty sure it is defined in the 'math.h' library, but VScode is not reconizing it. So I defined it here again 

// --- Structs --- 
// -------------------------------------------------------------
// // Position - coordinates
// // Don't understand the difference between a union and struct.
// // you can just as well use the 'normal' x,y,z position
// // because to use 'double xyz' you need to do t_pos3.xyz[0], which is same as t_pos3.x
// typedef union u_vec3
// {
//     double   xyz[3];
//     struct
//     {
//         double	x;  // x-axis (left-right)
//         double	y;  // y-axis (up-down)
//         double	z;  // z-axis (forward-back forwrd)
//     };
// }   t_vec3;

// Position - coordinates
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
    struct s_sphere     *next;
}   t_sphere;

// Object2: plane
typedef struct s_plane
{
    t_colour        colour;
    t_vec3          center;
    t_vec3          vector;
    struct s_plane  *next;
}   t_plane;

// Object3: cylinder
typedef struct s_cylinder
{
    t_colour            colour;
    t_vec3              center;
    t_vec3              vector;
    double              diameter;
    double              height;
    struct s_cylinder   *next;
}   t_cylinder;

// Struct for objects
typedef struct s_obj_type
{
    t_sphere     sphere;
    t_plane      plane;
    t_cylinder   cylinder;
    // t_cone       cone; // BONUS
}   t_obj_type;

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
    double  total_pixel_num; // might not need
}   t_screen;

// -------------------------------------------------------------
// Main struct
typedef struct s_data
{
    mlx_image_t *image;
    mlx_t       *mlx;
    t_screen    screen;
    t_obj_type  objects;
    t_camera    camera;
    t_ambient   ambient;
    t_light     light;
    double      matrix[16]; // representation for 4x4 matrices. Each element of the array corresponds to a specific position in the matrix, following a specific order. 
}   t_data;

// -------------------------------------------------------------
// Ray struct (alone standing)
typedef struct s_ray
{
    t_vec3  place;
    t_vec3  vector;
}   t_ray;

// --- Functions --- 
// Main functions
void ft_put_image(t_data *data);
void ft_key_action(mlx_key_data_t keydata, t_data *data);
void ft_open_window(t_data *data);
void ft_parse_input(int argc, char **argv, t_data *data);
void ft_render(t_data *data);

int32_t ft_pixel(int32_t r, int32_t g, int32_t b);
t_ray ft_create_ray(t_data *data, int x, int y);
t_vec3 init_vector(t_data *data, t_screen screen);

// operators
t_vec3 plus(t_vec3 u, t_vec3 v);
t_vec3 minus(t_vec3 u, t_vec3 v);
t_vec3 mult_vecvec(t_vec3 u, t_vec3 v);
t_vec3 mult_vecdub(t_vec3 v, double dub);
t_vec3 division_vec_dub(t_vec3 v, double dub);
t_vec3 division_vec_vec(t_vec3 u, t_vec3 v);
double dot_product(t_vec3 u, t_vec3 v);
t_vec3 cross_product(t_vec3 u, t_vec3 v);
double length_squared(t_vec3 vec);
t_vec3	normalize_vector(t_vec3 v);


#endif