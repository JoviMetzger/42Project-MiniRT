/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/23 17:14:22 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"
#include "../header/miniRT.h"

// USE SARAHS rt_malloc function !!!!
// void	*ft_rt_malloc(t_data *data, size_t size)
// {
// 	void	*alloc;
// 	(void)data;

// 	alloc = malloc(size);
// 	if (alloc == NULL)
// 	{
// 		printf("malloc failure\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (alloc);
// }

// // NOTE :: Put this to the parser files just so the structure of the files make sence.
// // Init the map for the mouse clicks.
// void	init_mouse_map(t_data *data) //turn this function into an char or int ?
// {
// 	int16_t	**map;
// 	uint32_t	i;

// 	i = 0;
	
// 	data->mouse.window_h = HEIGHT;
// 	data->mouse.window_w = WIDTH;
// 	if (data->mouse.mouse_map != NULL)
// 	{
// 		printf("Error: map failure\n");
// 		exit(EXIT_FAILURE);  // return a int or something else
// 	}
// 	map = ft_rt_malloc(data, (data->mouse.window_h + 1) * sizeof(int16_t *));
// 	data->mouse.mouse_map = map;
// 	while (i < data->mouse.window_h)
// 	{
// 		map[i] = ft_rt_malloc(data, data->mouse.window_w  * sizeof(int16_t)); // USE sarahs rt_malloc function
// 		i++;
// 	}
// 	map[i] = NULL;
// 	data->mouse.mouse_map = map;
// }

// main function:
int main(int argc, char **argv)
{
    t_data data;

	parse_input(argc, argv, &data);

	ft_open_window(&data); // Open window
	ft_render(&data); // the whole shazam!

	mlx_loop(data.mlx);		// loop

	//	mlx_delete_image(image); // might need these things if textures but idkk
	//	mlx_delete_texture(texture);
	
	mlx_terminate(data.mlx); // terminate

	free_objects(&data);	// needs to be part of the clean up
	return (EXIT_SUCCESS);
}
