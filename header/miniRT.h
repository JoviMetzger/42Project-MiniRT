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
#define WIDTH 1920
#define HEIGHT 1080

// --- Structs --- 
// -------------------------------------------------------------
// Position - coordinates
typedef union u_pos3
{
    double   xyz[3];
    struct
    {
        double	x;  // x-axis (left-right)
        double	y;  // y-axis (up-down)
        double	z;  // z-axis (forward-back forwrd)
    };
}   t_pos3;

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
    t_colour    colour;
    t_pos3      center;
    double       diameter;
    struct s_sphere *next;
}   t_sphere;

// Object2: plane
typedef struct s_plane
{
    t_colour colour;
    t_pos3   center;
    t_pos3   vector;
    struct s_plane *next;
}   t_plane;

// Object3: cylinder
typedef struct s_cylinder
{
    t_colour    colour;
    t_pos3      center;
    t_pos3      vector;
    double    diameter;
    double    height;
    struct s_cylinder *next;
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
    t_pos3      place;
    t_pos3      vector;
    int         FOV; //field of view
}   t_camera;

// -------------------------------------------------------------
// Struct for ambient - background
typedef struct s_ambient 
{
    t_colour    colour;
    double       ratio;
}   t_ambient;

// -------------------------------------------------------------
// Struct for light
typedef struct s_light 
{
    t_colour    colour;
    t_pos3      place;
    double       ratio;
}   t_light;

// -------------------------------------------------------------
// Screen struct
typedef struct s_screen
{
    double  viewport_w;
    double  viewport_h;
    double  img_ratio;
    double  pixel_x;
    double  pixel_y;
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
}   t_data;

// -------------------------------------------------------------
// Ray struct (alone standing)
typedef struct s_ray
{
    t_pos3  place;
    t_pos3  vector;
}   t_ray;


// --- Functions --- 
// Main functions
void ft_put_image(t_data *data);
void ft_key_action(mlx_key_data_t keydata, t_data *data);
void ft_open_window(t_data *data);
void ft_parse_input(int argc, char **argv, t_data *data);
void ft_render(t_data *data);

void ft_testing(t_data *data, uint32_t x, uint32_t y);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b);
t_ray ft_create_ray(t_data *data, int x, int y);


#endif