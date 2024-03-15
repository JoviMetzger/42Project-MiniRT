#include "../header/miniRT.h"

// Might or might not need the function
int32_t ft_pixel(int32_t r, int32_t g, int32_t b)
{
	int32_t a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}

//rm - for testing -> rm later
uint32_t pixel_colour(t_ray ray) 
{
	(void)ray;
	// probably need t_colour struct
	// so something like this:
	// ft_pixel(data->objects.cylinder.colour.r, data->objects.cylinder.colour.g, data->objects.cylinder.colour.b);
    // BUT USING THE t_ray. | t_data *data can be removed later it was for testing purposes
	return ft_pixel(10, 0, 255);
}

// 1. Calculate the ray from the “eye” through the pixel,
// 2. Determine which objects the ray intersects, and
// 3. Compute a color for the closest intersection point.
void ft_put_image(t_data *data)
{
	t_ray ray;
	int y = 0;
	int x = 0;
	// init_camera(data); // Not sure if I need to init it here or in the while loop
	while (x < data->mlx->width)
	{
		while (y < data->mlx->height)
		{
			// 1. Calculate the ray from the “eye” through the pixel,
			// 2. Determine which objects the ray intersects, and
			// 3. Compute a color for the closest intersection point.

			// ------------ eVerYTinG BeloW tHiS liNe iS jUSt ME gOiNg "hhhUUUUUhhhhhh?????????????" -----------
			// aka. cat meme (https://www.youtube.com/watch?v=xVWeRnStdSA)
		
			// --> Don't know what I am doning <--
			ray = ft_create_ray(data, x ,y);
			uint32_t colour = pixel_colour(ray);
			mlx_put_pixel(data->image, x, y, colour);
			// -----------------------------------------------
			
			// -------------- TESTING ------------------------
			// //  Drawing a circle -> rm later
			// ft_testing(data, x, y);
			// mlx_put_pixel(data->image, x, y, ft_pixel(10, 0, 255)); //RM tetsing
			// -----------------------------------------------
			// -------------------------------------------------------------------------------------------------

			y++;
		}
		y = 0; // NoT sure if this is important -> made sence while I was writing this, but now I don't know the why
		x++;
	}
}

void ft_render(t_data *data)
{
	ft_put_image(data); // Shazam(MATH)
	mlx_key_hook(data->mlx, (mlx_keyfunc)ft_key_action, data); // movement aka ESC

}
