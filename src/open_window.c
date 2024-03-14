#include "../header/miniRT.h"

void error_msg(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);;
	exit(EXIT_FAILURE);
}

void ft_open_window(t_data *data)
{
	// Gotta error check this stuff
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 0)))
		error_msg("Failed to set up the connection.");
	if (!(data->image = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height)))
	{
		mlx_close_window(data->mlx);
		error_msg("Failed to create a new image.");
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		error_msg("Failed to create a new window.");
	}
}
