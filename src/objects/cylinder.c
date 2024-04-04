/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/04 21:03:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// trying to figure out a capper cylinder with the below formula...

/**
 *
	// cylinder defined by extremes a and b, and radious ra
	vec4 cylIntersect( in vec3 ro, in vec3 rd, in vec3 a, in vec3 b, float ra )
	{
		vec3  ba = b  - a;
		vec3  oc = ro - a;
		float baba = dot(ba,ba);
		float bard = dot(ba,rd);
		float baoc = dot(ba,oc);
		float k2 = baba            - bard*bard;
		float k1 = baba*dot(oc,rd) - baoc*bard;
		float k0 = baba*dot(oc,oc) - baoc*baoc - ra*ra*baba;
		float h = k1*k1 - k2*k0;
		if( h<0.0 ) return vec4(-1.0);//no intersection
		h = sqrt(h);
		float t = (-k1-h)/k2;
		// body
		float y = baoc + t*bard;
		if( y>0.0 && y<baba ) return vec4( t, (oc+t*rd - ba*y/baba)/ra );
		// caps
		t = ( ((y<0.0) ? 0.0 : baba) - baoc)/bard;
		if( abs(k1+k2*t)<h )
		{
			return vec4( t, ba*sign(y)/sqrt(baba) );
		}
		return vec4(-1.0);//no intersection
	}

	// normal at point p of cylinder (a,b,ra), see above
	vec3 cylNormal( in vec3 p, in vec3 a, in vec3 b, float ra )
	{
		vec3  pa = p - a;
		vec3  ba = b - a;
		float baba = dot(ba,ba);
		float paba = dot(pa,ba);
		float h = dot(pa,ba)/baba;
		return (pa - ba*h)/ra;
	}
 */

// capped cylinder  - (a,b, ra) - ra = radius
// normal at point p of cylinder (a, b, ra) - ra = radius
// bool	intersect_norm_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
// {
// 	double	radius = cylinder->diameter / 2;
// 	t_vec3	ba = minus(ray->place, cylinder->vector);
// 	t_vec3	oc = minus(ray->vector, cylinder->vector);
	
// 	double	baba = dot_product(ba, ba);
// 	double	bard = dot_product(ba, cylinder->vector);
// 	double	baoc = dot_product(ba, oc);
	
// 	double	k2 = baba;
// 	double	k1 = baba * dot_product(oc, cylinder->vector);
	
// }


// infinite cylinder 
// base point - cb, a (normalised axis), ca, a, cr (radius)

// ro - ray->origin = ray->place
// cb - base point = cylinder->vector
bool	intersect_infi_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
{
	t_vec3	oc;
	double	radius = cylinder->diameter / 2;
	double	rad;
	double	c_oc;

	oc = minus(ray->place, cylinder->vector);
	rad = dot_product(ray->vector, cylinder->vector);
	c_oc = dot_product(ray->vector, cylinder->vector);

	obj_data->a = rad - (pow(dot_product(ray->vector, cylinder->center), 2));
	obj_data->b = 2 * dot_product(oc, ray->vector) - c_oc * c_oc - radius * radius;
	obj_data->c = dot_product(oc, oc) - c_oc * dot_product(oc, cylinder->center);
	obj_data->d = obj_data->b * obj_data->b - obj_data->a * obj_data->c;

	if (obj_data->d < 0)
		return (false); // no intersect
	else
	{
		obj_data->d = sqrt(obj_data->d);
		obj_data->root1 = (-obj_data->b - obj_data->d) / obj_data->a;
		obj_data->root2 = (-obj_data->b + obj_data->d) / obj_data->a;
		if (obj_data->root1 > obj_data->root2)
			obj_data->t = obj_data->root1;
		else
			obj_data->t = obj_data->root2;
	}
	return (true); // intersect found
}
