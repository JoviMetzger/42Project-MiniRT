/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 22:36:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/19 15:14:01 by smclacke      ########   odam.nl         */
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
	printf("C vector = %f %f %f\n\n", data->camera.vector.x, data->camera.vector.y, data->camera.vector.z);
	printf("C FOV = %i\n", data->camera.FOV);
	printf("----------------------------------\n");
	printf("\tL\n");
	printf("L coords = %f %f %f\n\n", data->light.place.x, data->light.place.y, data->light.place.z);
	printf("L ratio = %f\n", data->light.ratio);
	printf("L rgb = %i %i %i\n", data->light.colour.r, data->light.colour.g, data->light.colour.b);
	printf("----------------------------------\n");
	printf("\tsp\n");
	printf("sp coords = %f %f %f\n", data->objects.sphere.center.x, data->objects.sphere.center.y, data->objects.sphere.center.z);
	printf("sp diameter = %f\n", data->objects.sphere.diameter);
	printf("sp rgb = %i %i %i\n\n", data->objects.sphere.colour.r, data->objects.sphere.colour.g, data->objects.sphere.colour.b);
	printf("----------------------------------\n");
	printf("\tpl\n");
	printf("pl coords = %f %f %f\n", data->objects.plane.center.x, data->objects.plane.center.y, data->objects.plane.center.z);
	printf("pl vector = %f %f %f\n", data->objects.plane.vector.x, data->objects.plane.vector.y, data->objects.plane.vector.z);
	printf("pl rgb = %i %i %i\n\n", data->objects.plane.colour.r, data->objects.plane.colour.g, data->objects.plane.colour.b);
	printf("----------------------------------\n");
	printf("\tcy\n");
	printf("cy coords = %f %f %f\n", data->objects.cylinder.center.x, data->objects.cylinder.center.y, data->objects.cylinder.center.z);
	printf("cy vector = %f %f %f\n", data->objects.cylinder.vector.x, data->objects.cylinder.vector.y, data->objects.cylinder.vector.z);
	printf("cy diameter = %f\n", data->objects.cylinder.diameter);
	printf("cy height = %f\n", data->objects.cylinder.height);
	printf("cy rgb = %i %i %i\n\n", data->objects.cylinder.colour.r, data->objects.cylinder.colour.g, data->objects.cylinder.colour.b);
}
