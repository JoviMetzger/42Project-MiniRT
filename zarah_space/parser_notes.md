
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
