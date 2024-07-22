
// old in light functions

// first push, just added light while loop

// static bool	in_light(t_data *data, int i)
// {
// 	int				light_i = 0;
//     t_hit_data		hit_2;
// 	t_ray			ray;

// 	data->pix[i]->in_light = true;
// 	while (light_i < data->light_i)
// 	{
// 		data->light[light_i]->in_light = true;
// 		int obj_i = 0;
// 		ray = init_light_ray(data, i, light_i);
// 		while (obj_i < data->objs_i)
// 		{
// 			if ((intersect_sphere(&ray, data->objs[obj_i], &hit_2)
// 				|| intersect_triangle(&ray, data->objs[obj_i], &hit_2)
// 				|| intersect_cylinder(&ray, data->objs[obj_i], &hit_2)
// 				|| intersect_plane(&ray, data->objs[obj_i], &hit_2))
// 				&& data->objs[obj_i] != data->pix[i]->obj)
// 				{
// 					data->light[light_i]->in_light = false;
// 					data->pix[i]->in_light = false;
// 					break ;
// 				}
// 			obj_i++;
// 		}
// 		light_i++;
// 	}
// 	light_i = 0;
// 	while (light_i < data->light_i)
// 	{
// 		if (data->light[light_i]->in_light == true)
// 			data->pix[i]->in_light = true;
// 		else
// 			return (false);
// 		light_i++;
// 	}
// 	if (data->pix[i]->in_light == true)
// 		return (true);
// 	return (false);
// }

static bool	in_light(t_data *data, int i)
{
	int				light_i = 0;
    t_hit_data		hit_2;
	t_ray			ray;
	int				obj_i = 0;

	data->pix[i]->in_light = true;
	data->objs[obj_i]->in_light = true;
	while (light_i < data->light_i)
	{
		data->light[light_i]->in_light = true;
		obj_i = 0;
		ray = init_light_ray(data, i, light_i);
		while (obj_i < data->objs_i)
		{
			if ((intersect_sphere(&ray, data->objs[obj_i], &hit_2)
				|| intersect_triangle(&ray, data->objs[obj_i], &hit_2)
				|| intersect_cylinder(&ray, data->objs[obj_i], &hit_2)
				|| intersect_plane(&ray, data->objs[obj_i], &hit_2))
				&& data->objs[obj_i] != data->pix[i]->obj)
				{
					data->light[light_i]->in_light = false;
					data->objs[obj_i]->in_light = false;
					data->pix[i]->in_light = false;
					break ;
				}
			obj_i++;
		}
		light_i++;
	}
	light_i = 0;
	while (light_i < data->light_i)
	{
		if (data->light[light_i]->in_light == true)
			data->pix[i]->in_light = true;
		else
			return (false);
		light_i++;
	}
	if (data->pix[i]->in_light == true)
		return (true);
	return (false);
}


// static bool	in_light(t_data *data, int i)
// {
// 	int				light_i = 0;
//     t_hit_data		hit_2;
// 	t_ray			ray;
// 	int				obj_i = 0;

// 	data->pix[i]->in_light = true;
// 	data->objs[obj_i]->in_light = true;
// 	while (light_i < data->light_i)
// 	{
// 		data->light[light_i]->in_light = true;
// 		obj_i = 0;
// 		ft_bzero(&ray, sizeof(t_ray));
// 		ray = init_light_ray(data, i, light_i);
// 		while (obj_i < data->objs_i)
// 		{
// 			ft_bzero(&hit_2, sizeof(t_hit_data));
// 			if (does_intersect(&ray, data->objs[obj_i], &hit_2)
// 				&& data->objs[obj_i] != data->pix[i]->obj)
// 				{
// 					data->light[light_i]->in_light = false;
// 					data->objs[obj_i]->in_light = false;
// 					data->pix[i]->in_light = false;
// 					break ;
// 				}
// 			obj_i++;
// 		}
// 		light_i++;
// 	}
// 	if (check_all_after(data, i) == true)
// 		return (true);
// 	return (false);
// }

