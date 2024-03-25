/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 22:36:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/25 15:11:07 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"

void	print_parser(t_data *data)
{
	printf("\tA\n");
	printf("A ratio = %f\n", data->ambient.ratio);
	printf("A rgb = %i %i %i\n\n", data->ambient.colour.r, data->ambient.colour.g, data->ambient.colour.b);
	printf("----------------------------------\n");
	printf("\tC\n");
	printf("C coords = %f %f %f\n", data->camera.place.x, data->camera.place.y, data->camera.place.z);
	printf("C vector = %f %f %f\n", data->camera.vector.x, data->camera.vector.y, data->camera.vector.z);
	printf("C FOV = %i\n\n", data->camera.FOV);
	printf("----------------------------------\n");
	printf("\tL\n");
	printf("L coords = %f %f %f\n", data->light.place.x, data->light.place.y, data->light.place.z);
	printf("L ratio = %f\n", data->light.ratio);
	printf("L rgb = %i %i %i\n\n", data->light.colour.r, data->light.colour.g, data->light.colour.b);
	printf("----------------------------------\n");

	int		index = 0;

	while (index < data->objs->i)
	{
		printf("obj type = %i\n", data->objs[index].type);
		printf("DIAMETER = %f\n", data->objs[index].diameter);
		printf("HEIGHT = %f\n", data->objs[index].height);
		printf("coords = %f,%f,%f\n", data->objs[index].center.x, data->objs[index].center.y, data->objs[index].center.z);
		index++;
	}
}
