/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/11 13:58:32 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

		// if (data->objs[j]->obj_hit < DBL_MAX)
		// {
		// 	// 
		// }
		// // hit->t per obj loop, checking if shadow ray hits
		// // way of not doing this? + changing hit data? + saving the closest hit/going in order of file array
// REMEMBER LIGHT ARRAY..

static t_colour give_light(t_data *data)
{
	add_light(&data->vars, data->ray);
	data->vars.result.r = fmin(255, fmax(0, data->vars.result.r));
	data->vars.result.g = fmin(255, fmax(0, data->vars.result.g));
	data->vars.result.b = fmin(255, fmax(0, data->vars.result.b));
	return (data->vars.result);
}

// check_shadow
static bool check_light(t_data *data, t_objs *obj, t_hit_data *hit)
{
	// (void) hit;
	t_ray	shadow_ray;
	data->is_shadow = 0;
	obj->has_shadow = 0;
	
	shadow_ray.place = plus(data->vars.intersect_p, mult_vecdub(obj->normal, EPSILON));
	shadow_ray.vector = data->vars.light_dir; // LATER; colour->curr_light->place

	int j = -1;
	while (++j < data->objs_i)
	{
		// if ray does not hit directly - false
		if (intersect_sphere(&shadow_ray, data->objs[j], hit)
			|| intersect_plane(&shadow_ray, data->objs[j], hit)
			|| intersect_cylinder(&shadow_ray, data->objs[j], hit)
			|| intersect_triangle(&shadow_ray, data->objs[j], hit))
			return (false);
	}
	return (true);
}
		
// update_shadow_colour
// change back/cover with ambient lighting

/*	This function checks which object is closer to the camera, 
 *	other wise objects will overlap and won't be dispalyed realistic.
 *		- If no intersection is found, it will return black.
 */
static uint32_t	get_ret(t_data *data, t_hit_data *hit, t_objs *obj)
{
	t_colour	colour;
	uint32_t	ambient_light;
	t_colour	light;

	if (hit->closest_t != DBL_MAX)
	{
		colour = get_colour(data, hit, obj); // colour for this obj, we know is closests
		ambient_light = ft_convert_rgb(colour.r, colour.g, colour.b);
		// printf("colours = %d %d %d\n", data->vars.result.r, data->vars.result.g, data->vars.result.b);

		if (check_light(data, obj, hit) == true)
		{
			// puts("light!");
			light = give_light(data);
			return (ft_convert_rgb(light.r, light.g, light.b));
		}
		else
		{
			// puts("here");
			return (ambient_light);
		}
		
	}
	else
		return (ft_convert_rgb(0, 0, 0));
}

/*	This function applies colour to each hit object.
 *		- It applies get_colour() to the correct type;
 *		- The result of that will be send back to mlx_put_pixel().
 *		- data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = i; 
 *		  is for the mouse_map, so that we can select object.
 */
// all the same regardless of obj type
static void	do_stuff(t_type type, t_data *data, t_hit_data *hit, int obj_i)
{
	(void) type; // remove
	(void) hit; // remove
	data->objs[obj_i]->i_am = obj_i;
	data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = obj_i;
}

/*	STEP 2. Determine which objects the ray intersects
 *	
 *	This function applies colour to each hit object.
 *		- It loops through all the objects and checks 
 *		  if it has an intersect point (if a obj gets hit).
 *			- If it does have a hit point it executs do_stuff();
 *			  (Becuse the function was too long)
 */
uint32_t	ft_calculate_colour(t_data *data, t_hit_data *hit)
{
	int		i;
	t_objs	*tmp_obj;

	i = 0;
	hit->closest_t = DBL_MAX;
	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_SPHERE
			&& intersect_sphere(&data->ray, data->objs[i], hit))
		{
			tmp_obj = data->objs[i];	
			do_stuff(E_SPHERE, data, hit, i); // remove hit and type + change function name
		}
		else if (data->objs[i]->type == E_PLANE
			&& intersect_plane(&data->ray, data->objs[i], hit))
		{		
			tmp_obj = data->objs[i];	
			do_stuff(E_PLANE, data, hit, i); // remove hit and type + change function name
		}
		else if (data->objs[i]->type == E_CYLINDER
			&& intersect_cylinder(&data->ray, data->objs[i], hit))
		{		
			tmp_obj = data->objs[i];	
			do_stuff(E_CYLINDER, data, hit, i); // remove hit and type + change function name
		}
		else if (data->objs[i]->type == E_TRIANGLE	
			&& intersect_triangle(&data->ray, data->objs[i], hit))
		{
			tmp_obj = data->objs[i];
			do_stuff(E_TRIANGLE, data, hit, i); // remove hit and type + change function name
		}
		i++;
	}
	return (get_ret(data, hit, tmp_obj));
}
  