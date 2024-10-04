# 🔸🔻 MiniRT 🔻🔸
**Welcome to MiniRT** <br> <br>
This project was made in collaboration with 🌈 [Sarah Mclacke](https://github.com/smclacke) 🌈 <br>
MiniRT is about a ray-tracing engine that renders realistic <br>
3D computer-generated images through ray-tracing techniques. <br>

## Table of Contents

- [Building a Ray Tracer](#Building-a-Ray-Tracer)
- [Checkerboard](#Checkerboard)
- [Light](#Light)
- [Shadow](#Shadow)
- [Important Things to Know](#Important-Things-to-Know)
- [Installation](#Installation)
- [Resources](#Resources)

<br>

<small><sup>eVerYTinG bEloW tHiS liNe wAs ME gOiNg <a href="https://www.youtube.com/watch?v=xVWeRnStdSA">"hhhUUUUUhhhhhh?????????????"</a> <i>(aka. cat meme)</i></sup></small> <br>


![Screencast from 30-09-24 15-57-13](https://github.com/user-attachments/assets/1808e263-a0c8-4cfc-bb25-2b73f594d221)


<br> <br>

## 🧩Building a Ray Tracer
A ray tracer works a bit differently than your eye. <br>
Ray tracing simulates how rays of light interact with objects to produce realistic images. <br>
Unlike how our eyes work, which detect light coming from objects, <br>
a ray-tracing algorithm traces rays from the camera *(the "eye")* into the scene, <br>
determining which objects they hit and rendering the scene accordingly. <small><sup><i><a href="https://www.youtube.com/watch?v=xVWeRnStdSA">"hUh??"</a> moment</i></sup></small>

![This-figure-demonstrates-the-concept-of-ray-tracing-A-ray-is-cast-from-the-camera](https://github.com/user-attachments/assets/ebd05c2d-aa8f-4b2b-af66-dfd3ad3805dd)

 
**You get 3 main steps to building a ray tracer:**
 - Step 1) &nbsp;&nbsp; Calculate the ray from the “eye” through the pixel, <br>
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ⇾ Set up your camera and calculate a ray per pixel *(width x height)*.
 - Step 2) &nbsp;&nbsp; Determine which objects the ray intersects,	<br>
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ⇾ Calculate your intersection points with each object *(save that information in a struct)*
 - Step 3) &nbsp;&nbsp; Compute a color for the closest intersection point. <br>
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ⇾ Calculate, with the Phong reflection model, your light per light source and shadow.


<details>
  <summary><strong>Step 1;</strong></summary>

## 🖍️ Step 1

### 🎲 Understanding the 3D grid:
You get 2D grid, which only have x and y coordinates. `Coordinates(x, y)` <br>
And you get a 3D grid, which has x, y and z coordinates. `Coordinates(x, y, z)` <br>

- `x: left/right` <br>
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ⇾ **x** = right *(positive numbers)* **|** **-x** = left *(negative numbers)* <br>
- `y: up/down` <br>
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ⇾ **y** = right *(positive numbers)* **|** **-y** = left *(negative numbers)* <br>
- `z: forward/back forward` <br>
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ⇾ **z** = right *(positive numbers)* **|** **-z** = left *(negative numbers)* <br>

<br>
<img src="https://github.com/user-attachments/assets/675c4e96-4e7c-4c37-8241-e814f899eb87" alt="3D_Grid_Example" width="500"> <br> <br>

<small><sup>Online 3D grid for visualizing: <a href="https://www.desmos.com/3d">3D-Graph</a></sup></small> <br>


### 🎲 How do I set up the ray?:
- 1) &nbsp;&nbsp; Set up the  width, height and image ratio of the window/image. <br>
	&nbsp;&nbsp; image_width and image_height you can choose yourself. <small><sup><i>(a nice size: <strong>WIDTH = 1800</strong>; and <strong>HEIGHT = 1900</strong>;) </i></sup></small> <br>
	&nbsp;&nbsp; `image_ratio = image_height / image_width;` <br>
- 2) &nbsp;&nbsp; Calculate the viewport, so what your imaginary camera sees. <br>
	&nbsp;&nbsp; pos_x and pos_y is at what pixel you are currently. <br>
	&nbsp;&nbsp; `viewport_w = 2 * ((pos_x + 0.5) / image_width) - 1;` <br>
	&nbsp;&nbsp; `viewport_h = (1 - 2 * ((pos_y + 0.5) / image_height)) * image_ratio;` <br>
- 3) &nbsp;&nbsp; Calculate each delta pixel. <br>
	&nbsp;&nbsp; **M_PI** ⇾ This is a constant representing the value of pi. <small><sup><i><strong>(M_PI = 3.14159265358979323846)</strong></i></sup></small> <br>
	&nbsp;&nbsp; `pixel_x = viewport_w * (tan((fov / 2) * (M_PI / 180)));` <br>
	&nbsp;&nbsp; `pixel_y = viewport_h * (tan((fov / 2) * (M_PI / 180)));` <br>
- 4) &nbsp;&nbsp; Initialize the ray vector and the ray place. <br>
	&nbsp;&nbsp; Make sure your camera vector works, in other words, make sure your camera can rotate. <br>
	&nbsp;&nbsp; We did it like this; it's not the most correct way, but it works *(if it works, don't tough it)* <br>

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

</details>

---

<details>
  <summary><strong>Step 2;</strong></summary>

## 🖍️ Step 2

For intersecting objects, you get different options and examples online, <br>
take the one that makes most sense for you. <br>
`Sphere`, start with the sphere, it is the easiest. *(Plenty examples online)* <br>

- Do camera, screen testing with the sphere: <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ Check for distortion at the edges of the screen. <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ Make sure you understand how your grid/position of objects works. <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ Make sure, if you have two spheres next to each other, <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; that they intersect correctly with each other.

`Plane` is easy as well. <br>
- Make sure you understand that a plane is infinite. <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ Make sure if you change the vector that all vector directions work. <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ It is very important to make sure that the surface normal is correct; <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; otherwise later, the light might give you problems. <br>

`Cylinder` is a b**ch! <br>
- Cylinders consist out of two or three objects. <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ The body and the two caps. <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ The body ⇾ it will be in the beginning infinite, <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; so you need to cut/trim it at the correct height. <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ The caps are two planes, that are trimmed/cut as well. <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ Make sure the caps are perfectly on the body, <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; sometimes there is space in between cap and body, <br> 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; you will see the space once you added light. <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ Make sure the surface normal of the caps is correct. <br>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ Make sure all vector directions work correctly *(look correct)* <br>

Make sure you have all the objects, before adding light. <br>
Make sure you take the object closest to the camera. ***(Or do this in step 3)*** <br>

<img src="https://github.com/user-attachments/assets/ef45cd67-a7e1-4c7e-9438-417e4b6fbd85" alt="Correct_intersection_and_Space_between_cap_and_body" width="800">

<br>
<br>

</details>

---

<details>
  <summary><strong>Step 3;</strong></summary>

## 🖍️ Step 3

Look at the [light](#Light) and [shadow](#shadow) sections. <br>
Make sure you take the object closest to the camera. *(If you haven't in step 2)* <br>
Check all surface normals, sometimes they cause problems with the light. <br> <br>
**For example;** <br>
a Plane below a light source has the correct lighting, but a plane above a light source has no light at all. <br>
**If that happens:** flip the surface normal of the plane above *(make the surface normal positive)*, so it shows the light. <br>

```C
cyl->normal = mult_vecdub(cyl->vector, -1);	// Surface normal points downwards -> (mult_vecdub() = multiplying a vector and a double)
cyl->normal = cyl->vector; 			// Surface normal points upwards
```

</details>

---

<br>
<br>

## 🏁Checkerboard
#### It is not possible to create a sphere with a perfect checkerboard!
If the checked sphere looks good from the center, check the sides; there will be distortion. <br>
So rather calculate a checkerboard sphere that touches at the poles. <br>
Or make a texture that rotates towards the camera, so it always looks good. <br>


<img src="https://github.com/user-attachments/assets/041b6089-5dc9-487d-a844-c3b82bc07971" alt="perfect_and_real_checkerboard" width="800">

<br>
<br>


## 💡Light
<small><sup><i>(A lot of <a href="https://www.youtube.com/watch?v=xVWeRnStdSA">"hUh??"</a>moments)</i></sup></small><br>

## Calculating lighting on an object involves several steps:
- calculating the direction of light rays,
- determining the visibility of the light source from the surface point of the object. *[(Shadow part)](#Shadow)*
- and then applying illumination models such as [Phong](https://en.wikipedia.org/wiki/Phong_reflection_model) or [Blinn-Phong](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model) to compute <br>
the final colour of the object.
<br>

### 🔦 Calculate Light Direction: <br>
Determine the direction of light rays from the light source(s) to the surface point of the object. <br>
If the light source is directional *(like the sun)* , you only need the direction vector.  <br>
If the light source is a point light, you'll need to calculate the direction vector from <br>
the surface point to the light source position. <br>
<br>

### 🔦 Check Visibility: <br>
Determine if the surface point of the object is in shadow or not. <br>
<br>

### 🔦 Compute Illumination: <br>
Apply an illumination model *(such as [Phong](https://en.wikipedia.org/wiki/Phong_reflection_model) or [Blinn-Phong](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model))* to compute <br>
the final color of the object at the surface point. <br>
This involves calculating ambient, diffuse, and specular components based on the surface properties, <br>
light properties, and view direction. <br>
<br>

You go through each object and each object goes through each light.  <br>
### For example you have;
2 objects, 3 lights. <br> <br>
object**1** will be caclulated with light*1*, light*2*, light*3* <br>
then, object**2** will be calculated with light*1*, light*2*, light*3* <br> <br>

```C
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

![Phong reflection model](https://github.com/user-attachments/assets/717fa0b9-c06a-4c3f-a7dd-dd98fe0c8e7a)

⭕ &nbsp;&nbsp; Make sure for your Phong reflection model that your base colour is calculated <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; before you do diffuse and spectular light. <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Else your texture *(Checkerboard)* won't have light and shadow. <br>

<br>
<br>


## ⚫Shadow
### Check Visibility:
Determine if the surface point of the object is in shadow or not. <br>
You can achieve this by casting a shadow ray from the surface point towards the light source <br>
and checking if it intersects with any other object in the scene. <br>
If it intersects, the surface point is in shadow; otherwise, it's light. <br><br>

So, instead of calculating what makes logical sence, to calculate a ray from the light to the object, <br>
you need to calculate a ray from the object to the light.<small><sup><i>More <a href="https://www.youtube.com/watch?v=xVWeRnStdSA">"hUh??"</a>moments</i></sup></small><br>
If the ray *(on the way to the light)* hits another object, shadow will be drawn. <br>
If the ray makes it susscesfully to the light, light/Illumination will be calculated.<br>

![Shadow ray](https://github.com/user-attachments/assets/9834b1a9-93cf-4eef-932b-16f296b37889)


<br>
<br>

## 🧲Important Things to Know

<details>
  <summary><strong>Filed of view (FOV)</strong></summary>

### Filed of view (FOV)
- between 70° and 90° is the sweet spot. Less or more will distort the image.
- Distortion will always happen near the edges of the image.


</details>

---

<details>
  <summary><strong>Normalizing a vector</strong> ⇾ Decimal numbers (0.0)</summary>

### Normalizing a vector -> Decimal numbers (0.0) 
- Your number input *(excluding rgb)* need to take decimal numbers.
- Thats why we normalize our vectors.
- The normalization process ensures that the vectors have a consistent scale or magnitude, <br>
which can be important in certain operations such as distance calculations, clustering, or classification.
- So normalize every vector, either in the beginning *(while parsing)* <br>
or every vector you entcounter durring your calculations.


</details>

---

<details>
  <summary><strong>Selecting objects</strong></summary>

### Selecting objects
Selecting objects is not part of the project. <br>
We just thought it's a nice and easy way for the user/evaluater. <br>
to click on a object and do something with it. <br>

![selected_and_deselected_object](https://github.com/user-attachments/assets/c5912668-b1e0-483a-b719-e6ad4e7d358a)


#### WE only have the option: 
- You can select all objects, but you can only do something with the sphere.
- If a sphere is selected you can press arrow key up &nbsp;&nbsp; <img src="https://github.com/user-attachments/assets/184cb383-b186-4048-a030-cfb054eb9758" alt="Arrow_key_up" width="40"> <br>
- It will then add the Checkerboard on the sphere.

#### but YOU also could:
- Add more textures to the sphere or give other objects textures aswell.
- Move and rotate objects.
- Make objects bigger or smaller.

<br>

### How does it work
you need **mlx** functions:
```C
- mlx_key_hook();	-> is for key movement (ESC, Arrow up).
- mlx_mouse_hook();	-> is for mouse movement (selcet objects).
```

<br>

🐭 **Mouse movement *(selcet objects)*:** <br>
Quick explanation how the mouse map works.
 - There is a 2D mouse_map[x][y].
 - While we loop through every pixel, we fill in this map.
 - If no object is at that position fill in **-1**.
 - If there is an object, give it a number *(intersection point found)*.
 ```C
Example:
	Sphere1 = 0; (red)
	Sphere2 = 1; (blue)
	Plane   = 2; (green)
mouse_map:
	-1 -1 -1 -1 -1        ⬛⬛⬛⬛⬛
	-1 -1  0 -1 -1        ⬛⬛🟥⬛⬛
	-1  0  0  0 -1        ⬛🟥🟥🟥⬛
	 0  0  0  0  0   ->   🟥🟥🟥🟥🟥
	-1  0  0  0 -1        ⬛🟥🟥🟥⬛
	-1 -1  0 -1  2        ⬛⬛🟥⬛🟩
	-1 -1 -1  2  2        ⬛⬛⬛🟩🟩
```
 - Find the position of the mouse, with **mlx_get_mouse_pos();**.
 - If the mouse map is **-1** at that position, so no object has been selected.
 - Else if the mouse map is **NOT -1** at that position. Highlight the object. <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ Just set/draw a white pixel with a bit of offset inwards next to the position.
 - For removeing the highlight, remove the colour of the pixel *(set it to 0)*.
 - <strong>How is that possible ☝️ ? </strong>
 - Use **mlx_image_to_window()** to put a layer on top of the 'original' <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ○ It loads faster because it doesn't go through each pixel and recalculates everything.
- That's why to remove the highlight, you can set that colour to 0, so it will just unset those pixels.

<br>

🗝️ **Key movement *(ESC, Arrow up)*:** <br>

🔴 &nbsp;&nbsp; - &nbsp;&nbsp; If the pressed key is 'ESC key', close and free window. <br>
🟡 &nbsp;&nbsp; - &nbsp;&nbsp; If an object is selected and the key 'Arrow up' is pressed, <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; we change the pattern of that object. <br>
🟢 &nbsp;&nbsp; - &nbsp;&nbsp; You need to count how many arrow-ups you have. <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Because arrowUp-1 should change pattern, arrowUp-2 should change <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; to a different pattern or original form. <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; After that, you need to reset your arrow-up count <br>
🔵 &nbsp;&nbsp; - &nbsp;&nbsp; Change the pattern of that object. 

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

-----------------------------------------------------------------------------------------------

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
🚩 &nbsp;&nbsp; : &nbsp;&nbsp; BECAUSE: &nbsp;&nbsp; you recalculate all pixels, it will take a while. <br>
			  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;It would be wiser to use mlx_image_to_window() <br>
			  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;to put a layer on top of the 'original'. <br>
			  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;In the very beginning, initialize all pixels and store <br>
			  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;that information for each pixel in a pixel struct *(object, distance, colour, light, etc.)* <br>
			  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Reuse that pixel struct, so you don't need to <br>
			  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;recalculate everything. <br>
			  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;It's also easier for if you want object rotation, <br>
			  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;so the original information is saved, and you can access it fast.   <br>

![video](https://github.com/user-attachments/assets/b72cda00-34ce-437e-be8d-7b04f5cd7c45)



</details>

---

<details>
  <summary><strong>About Colour</strong></summary>

### About Colour
Use this webside you find you rgb colours 👉 [RGB Color Picker](https://rgbacolorpicker.com/) 👈 <br>
You can pick your colour and it will give you the rgb number.
<br>

Check that your colour overlap is correct. 
<br>
<br>

<img src="https://github.com/user-attachments/assets/dd1bb85a-d790-4741-a32d-09768fa7844e" alt="Colour_example" width="800">


</details>

---

<details>
  <summary><strong>Just an example of `.rt` file</strong></summary>

Minirt.rt file
```script

#Ambient lighting (A): 
#Identifier         #Ratio           #R,G,B
A                   0.2              255,255,255

# --------------------------------------------------------------------------------------------
#Camera (C): 
#Identifier         #Coordinates     #3D vector     #FOV
C                   0,0,-1           0,0,1          70

# --------------------------------------------------------------------------------------------
#Light (L):
#Identifier         #Coordinates     #Ratio        #R,G,B
L                   2,2,0            0.6           255,255,255

# --------------------------------------------------------------------------------------------
#Sphere (sp):
#Identifier         #Coordinates     #Diameter      #R,G,B
sp                  0,0,-10          12.6           10,0,255

# --------------------------------------------------------------------------------------------
#Plane (pl): 
#Identifier         #Coordinates     #3D vector     #R,G,B
pl                  10,3,-10         0,1,0          0,0,225

# --------------------------------------------------------------------------------------------
#Cylinder (cy):
#Identifier         #Coordinates     #3D vector     #Diameter        #Height      #R,G,B
cy                  -5,0,-5          0,0,1          14.2             21.42        10,0,255

# --------------------------------------------------------------------------------------------
#Triangle (tr) -> optional:
#Identifier         #Coordinates1    #Coordinates2   #Coordinates3   #R,G,B
tr                  -7,6,-11         -7,-6,-11       10,0,-11        255,102,102

```

</details>
<br>
<br>


## 🔮Installation

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

## 📋Resources

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
