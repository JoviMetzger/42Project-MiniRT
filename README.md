# MiniRT

Welcome to MiniRT. <br> <br>
This project was made in collaboration with [Sarah Mclacke](https://github.com/smclacke). <br>
MiniRT is about a ray-tracing engine that renders realistic 3D computer-generated images through ray-tracing techniques. <br>

## Table of Contents

- [Building a Ray Tracer](#Building-a-Ray-Tracer)
- [Checkerboard](#Checkerboard)
- [Light](#Light)
- [Shadow](#Shadow)
- [Important Things to Know](#Important-Things-to-Know)
- [Installation](#Installation)
- [Resources](#Resources)

<br>

eVerYTinG bEloW tHiS liNe wAs ME gOiNg ["hhhUUUUUhhhhhh?????????????"](https://www.youtube.com/watch?v=xVWeRnStdSA) (aka. cat meme)
			
![images]()


<br> <br>

## Building a Ray Tracer
A ray tracer works a bit differently than your eye. <br>
Ray tracing simulates how rays of light interact with objects to produce realistic images. <br>
Unlike how our eyes work, which detect light coming from objects, <br>
a ray-tracing algorithm traces rays from the camera (the "eye") into the scene, <br>
determining which objects they hit and rendering the scene accordingly. ["hUh??"](https://www.youtube.com/watch?v=xVWeRnStdSA) moment
![](https://www.researchgate.net/figure/1-This-figure-demonstrates-the-concept-of-ray-tracing-A-ray-is-cast-from-the-camera_fig1_236342499)
 
**You get 3 main steps to building a ray tracer:**
 - [Step 1)](#Step-1-;) &nbsp; Calculate the ray from the “eye” through the pixel, <br>
			&nbsp;&nbsp;&nbsp; ⇾ Set up your camera and calculate a ray per pixel (width x height).
 - [Step 2)](#Step-2-;) &nbsp; Determine which objects the ray intersects,	<br>
			&nbsp;&nbsp;&nbsp; ⇾ Calculate your intersection points with each object (safe that information in a struct)
 - [Step 3)](#Step-3-;) &nbsp; Compute a color for the closest intersection point. <br>
			&nbsp;&nbsp;&nbsp; ⇾ Calculate, with the Phong reflection model, your light per light source and shadow.

#### Step 1;

**Understanding the 3D grid:** <br>
You get 2D grid, which only have x and y coordinates. `Coordinates(x, y)` <br>
And you get a 3D grid, which has x, y and z coordinates. `Coordinates(x, y, z)` <br>
	- `x: left/right`
		⇾ **+x/**x = right *(positive numbers)* ***||*** **-x** = left *(negative numbers)*
	- `y: up/down`
		⇾ **+y/y** = right *(positive numbers)* ***||*** **-y** = left *(negative numbers)*
	- `z: forward/back forward`
		⇾ **+z/z** = right *(positive numbers)* ***||*** **-z** = left *(negative numbers)* <br>

First do **x**, then **y**, then **z**. <br>
So we first walk *(x)* left or right, then we go *(y)* up or down, then we go *(z)* forward or back forward. <br>
*Some people switch* **y** *and* **z***, so* **y** ***=*** *forward and back forward and* **z** ***=*** *up and down, but do it how it makes sense for you.* <br> <br>

Online 3D grid for visualizing: [3D-Graph](https://technology.cpm.org/general/3dgraph/)


**How do I set up the ray?:** <br>
	- 1. Set up the  width, height and image ratio of the window/image.
		image_width and image_height you can choose yourself. *(a nice size: ****WIDTH = 1800****; and ***HEIGHT = 1900****;)*
		`image_ratio = image_height / image_width;`
	- 2. Calculate the viewport, so what your imaginary camera sees.
		pos_x and pos_y is at what pixel you are currently.
		`viewport_w = 2 * ((pos_x + 0.5) / image_width) - 1;`
		`viewport_h = (1 - 2 * ((pos_y + 0.5) / image_height)) * image_ratio;`
	- 3. Calculate each delta pixel.
		**M_PI** ⇾ This is a constant representing the value of pi. ***(M_PI = 3.14159265358979323846)***
		`pixel_x = viewport_w * (tan((fov / 2) * (M_PI / 180)));`
		`pixel_y = viewport_h * (tan((fov / 2) * (M_PI / 180)));`
	- 4. Initialize the ray vector and the ray place.
		Make sure your camera vector works, in other words, make sure your camera can rotate.
		We did it like this; it's not the most correct way, but it works ***(if it works, don't tough it)***
		```C
		forward = normalize(camera.vector);
		-------------------------------------

		/* Camera vector(x,y,z)
		* - If camera vector(0,1,0) -> (fabs(forward.y) == 1.0)
		* 	- We give it init_ray_pos(1, 0, 0).
		* - In anyother case it will stay init_ray_pos(0, 1, 0).
		*/
		if (fabs(forward.y) == 1.0)
			right = normalize(cross_product(forward, init_ray_pos(1, 0, 0)));
		else
			right = normalize(cross_product(forward, init_ray_pos(0, 1, 0)));

		-------------------------------------
		up = cross_product(right, forward);
		pixel_direction = plus(plus(scale_vector(right, screen.pixel_delta_x),
			scale_vector(up, screen.pixel_delta_y)), forward);
		return (normalize(pixel_direction));
		```

<br> <br>

#### Step 2;
	For intersecting objects, you get different options and examples online, take the one that makes most sense for you. <br>
	`Sphere`, start with the sphere, it is the easiest. *(Plenty examples online)* <br>
		- Do camera, screen testing with the sphere: 
			- Check for distortion at the edges of the screen.
			- Make sure you understand how your grid/position of objects works.
			- Make sure, if you have two spheres next to each other, that they intersect correctly with each other..
			![]()
	`Plane` is easy as well. <br>
		- Make sure you understand that a plane is infinite.
		- Make sure if you change the vector that all vector directions work.
		- It is very important to make sure that the surface normal is correct; otherwise later, the light might give you problems.
	`Cylinder` is a b**ch! <br>
		- Cylinders consist out of two or three objects. The body and the two caps.
		- The body ⇾ it will be in the beginning infinite, so you need to cut/trim it at the correct height.
		- The caps are two planes, that are trimmed/cut as well.
			- Make sure the caps are perfectly on the body, sometimes there is space in between cap and body, you will see the space once you added light.
			- Make sure the surface normal of the caps is correct.
		- Make sure all vector directions work correctly (look correct)
		![]()
	Make sure you have all the objects, before adding light. <br>
	Make sure you take the object closest to the camera. (Or do this in step 3) <br>

<br> <br>
#### Step 3;
	Look at the [light](#Light) and [shadow](#shadow) sections.
	Make sure you take the object closest to the camera. (If you haven't in step 2)
	Check all surface normals, sometimes they cause problems with the light.
	**For example;**
	a Plane below a light source has the correct lighting, but a plane above a light source has no light at all.
	**If that happens:** flip the surface normal of the plane above (make the surface normal positive), so it shows the light.
	```C
	cyl->normal = mult_vecdub(cyl->vector, -1); // Surface normal points downwards -> mult_vecdub() = multiplying a vector and a duble
	cyl->normal = cyl->vector; 					// Surface normal points upwards
	```

<br>
<br>

## Checkerboard
It is not possible to create a sphere with a perfect checkerboard! <br>
If the checked sphere looks good from the center, check the sides; there will be distortion. <br>
So rather calculate a checkerboard sphere that touches at the poles. <br>
Or make a texture that rotates towards the camera, so it always looks good. <br>
![](perfect and real checkerboard)
<br>
<br>


## Light
*(A lot of ["hUh??"](https://www.youtube.com/watch?v=xVWeRnStdSA) moments)* <br>
**Calculating lighting on an object involves several steps:** <br>
- calculating the direction of light rays,
- determining the visibility of the light source from the surface point of the object. [(Shadow part)](#Shadow)
- and then applying illumination models such as [Phong](https://en.wikipedia.org/wiki/Phong_reflection_model) or [Blinn-Phong](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model) to compute the final color of the object.
<br>
**Calculate Light Direction:** <br>
Determine the direction of light rays from the light source(s) to the surface point of the object. <br>
If the light source is directional *(like the sun)*, you only need the direction vector.  <br>
If the light source is a point light, you'll need to calculate the direction vector from the surface point to the light source position. <br>
<br>
**Check Visibility:** <br>
Determine if the surface point of the object is in shadow or not. <br>
<br>
**Compute Illumination:** <br>
Apply an illumination model *(such as [Phong](https://en.wikipedia.org/wiki/Phong_reflection_model) or [Blinn-Phong](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model))* to compute the final color of the object at the surface point. <br>
This involves calculating ambient, diffuse, and specular components based on the surface properties, light properties, and view direction. <br>
<br>
You go through each object and each object goes through each light.  <br>
**for example you have:** 2 objects, 3 lights. <br>
object**1** will be caclulated with light*1*, light2*,* light*3* <br>
then, object**2** will be calculated with light*1*, light*2*, light*3* <br>

```c
while (++i < Number_of_objects)
{
	while (++k < Number_of_lights)
	{
		- For each light we get:
			- intersection_point,
			- light_direction,
			- current light information (You need the colour, position and ratio of the current light)
		if (Shadow)
		{
			- Shadow -> visibility of the light source from the surface point of the object.
		}
		else
		{
			- Phong reflection model
				- Ambient Light (General illumination in the scene)
				- Diffuse Light (Direct light from the source)
				- vSpecular Light (Highlights on shiny surfaces)
		}
	}
	- Clamp Light result, so the rgb colours don't overflow, if it overflows it prints black.
}
```

Make sure for your Phong reflection model that your base colour is calculated before you do diffuse and spectular light. <br>
Else your texture (Checkerboard) won't have light and shadow. <br>
<br>
We used Phong reflection model, because it was easier to visulize what was happening, but you also could use Blinn-Phong reflection model.
![Phong reflection model](https://en.wikipedia.org/wiki/Phong_reflection_model#/media/File:Phong_components_version_4.png)
<br>
<br>


## Shadow
**Check Visibility:** <br>
Determine if the surface point of the object is in shadow or not. <br>
You can achieve this by casting a shadow ray from the surface point towards the light source and checking if it intersects with any other object in the scene. <br>
If it intersects, the surface point is in shadow; otherwise, it's light. <br><br>
So, instead calculating what makes logical sence, to calculate a ray from the light to the object, you need to calculate a ray from the object to the light. *More ["hUh??"](https://www.youtube.com/watch?v=xVWeRnStdSA) moments* <br>
If the ray *(on the way to the light)* hits another object, shodow will be drawn. If the ray makes it susscesfully to the light, light/Illumination will be calculated.<br>
![Shadow ray](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/ligth-and-shadows.html)

<br>
<br>

## Important Things to Know

<details>
  <summary><strong>Filed of view (FOV)</strong> <br> &nbsp;&nbsp;&nbsp;<em>(<strong>Filed of view (FOV)</strong>)</em></summary>
  <br>

### Filed of view (FOV)
- between 70 and 90 is the sweet spot. Less or more will distort the image.
- Distortion will always happen near the edges of the image.

br>
<br>

</details>

---

<details>
  <summary><strong>Normalizing a vector</strong> <br> &nbsp;&nbsp;&nbsp;<em>(<strong>Normalizing a vector -></strong> Decimal numbers (0.0))</em></summary>
  <br>

### Normalizing a vector -> Decimal numbers (0.0) 
- Your number input (excluding rgb) need to take decimal numbers.
- Thats why we normalize our vectors.
- The normalization process ensures that the vectors have a consistent scale or magnitude, 
which can be important in certain operations such as distance calculations, clustering, or classification.
- So normalize every vector, either in the beginning(while parsing) or every vector you entcounter durring your calculations.

br>
<br>

</details>

---

<details>
  <summary><strong>Selecting objects</strong> <br> &nbsp;&nbsp;&nbsp;<em>(<strong>Selecting objects</strong>)</em></summary>
  <br>

### Selecting objects
Selecting objects is not part of the project. We just thought it's a nice and esay way for the user/evaluater to click on a object and do something with it.

![]()

#### We only have the option: 
- You can select all objects, but you can only do something with the sphere.
- If a sphere is selected you can press arrow key up ![](https://www.google.com/search?sca_esv=adb58b67ff5950fb&sca_upv=1&q=keyboard+arrow+symbol&udm=2&fbs=AEQNm0Aa4sjWe7Rqy32pFwRj0UkWd8nbOJfsBGGB5IQQO6L3J_86uWOeqwdnV0yaSF-x2jopn8p7xL4A1Dm_DA2mNSwQf3Ts-oLed-fok38HK-L3touqFtv6wIt8FVCSDg7FOXl9BZhwvwkKnTuEN51hFYXnnYqV40IDAPbrBOsskslGNy0Z6pM&sa=X&ved=2ahUKEwj12M7CiuGIAxX4g_0HHRowIYgQtKgLegQIFxAB&biw=1442&bih=1133&dpr=1.5#imgrc=opwshXhf8vkFvM&imgdii=bQ-q1cgYYkpsiM) 
- It will then add the Checkerboard on the sphere.

#### You also could:
- Add more textures to the sphere or give other objects tectures aswell.
- Move and rotate objects.
- Make them bigger or smaller.


#### How does it work
you need mlx functions:
```C
 - mlx_key_hook(); 		-> is for key movement (ESC, Arrow up).
 - mlx_mouse_hook();	-> is for mouse movement (selcet objects).
```

Mouse movement (selcet objects):
Quick explanation how the mouse map works.
 - There is a 2D mouse_map[x][y].
 - While we loop through every pixel, we fill in this map.
 - If no object is at that position fill in -1.
 - If there is an object, give it a number (intersection point found).
 ```script
		Example:
				Sphere1 = 0; (red)
				Sphere2 = 1; (blue)
				Plane	= 2; (green)
		mouse_map:
				-1 -1 -1 -1 -1			⬛⬛⬛⬛⬛
				-1 -1  0 -1 -1			⬛⬛🟥⬛⬛
				-1  0  0  0 -1			⬛🟥🟥🟥⬛
				 0  0  0  0  0	  ->	🟥🟥🟥🟥🟥
				-1  0  0  0 -1			⬛🟥🟥🟥⬛
				-1 -1  0 -1  2			⬛⬛🟥⬛🟩
				-1 -1 -1  2  2			⬛⬛⬛🟩🟩
```
 - Find the position of the mouse, with mlx_get_mouse_pos();.
 - If the mouse map is -1 at that position, So no object has been selected.
 - Else if the mouse map is NOT -1 at that position. Highlight the object.
 - Just set/draw a white pixel with a bit of offset inwards next to the position.
 - For remove_highlight() remove the colour of the pixel (set it to 0).
 - How is that possible ☝️ ? 
 - Use mlx_image_to_window() to put a layer on top of the 'original'
 - It loads faster because it doesn't go through each pixel and recalculates everything.
 - That's why to remove_highlight(), you can set that colour to 0, so it will just unset those pixels.


Key movement (ESC, Arrow up):

🔴 - If the pressed key is 'ESC key', close and free window.
🟡 - If an object is selected and the key 'Arrow up' is pressed, we change the pattern of that object.
🟢 - You need to count how many arrow-ups you have. Because arrowUp-1 should change pattern, arrowUp-2 should change to a different pattern or original form. After that, you need to reset your arrow-up count
🔵 - Change the pattern of that object. 

```C
void	ft_key_action(mlx_key_data_t keydata, t_data *data)
{
	(void)keydata;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE)) 🔴
		mlx_close_window(data->mlx);
	if (data->mouse.selected == true && mlx_is_key_down(data->mlx, MLX_KEY_UP)) 🟡
	{
		data->objs[data->i_am]->i++;
		if (data->objs[data->i_am]->i > 1) 🟢
			data->objs[data->i_am]->i = 0;
		change_pattern(data, data->objs[data->i_am]); 🔵
	}
}
```

```C
void	change_pattern()
{
	- Check what type the object is : if (obj->type == E_SPHERE)
	{
		- if (obj->i == 1) -> is for Checkerboard. (obj->what_pattern = 1)
		- else -> is for Normal. (obj->what_pattern = 0)
		- go through each pixel again and redo calculations (🚩 I Don't recommand 🚩)
	}
}
```
🚩 : BECAUSE: you recalculate all pixels, it will take a while.
			  It would be wiser to use mlx_image_to_window() to put a layer on top of the 'original'.
			  In the very beginning, initialize all pixels and store that information for each pixel in a pixel struct (object, distance, colour, light, etc.)
			  Reuse that pixel struct, so you don't need to recalculate everything.
			  It's also easier for if you want object rotation, so the original information is saved, and you can access it fast.  

<br>
<br>

</details>

---

<details>
  <summary><strong>About Colour</strong> <br> &nbsp;&nbsp;&nbsp;<em>(<strong>About Colour</strong>)</em></summary>
  <br>

### About Colour
Use this webside you find you rgb colours -> [RGB Color Picker](https://rgbacolorpicker.com/) <-
You can pick your colour and it will give you the rgb number.
<br>
<br>

Check that your colour overlapping is correct.
![](https://www.google.com/imgres?q=3%20colored%20lights%20on%20an%20object&imgurl=https%3A%2F%2Fwww.exploratorium.edu%2Fsites%2Fdefault%2Ffiles%2FRGB_screen.gif&imgrefurl=https%3A%2F%2Fwww.exploratorium.edu%2Fsnacks%2Fcolored-shadows&docid=Nzp0duVI3UF6RM&tbnid=gZrFqPSCteUEVM&vet=12ahUKEwig4YGW_oCIAxU7wAIHHQvQKqUQM3oECDIQAA..i&w=1080&h=612&hcb=2&ved=2ahUKEwig4YGW_oCIAxU7wAIHHQvQKqUQM3oECDIQAA)
![](mine)

br>
<br>

</details>

---

<details>
  <summary><strong>'.rt' file</strong> <br> &nbsp;&nbsp;&nbsp;<em>(<strong>template</strong> Just a example)</em></summary>
  <br>

Minirt.rt file
```script

# Ambient lightning (A): 
#Identifier     #Ratio        #R,G,B
A               0.2           255,255,255

# --------------------------------------------------------------------------------------------
# Camera (C): 
#Identifier    #Coordinates         #3D vector     #FOV
C              0,0,-1     		    0,0,1          70

# --------------------------------------------------------------------------------------------
# Light (L):
#Identifier     #Coordinates        #Ratio      #R,G,B
L               2,2,0  				0.6         255,255,255

# --------------------------------------------------------------------------------------------
# Sphere (sp):
#Identifier     #Coordinates        #Diameter       #R,G,B
sp              0,0,-10     		12.6            10,0,255

# --------------------------------------------------------------------------------------------
# Plane (pl): 
#Identifier     #Coordinates        #3D vector      #R,G,B
pl              10,3,-10     		0,1,0  			0,0,225

# --------------------------------------------------------------------------------------------
# Cylinder (cy):
#Identifier     #Coordinates        #3D vector      #Diameter       #Height     #R,G,B
cy              -5,0,-5      		0,0,1    		14.2            21.42       10,0,255

# --------------------------------------------------------------------------------------------
# Triangle (tr) -> optional:
#Identifier     #Coordinates1       #Coordinates2   #Coordinates3   #R,G,B
tr           	-7,6,-11         	-7,-6,-11       10,0,-11     	255,102,102


```
<br>
<br>

</details>
<br>
<br>


## Installation

To execute the program, follow the steps below:

1. Compile the RayTracer by running the following command:
```bash
$ make
```
2. Finally, execute the program using the following command: 
```bash
$ ./miniRT <scenes/sphere/sphere_circle_back.rt>
```

<br>
<br>

## Resources

- Ray Tracing
	- [Ray Tracing on Wikipedia](https://nl.wikipedia.org/wiki/Raytracing)
	- [NVIDIA Ray Tracing Resources](https://developer.nvidia.com/discover/ray-tracing)
	- [Ray Tracing in One Weekend - Book](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
	- [Minimal Ray Tracer: Seting up the Camera & Rendering Spheres](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/minimal-ray-tracer-rendering-spheres.html)
	- [CMU Lecture on Ray Tracing](https://www.cs.cmu.edu/afs/cs/academic/class/15462-s09/www/lec/04/lec04.pdf)
	- [CMU Graphics Course Ray Tracing Slides](http://graphics.cs.cmu.edu/nsp/course/15-462/Spring04/slides/13-ray.pdf)

- C Library Math Functions
	- [C Library: <math.h> Functions on GeeksforGeeks](https://www.geeksforgeeks.org/c-library-math-h-functions/)
	- [C Standard Library: <math.h> Functions on TutorialsPoint](https://www.tutorialspoint.com/c_standard_library/math_h.htm)

- Shading & Lighting
	- [Introduction to Shading: Light and Shadows](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/ligth-and-shadows.html)
	- [RGB Color Picker](https://rgbacolorpicker.com/)
	- [Phong reflection model](https://learnopengl.com/Lighting/Basic-Lighting)
	- [Ambient Light, Diffuse Light, Spectular Light code example](https://learnwebgl.brown37.net/09_lights/lights_combined.html)

- Troubleshooting & Tips
	- [Correcting Fisheye Effect in Ray Casting - GameDev Stack Exchange](https://gamedev.stackexchange.com/questions/156842/how-can-i-correct-an-unwanted-fisheye-effect-when-drawing-a-scene-with-raycastin/156853#156853)
	- [Fixing Fisheye Distortion in Raycast Renderer - GameDev Stack Exchange](https://gamedev.stackexchange.com/questions/97574/how-can-i-fix-the-fisheye-distortion-in-my-raycast-renderer)

<br>
<br>

		



<!--


WEBSERV
Webserv

This project is made in collabaration with [Adri Rommers](https://github.com/arommers) and [Sven van Hasselt](https://github.com/svenvanhasselt)
This project is all about creating your own HTTP server, a fundamental piece of the internet's backbone. <br>
By building it yourself, you’ll see how the Hypertext Transfer Protocol (HTTP) drives the web, <br>
allowing browsers to communicate with servers to fetch and display web pages.


![image]

## Table of Contents

- [About](#About)
- [Server](#Server)
- [Request & Response](#Request & Response)
- [CGI](#CGI)
- [Configuration File](#Configuration File)
- [Configuration Parser](#Configuration Parser)
- [Installation](#Installation)
- [Resources](#Resources)



## About
The goal of the project is to build a C++ compatible HTTP web server from scratch. 
The web server can handle HTTP GET, POST, and DELETE Requests, 
and can serve static files from a specified root directory or dynamic content using CGI.

### HTTP (Hypertext Transfer Protocol)
HTTP (Hypertext Transfer Protocol) is a protocol for sending and receiving information over the internet. 
It is the foundation of the World Wide Web (www) and is used by web browsers and web servers to communicate with each other. 
When you click a link or submit a form, your browser sends an HTTP request, 
and the server responds with the content you need—or an error message if something goes wrong.

HTTP consists of requests and responses: When a client (such as a web browser) wants to retrieve a webpage from a server, 
it sends an HTTP request to the server. The server then processes the request and sends back an HTTP response.

```bash
								HTTP Message can be either 
								   a request or response.
									  /				\
									 /				 \
									/				  \
------------------------------------			  	   ------------------------------------
	HTTP request:															HTTP response:
	consists of a 															consists of a
	- request line,															- status line,
	- headers,																- headers,
	- optional message body.												- optional message body.
Example:																Example:
GET /index.html HTTP/1.1												HTTP/1.1 200 OK
Host: localhost:8080													Content-Type: text/html
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)					Content-Length: 1234
																		<Message Body>
------------------------------------------------------------------------------------------
```
									HTTP Request States:

Either the client or the server may exchange messages using any HTTP request method. 
The choice of method affects the state between the client and server. 
GET (read-only request) requests do not alter the server’s state, while POST and DELETE can.

 - GET : The path to resource (e.g. /index.html). 
	     In case of success (or non-error), GET returns a representation of the resource
		 in response body and HTTP response status code of 200 (OK). 
	     In an error case, it most often returns a 404 (NOT FOUND) or 400 (BAD REQUEST).

- POST : POST method is most often utilized to create new resources. 
		 On successful creation, HTTP response code 201 (Created) is returned.

- DELETE : It deletes a resource specified in URI. 
		   On successful deletion, it returns HTTP response status code 204 (No Content).


## Server

Server Core: 
Responsible for the low-level networking, such as creating and managing sockets, handling input and output streams, and managing the flow of data between the server and clients.
Socket programming:
Socket : mechanism to give programs access to the network
- create a socket with socket()
- identify the socket with bind()
- wait for a connection with listen() and accept()
- send and receive messages with read() and write() (or send() and recv())
- close the socket with close()


## Request & Response

Request:
The process that is responsible for interpreting and extracting information from HTTP requests. 
Receives an incoming request, parses it, and extracts the relevant information such as the method, path, headers, and message body(if present). 
If any syntax error was found in the request during parsing, error flags are set and parsing stops.
```bash
-----------------------------------------------------------------------------------------------------------------------------
													HTTP request:

	
	Request line:							Headers:									Optional message body:		
	consists of								contain additional 							- GET method usually doesn't
	- the method, 							information about the request				  include any body, most servers
	- the path, 							- the hostname of the server, 				  respond with information
	- the HTTP version.						- the type of browser being used.			  from the URI/URL requested.
-----------------------------------------------------------------------------------------------------------------------------	
`The method` specifies the action
that the client wants to perform,
such as GET (to retrieve a resource) 
or POST (to submit data to the server)
-----------------------------------------------------------------------------------------------------------------------------
`The path` or URI specifies the location 
of the resource on the server.
-----------------------------------------------------------------------------------------------------------------------------
`The HTTP version` indicates the version
of the HTTP protocol being used.
-----------------------------------------------------------------------------------------------------------------------------
```

Response:
The response is responsible for constructing and formatting the HTTP responses that are sent back to clients in response to their requests. 
Building and storing the HTTP response, including the status line, headers, and message body. 
The response builder may also perform tasks such as setting the appropriate status code and reason phrase based on the result of the request, 
adding headers to the response to provide additional information about the content or the server, 
and formatting the message body according to the content type and encoding of the response. 
```bash
------------------------------------------------------------------------------------------------------------------------------------
														HTTP response:


	Status line:							 Headers:									  Optional message body:
	consists of								 contain additional 						  - The message body contains the actual	
	- the HTTP version, 					 information about the response				    content of the response,
	- the status code, 						 - the type and size						    such as the HTML code for a webpage.
											   of the content being returned.
------------------------------------------------------------------------------------------------------------------------------------				 	
The status code indicates 
the result of the request,
such as 200 OK (successful) 
or 404 Not Found (resource not found). 
The reason phrase is 
a short description of the status code.
   ----------------------------
Responses are grouped in five classes:
(https://developer.mozilla.org/en-US/docs/Web/HTTP/Status)
Informational responses (100 – 199)
Successful responses (200 – 299)
Redirection messages (300 – 399)
Client error responses (400 – 499)
Server error responses (500 – 599)
------------------------------------------------------------------------------------------------------------------------------------
```


## CGI

CGI:
CGI is a standard for running external programs from a web server. 
When a user requests a web page that should be handled by a CGI program, 
the web server executes the program and returns the output to the user's web browser.
CGI programs are simply scripts that can be written in any programming language, such as Perl, Python, or bash, 
and are typically used to process data submitted by a user through a web browser, or to generate dynamic content on a web page.


## Configuration File

Configuration file is a text file that contains various settings and directives that dictate how the web server should operate. 
Could use nginx as example for testing.
nginx [engine x]:
NGINX is open source software for web serving, reverse proxying, caching, load balancing, media streaming, and more. 
It started out as a web server designed for maximum performance and stability. 
In addition to its HTTP server capabilities, NGINX can also function as a proxy server for email (IMAP, POP3, and SMTP) and a reverse proxy and load balancer for HTTP, TCP, and UDP servers.

Default server block:
```bash
# --- All variables ---
server {
	server_name		=	W3bMasters						# Name of server
	port 			=	8080							# Listen on port for incoming connections
	host			=	127.0.0.1						# Server block will respond to requests for localhost (or (127.0.0.1))
	root			=	/www/html						# Sets the root directory for this server block
	max_client_size =	5000000							# File upload limit is 5MB -> 5000000
	index			=	/index.html		 				# File to serve when a server running (Main web page)
	error_page 400 	=	/config/error_page/400.html		# Files to serve when a error occurs
	error_page 403 	=	/config/error_page/403.html 
	error_page 404 	=	/config/error_page/404.html
	error_page 405 	=	/config/error_page/405.html
	error_page 406 	=	/config/error_page/406.html
	error_page 409 	=	/config/error_page/409.html
	error_page 410 	=	/config/error_page/410.html
	error_page 500 	=	/config/error_page/500.html
	error_page 505 	=	/config/error_page/505.html

	# Handles requests to the root URL '/cgi-bin' -> first location block context 
	location /cgi-bin {
		allowed_methods = POST GET DELETE				# Allowed_methods for that location Block
		root			= /www
	}
	
	# Handles requests to the root URL '/' -> second location block context
	location / {
		index 	= /index.html							# Specifies the default file to serve in this location
		return	= 301 <URL>								# For redirecting this to a specific page <URL> can be any http-page (https://en.wikipedia.org/wiki/42_(number))
	}

	# Handles requests to the root URL '/img' -> third location block context
	location /img {
		root		= /www/html							# Local pathing to what directory should be served in this location Block
		autoindex	= on 								# Turns off/on directory listing. -> showes/listing of directories
	}
}
```

Test Server blocks:

# Test 1 : Location Block with a valid autoindex (list of directories)
server {
	server_name		=	TestServer
	port 			=	8080
	host			=	localhost
	root			=	/www/html
	index			=	/index.html

	location /img {
		root		= /www/html
		autoindex	= on 
	}
}
=> How to test: Web browser URL -> localhost:8080/img/


# Test 2 : Location Block with a invalid root (output '404 error')
server {
	server_name		=	TestServer
	port 			=	8080
	host			=	localhost
	root			=	/www/html

	location /cgi-bin {
		root 			= /test
	}
}
=> How to test: Web browser URL -> localhost:8080


# Test 3 : different index & No Location block (should display index1.html)
server {
	server_name		=	TestServer
	port 			=	7070
	host			=	localhost
	index			=	/index1.html
	root			=	/www/html1
}
=> How to test: Web browser URL -> localhost:7070


# Test 4 : Test Redirects
server {
	server_name		=	TestServer
	port 			=	6060
	host			=	localhost
	root			=	/www/html1
	index			=	/index1.html

	location /img {
		root		= /www/html
		return		= 301 https://en.wikipedia.org/wiki/42_(number)
	}
}
=> How to test: Web browser URL -> localhost:6060 (should go to the redirect URL, in this case to 'https://en.wikipedia.org/wiki/42_(number)')


# Test 5 : Test server_name (curl --resolve TestServer:8080:127.0.0.1 http://TestServer:8080/index.html -v)
server {
	server_name		=	TestServer
	port 			=	8080
	host			=	localhost
	root			=	/www/html
	index			=	/index.html
}
=> How to test: open second terminal (same folder as currecnt one) -> `$ curl --resolve TestServer:8080:127.0.0.1 http://TestServer:8080/index.html -v`
Output example:
```bash
1		* Added TestServer:8080:127.0.0.1 to DNS cache
2		* Hostname TestServer was found in DNS cache
3		*   Trying 127.0.0.1:8080...
4		* Connected to exampletest (127.0.0.1) port 8080 (#0)
5		> GET /index.html HTTP/1.1
6		> Host: TestServer:8080
7		> User-Agent: curl/7.81.0
8		> Accept: */*
9		> 
10		* Mark bundle as not supporting multiuse
11		< HTTP/1.1 200 Found
12		< Content-Type: text/html
13		< Content-Length: 1139
14		< 
15		<!DOCTYPE html>
16		<head>
17		    <meta charset="UTF-8">
18		    <meta name="viewport" content="width=device-width, initial-scale=1.0">
19		    <title>404 Not Found</title>
20		    <style>
21		        body {
22		            font-family: Arial, sans-serif;
23		            display: flex;
24		            justify-content: center;
25		            align-items: center;
26		            height: 100vh;
27		            margin: 0;
28		            background-color: #fff;
29		        }
30		        .container {
31		            text-align: center;
32		            padding: 20px;
33		            background-color: #fff;
34		        }
35		        .error-code {
36		            font-size: 9em;
37		            font-weight: bold;
38		            margin-bottom: -0.1em;
39		            color: #333;
40		        }
41		        h1 {
42		            font-size: 2em;
43		            margin-bottom: 0.1em;
44		            color: #333;
45		        }
46		        p {
47		            font-size: 1em;
48		            margin-bottom: 1em;
49		            color: #666;
50		        }
51		    </style>
52		</head>
53		<body>
54		    <div class="container">
55		        <div class="error-code">404</div>
56		        <h1>Not Found</h1>
57		        <p>The requested resource could not be found on the server!</p>
58		    </div>
59		</body>
60		* Connection #0 to host exampletest left intact
61		</html>% 
```
Line 11 : `< HTTP/1.1 200 Found` -> displayes the responds code, so also coud be `< HTTP/1.1 404 Not Found`
Line 15+ : `<!DOCTYPE html>` -> Onward is the index.html file that the browser is displaying, so might look different -> `< HTTP/1.1 404 Not Found` will display the 404_ErrorPage.html file


## Configuration Parser

Ports, in the context of computer networking, are identified by port numbers, which range from 0 to 65535. This range means that port numbers can be up to five digits long. Here is a breakdown of the port number ranges:

Well-Known Ports (0 to 1023): These ports are reserved for system or well-known services and protocols (e.g., HTTP uses port 80, FTP uses port 21).

Registered Ports (1024 to 49151): These ports are assigned by the Internet Assigned Numbers Authority (IANA) for user processes or applications.

Dynamic or Private Ports (49152 to 65535): These ports are used for private or temporary purposes, often assigned dynamically to client applications when they connect to a network service.

So, ports can be 1 to 5 digits long, but they must fall within the 0 to 65535 range.


## Installation
1. Compile the program by running the following command:
```bash
$ make
```
2. Execute the program using the following command:
```bash
$ ./webserv
```
or
```bash
$ ./webserv <configuration file your choice>
```
3. The program is now running. Go to your web browser:
![image] 

![Video]

## Resources

- NGINX Resources
	- [Official NGINX Website](https://nginx.org/en/)
	- [NGINX Blog: HTTP/2 Theory and Practice](https://blog.nginx.org/blog/http2-theory-and-practice-in-nginx-stable-13)
	- [NGINX Configuration Examples](https://kbeezie.com/nginx-configuration-examples/)

- Node.js and HTTP Servers
	- [Node.js HTTP Module Documentation](https://nodejs.org/api/http.html)

- HTTP Protocol
	- [TechTarget: What is an RFC?](https://www.techtarget.com/whatis/definition/Request-for-Comments-RFC)
	- [Linode Guide: HTTP GET Request](https://www.linode.com/docs/guides/http-get-request/)
	- [MDN: HTTP Status Codes](https://developer.mozilla.org/en-US/docs/Web/HTTP/Status)



-->
