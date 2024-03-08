/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 14:43:34 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/08 15:38:36 by smclacke      ########   odam.nl         */
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
# define WIDTH 1400
# define HEIGHT 1000

// --- Structs --- 
// -------------------------------------------------------------
// Position - coordinates
typedef struct s_pos3
{
    float	x;  // x-axis (left-right)
    float	y;  // y-axis (up-down)
    float	z;  // z-axis (forward-back forwrd)
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
    float       diameter;
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
    float    diameter;
    float    height;
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
    int         FOV;
}   t_camera;

// -------------------------------------------------------------
// Struct for ambient - background
typedef struct s_ambient 
{
    t_colour    colour;
    float       ratio;
}   t_ambient;

// -------------------------------------------------------------
// Struct for light
typedef struct s_light 
{
    t_colour    colour;
    t_pos3      place;
    float       ratio;
}   t_light;

// -------------------------------------------------------------
// Main struct
typedef struct s_data
{
    mlx_image_t *image;
    mlx_t       *mlx;
    uint32_t    viewport_W;
    uint32_t    viewport_H;
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
void error_msg(char *msg);
void ft_render(t_data *data);

#endif