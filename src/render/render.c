#include "../../header/miniRT.h"

// Might or might not need the function
int32_t ft_pixel(int32_t r, int32_t g, int32_t b)
{
	int32_t a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}

void ft_put_image(t_data *data)
{
	// t_ray ray;
	uint32_t y = 0;
	uint32_t x = 0;
	while (x < data->viewport_W)
	{
		while (y < data->viewport_H)
		{
			// ray = ft_create_ray(data, x ,y); // create/calculate ray 
			// mlx_put_pixel(data->image, x, y, ft_colour(ray, data));
			mlx_put_pixel(data->image, x, y, ft_pixel(0, 0, 0)); //RM tetsing
			y++;
		}
		y = 0;
		x++;
	}
}


void ft_render(t_data *data)
{
    // mlx_loop_hook(data->mlx, ft_put_image, data);	// Putting pixel on image.
	ft_put_image(data);
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data); // movement aka ESC

}

