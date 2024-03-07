#include "../header/miniRT.h"

int main(int argc, char **argv)
{
    t_data data;

	ft_parse_input(argc, argv, &data); // Check file Input & supstract the values to the struct.
    
	ft_open_window(&data); // Open window
	ft_render(&data); // the whole shazam!

	mlx_loop(data.mlx);		// loop
	mlx_terminate(data.mlx); // terminate
	return (EXIT_SUCCESS);
}
