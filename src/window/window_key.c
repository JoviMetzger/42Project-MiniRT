/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window_key.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/06 17:35:22 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"
#include "../../header/parser.h"

/*	This function is for if the object got selected to change the pattern.
 *		- obj->what_pattern = 1;	->	is for Checkerboard.
 *		- obj->what_pattern = 0;	->	is for Normal.
 */
static void	change_pattern(t_data *data, t_objs *obj)
{
	if (obj->i == 1)
		obj->what_pattern = 1;
	else
		obj->what_pattern = 0;
	ft_put_image(data);
}

//	This function checks what object got selected
static void	what_obj_me(t_data *data, t_objs *obj)
{
	if (obj->type == E_SPHERE)
		change_pattern(data, data->objs[data->i_am]);
	else if (obj->type == E_PLANE)
		change_pattern(data, data->objs[data->i_am]);
	else if (obj->type == E_CYLINDER)
		change_pattern(data, data->objs[data->i_am]);
}

/*	Key commands
 *	- If the pressed key is 'ESC key', close and free window.
 *	- If an object got selected (data->mouse.selected == true)
 *	  And the key 'Arrow up' is pressed, we change the pattern of that object.
 *	  (We first check what object got selected and then we change the pattern)
 */
void	ft_key_action(mlx_key_data_t keydata, t_data *data)
{
	(void)keydata;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
		free_objects(data);
	}
	if (data->mouse.selected == true && mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->objs[data->i_am]->i++;
		if (data->objs[data->i_am]->i > 1)
			data->objs[data->i_am]->i = 0;
		what_obj_me(data, data->objs[data->i_am]);
	}
}
