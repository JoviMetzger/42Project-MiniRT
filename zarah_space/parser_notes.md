
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


