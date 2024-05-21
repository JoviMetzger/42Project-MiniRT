

				
C              0,0,0      0,0,1      70

A               0.1      255,255,255

L               -10.0,0.0,0.0     0.5     255,255,255



sp              2.0,0.0,-3       1.2     0,0,0
sp              0.0,0.0,-3       1.0     0,0,255
sp              0.0,1.0,-3       0.2     0,255,255

sp              0.0,0.5,-3       0.5     255,255,255
sp              1.0,0.3,-2       1.0     0,100,0
sp              0.5,0.2,-2       0.1     255,100,0


pl              0.0,0.0,-10.0       0.0,1.0,0.0     0,0,225

cy              50.0,0.0,20.6       0.0,0.0,1.0     14.2     21.42   10,0,255
cy              50.0,0.0,20.6       0.0,0.0,1.0     14.2     21.42   10,0,255
cy              50.0,0.0,20.6       0.0,0.0,1.0     14.2     21.42   10,0,255
cy              50.0,0.0,20.6       0.0,0.0,1.0     14.2     21.42   10,0,255

void ft_create_intersection(t_data *data, t_hit_data *hit_data, t_ray ray)
{
    int i = 0;

    while (i < data->objs->i)
    {
		if (data->objs->type == E_SPHERE)
		{
            if (intersect_sphere(&ray, &data->objs[i], hit_data))
                return ;
		}
        // // 'if' OR 'if/else if'????
        // if (data->objs->type == E_PLANE)
		// {
        //     if (intersect_plane(&ray, &data->objs[i], hit_data))
        //         return ;
		// }
        // if (data->objs->type == E_CYLINDER)
		// {
        //     if (intersect_cylinder(&ray, &data->objs[i], hit_data))
        //         return ;
		// }
        i++;
    }
    return ;
}




// 1. Calculate the ray from the “eye” through the pixel,	 -> ft_create_ray();
// 2. Determine which objects the ray intersects,			 -> ft_create_intersecttions();
// 3. Compute a color for the closest intersection point.	 -> ft_calculate_colour();
void ft_put_image(t_data *data)
{
	t_ray ray;
	t_hit_data hit_data; // maybe we don't need this. -> can add "a,b,c,d,root1,root2,t" in objs struct
	uint32_t colour;
	int y = 0;
	int x = 0;

	while (x < data->mlx->width)
	{
		while (y < data->mlx->height)
		{ 
			ray = ft_create_ray(data, x ,y);
			ft_create_intersection(data, &hit_data, ray);			
			colour = ft_calculate_colour(data, &hit_data, ray); // eVerYTinG iN heRE iS jUSt ME gOiNg "hhhUUUUUhhhhhh?????????????" -> aka. cat meme (https://www.youtube.com/watch?v=xVWeRnStdSA)
			mlx_put_pixel(data->image, x, y, colour);
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


-----------------------------------------------------------------------------

somewhat standard file to test against

A 0.2 255,255,255


pl 0,0,0 0,1.0,0 255,0,225

sp 0,0,20 20 255,0,0

cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255


L -40.0,50.0,0.0 0.6 10,0,255


C -40,0,30 0.7 255,255,255

-----------------------------------------------------------------------------

line 1 = A	+ 	light	+ 	r,g,b
line 2 = C	+ 	coords	+ 	vector	+ 	FOV
line 3 = L	+ 	coords	+ 	light	+ 	r,g,b
line 4 = pl + 	coords	+ 	vector	+ 	r,g,b
line 5 = sp + 	coords	+ 	decimal + 	r,g,b
line 6 = cy + 	coords	+	vector	+	decimal	+	decimal	+	r,g,b



light	-			[0.0,1.0]

r g b	- 			[0 - 255] no decimals

vector	- 			[-1,1] xyz

coordinates -		[decimals] xyz

FOV		-			[0,180]

decimal	-			[decimals] (diameter/height)

// one or more line breaks
// separated by one or more spaces
// each element set in any order
// elements defined by caps declared once, rest possibly many times
// each element starts with the identifier


---------------------------------------------------------
## **Elements of file:**

		**A = ambient lighting**
		------------------------

-> 		Identifier:					A

->		Ratio: 						0.2
	range - [0.0,1.0]

->		R, G, B: 					255, 255, 255
	range - [0,255]


NOTES

 - difference between ambient lighting and light
 - why ratio 0.2?, what does this actually mean?

--------------------------------------------------------

		**C = camera**
		--------------

->		Identifier:					C

->		Coordinates of View Point:	-50.0,0,20
	x-axis -		left-right
	y-axis -		up-down
	z-axis -		forward-back forward

->		3D vector:					0,0,1
	Normalized Orientation Vector
	range - [-1,1]
	for each axis: x y z - 0.0,0.0,1.0

-> 		FOV:						70
	Horizontal Field of View
	in degrees
	range - [0,180] = 70


NOTES

 - what Horizontal Field of View?
 - what Normalized Orientation Vector?
 - why FOV 70?

--------------------------------------------------------

		**L = light**
		-------------

->		Identifier:					L

->		Coordinates Light Point:		-40.0,50.0,0.0
	x y z  - -40.0,50.0,0.0

->		Brightness Ratio:			0.6
	range - [0.0,1.0]

->		R, G, B:					10,0,255
	range - [0,255]


NOTES

 - light point being like a spot light?
 - why brightness ratio 0.6?

--------------------------------------------------------

		**SP = sphere**
		---------------

->		Identifier:					SP

->		Coordinates Sphere center:	0.0,0.0,20.6

->		Sphere diameter:			12.6

->		R, G, B:					10,0,255
	range - [0,255]


NOTES

 - Coordinates center of sphere center - differ from cylinder center?

--------------------------------------------------------

		**PL = plane**
		--------------

->		Identifier:					PL

->		Coordinates point in plane:	0.0,0.0,-10.0

->		3D vector:					0.0,1.0,0.0
	3D normalized normal vector
	range - [-1,1] for each axis

->		R, G, B:					0,0,255
	range - [0,255]


NOTES

 - coorindates point in plane??
 - 3D normalized normal vector?

--------------------------------------------------------

		**CY = cylinder**
		-----------------

->		Identifier:					CY

->		Coordinates center of cylinder:	50.0,0.0,20.6

->		3D vector:					0.0,1.0,0.0
	3D normalized vector of axis of cylinder
	range: [-1,1] for each axis

->		cylinder diameter:			14.2

->		cylinder height:			21.42

->		R, G, B:					10,0,255
	range - [0,255]


NOTES

 - Coordinates center of cylinder center - differ from sphere center?
 - 3D normalized vector of axis of cylinder... what?

--------------------------------------------------------


--------------------------------------------------------

// Jovi's og parser function + test file with comments

// void ft_parse_input(int argc, char **argv, t_data *data)
// {
//     (void)argc;
//     (void)argv;

//     // check_file() // Check valid input and put everything in the struct.
//     data->viewport_H = 600;
//     data->viewport_W = 800;

//     // Ambient lightning (A): 
//     data->ambient.ratio = 0.2;
//     data->ambient.colour.r = 255;
//     data->ambient.colour.g = 255;
//     data->ambient.colour.b = 255;

//     // Camera (C): 
//     data->camera.place.x = -50.0;
//     data->camera.place.y = 0;
//     data->camera.place.z = 20;
//     data->camera.vector.x = 0;
//     data->camera.vector.y = 0;
//     data->camera.vector.z = 1;
//     data->camera.FOV = 70;

//     // Light (L):
//     data->light.place.x = -40.0;
//     data->light.place.y = 50.0;
//     data->light.place.z = 0.0;
//     data->light.ratio = 0.6;
//     data->light.colour.r = 10;
//     data->light.colour.g = 0;
//     data->light.colour.b = 255;

//     // Sphere (sp):
//     data->objects.sphere.center.x = 0.0;
//     data->objects.sphere.center.y = 0.0;
//     data->objects.sphere.center.z = 20.6;
//     data->objects.sphere.diameter = 12.6;
//     data->objects.sphere.colour.r = 10;
//     data->objects.sphere.colour.g = 0;
//     data->objects.sphere.colour.b = 255;

//     // Plane (pl): 
//     data->objects.plane.center.x = 0.0;
//     data->objects.plane.center.y = 0.0;
//     data->objects.plane.center.z = -10.0;
//     data->objects.plane.vector.x = 0.0;
//     data->objects.plane.vector.y = 1.0;
//     data->objects.plane.vector.z = 0.0;    
//     data->objects.plane.colour.r = 0;
//     data->objects.plane.colour.g = 0;
//     data->objects.plane.colour.b = 255;

//     // Cylinder (cy):
//     data->objects.cylinder.center.x = 50.0;
//     data->objects.cylinder.center.y = 0.0;
//     data->objects.cylinder.center.z = 20.6;
//     data->objects.cylinder.vector.x = 0.0;
//     data->objects.cylinder.vector.y = 0.0;
//     data->objects.cylinder.vector.z = 1.0;
//     data->objects.cylinder.diameter = 14.2;
//     data->objects.cylinder.height = 21.42;
//     data->objects.cylinder.colour.r = 10;
//     data->objects.cylinder.colour.g = 0;
//     data->objects.cylinder.colour.b = 255;
// }



# Ambient lightning (A): 
#Identifier     #Ratio        #R,G,B
A               0.2           255,255,255

# --------------------------------------------------------------------------------------------
# Camera (C): 
#Identifier    #Coordinates         #3D vector     #FOV
C              -50.0,0,20           0,0,1          70

# --------------------------------------------------------------------------------------------
# Light (L):
#Identifier     #Coordinates        #Ratio      #R,G,B
L               -40.0,50.0,0.0      0.6         10,0,255

# --------------------------------------------------------------------------------------------
# Sphere (sp):
#Identifier     #Coordinates        #Diameter       #R,G,B
sp              0.0,0.0,20.6        12.6            10,0,255

# --------------------------------------------------------------------------------------------
# Plane (pl): 
#Identifier     #Coordinates        #3D vector      #R,G,B
pl              0.0,0.0,-10.0       0.0,1.0,0.0     0,0,225

# --------------------------------------------------------------------------------------------
# Cylinder (cy):
#Identifier     #Coordinates        #3D vector      #Diameter       #Height     #R,G,B
cy              50.0,0.0,20.6       0.0,0.0,1.0     14.2            21.42       10,0,255

