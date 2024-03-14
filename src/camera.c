#include "../header/miniRT.h"

void create_matrix(t_ray ray)
{
    // // Creating the 3D grid;
    // compute_forward_back(); // forward and backwards -> z axis;
    // compute_right_left(); // right and left -> x axis;
    // compute_up_down(); // up and down -> y axis;
}

void init_camera(t_data *data)
{
    t_ray camera;
    camera.place = data->camera.place;
    camera.vector = data->camera.vector;
    create_matrix(camera);

}