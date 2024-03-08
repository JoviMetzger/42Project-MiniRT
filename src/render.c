#include "../header/miniRT.h"

// Might or might not need the function
int32_t ft_pixel(int32_t r, int32_t g, int32_t b)
{
	int32_t a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}


// 1. Calculate the ray from the “eye” through the pixel,
// 2. Determine which objects the ray intersects, and
// 3. Compute a color for the closest intersection point.
void ft_put_image(t_data *data)
{
	t_ray ray;
	int y = 0;
	int x = 0;
	while (x < data->mlx->width)
	{
		while (y < data->mlx->height)
		{
			// 1. Calculate the ray from the “eye” through the pixel,
			// 2. Determine which objects the ray intersects, and
			ray = ft_create_ray(data, x ,y); // create/calculate ray 
			
			// 3. Compute a color for the closest intersection point.
			// mlx_put_pixel(data->image, x, y, ft_colour(ray, data));

			// -------------- TESTING ------------------------
			// ft_testing(data, x, y);
			// mlx_put_pixel(data->image, x, y, ft_pixel(10, 0, 255)); //RM tetsing
			// -----------------------------------------------
			y++;
		}
		y = 0;
		x++;
	}
}

void ft_render(t_data *data)
{
	ft_put_image(data); // Shazam(MATH)
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data); // movement aka ESC

}

