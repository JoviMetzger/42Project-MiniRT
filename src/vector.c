#include "../header/miniRT.h"

// assign pixels to the position of the ray-vector 
t_vec3 init_ray_pos(double pos_x, double pos_y, double pos_z)
{
    t_vec3 vec;

    vec.x = pos_x;
    vec.y = pos_y;
    vec.z = pos_z;
    return (vec);
}

// t_vec3 pos: ray direction;
//
t_vec3  matrix_math(double *matrix, t_vec3 pos)
{
    // NoT WoRKinG YET!!!
    // FIRST NeED TO INIT tHe maTriX
    (void)matrix;
    (void)pos;
    int i = 0;
    t_vec3 = 
    printF("GOT SO FAR, MATRIX NOT HEre YEt!\n");
}

t_vec3 init_vector(t_data *data, t_screen screen)
{
    // it returns the normalizes_vectors (scale it and assings a value to each pos3 (xyz)) of the 'matrix calculation';
    // the 'matrix calculation' takes the matrix(still need to create that) and the ray-vector;
    // Altough we need the ray-vector we assign x,y,z the pixel_x-y-z -> init_ray_pos() as the ray-vector;
    // matrix-calculation calculates then the ray.
    return (normalize_vector(matrix_math(data->matrix, init_ray_pos(screen.pixel_delata_x, screen.pixel_delata_y, 1))));
}