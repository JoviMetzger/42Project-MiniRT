Hello MiniRT :)


<!--
MiniRT

Welcome to MiniRT, this project is made in collabaration with [Sarah Mclacke](https://github.com/smclacke).
MiniRT is about Ray tracing, which will render a 3-dimensional computer-generated images.

![images]()

## Table of Contents

- [Build a Ray](#Functions)
- [Checkerboard](#Buildin)
- [Spectular light](#Signals)
- [Shadow](#Prompt)
- [Important things to know](#Test-for-Leaks)
- [Information about our MiniRT](#Installing-readline)
- [Installation](#Installation)
- [Resources](#Resources)




## Building a Ray


## Checkerboard


## Spectular light


## Shadow


## Important things to know


## Information about our MiniRT


## Installation


## Resources
- https://nl.wikipedia.org/wiki/Raytracing
- https://developer.nvidia.com/discover/ray-tracing
- https://raytracing.github.io/books/RayTracingInOneWeekend.html
- https://www.geeksforgeeks.org/c-library-math-h-functions/
- https://www.tutorialspoint.com/c_standard_library/math_h.htm
- https://rgbacolorpicker.com/
- https://www.cs.cmu.edu/afs/cs/academic/class/15462-s09/www/lec/04/lec04.pdf
- https://gamedev.stackexchange.com/questions/156842/how-can-i-correct-an-unwanted-fisheye-effect-when-drawing-a-scene-with-raycastin/156853#156853
- https://gamedev.stackexchange.com/questions/97574/how-can-i-fix-the-fisheye-distortion-in-my-raycast-renderer
- https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/minimal-ray-tracer-rendering-spheres.html
- http://graphics.cs.cmu.edu/nsp/course/15-462/Spring04/slides/13-ray.pdf
- https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/ligth-and-shadows.html
- https://www.google.com/imgres?q=3%20colored%20lights%20on%20an%20object&imgurl=https%3A%2F%2Fwww.exploratorium.edu%2Fsites%2Fdefault%2Ffiles%2FRGB_screen.gif&imgrefurl=https%3A%2F%2Fwww.exploratorium.edu%2Fsnacks%2Fcolored-shadows&docid=Nzp0duVI3UF6RM&tbnid=gZrFqPSCteUEVM&vet=12ahUKEwig4YGW_oCIAxU7wAIHHQvQKqUQM3oECDIQAA..i&w=1080&h=612&hcb=2&ved=2ahUKEwig4YGW_oCIAxU7wAIHHQvQKqUQM3oECDIQAA
- 
- 
- 





Sure, a 4x4 matrix is a mathematical construct used extensively in computer graphics, computer vision, and various other fields involving transformations in three-dimensional space. It's a rectangular array of numbers organized into four rows and four columns. Each element in the matrix can hold a scalar value, typically a floating-point number.

Here's how a 4x4 matrix looks:

Copy code
| m11  m12  m13  m14 |
| m21  m22  m23  m24 |
| m31  m32  m33  m34 |
| m41  m42  m43  m44 |
In the context of computer graphics and transformations, each row of the matrix often represents a transformation operation (translation, rotation, scaling, etc.), while each column represents a coordinate axis (x, y, z, w). Here's a breakdown of the components:

m11, m12, m13, m14: These elements typically represent the transformation and scaling applied to the x-axis.
m21, m22, m23, m24: These elements represent the transformation and scaling applied to the y-axis.
m31, m32, m33, m34: These elements represent the transformation and scaling applied to the z-axis.
m41, m42, m43, m44: These elements represent the translation components.
The elements along the diagonal from the top-left to the bottom-right (m11, m22, m33, m44) are often referred to as the "main diagonal" or simply the "diagonal" of the matrix. In a transformation matrix, these elements are typically related to scaling and rotation operations.

In 3D graphics, the fourth column (m14, m24, m34) and fourth row (m41, m42, m43) are often used for translation components. The fourth row is usually [0 0 0 1], where the last element, m44, is set to 1. This is known as a homogeneous coordinate system, which allows affine transformations (including translations) to be represented as matrix multiplications.

By combining various transformation matrices (for translation, rotation, scaling, etc.) through multiplication, you can perform complex transformations on geometric objects in three-dimensional space efficiently. This is the basis of many operations in computer graphics, such as transforming 3D models, positioning cameras, and rendering scenes.


// ------------ eVerYTinG BeloW tHiS liNe iS jUSt ME gOiNg "hhhUUUUUhhhhhh?????????????" -----------
			// aka. cat meme (https://www.youtube.com/watch?v=xVWeRnStdSA)
			
			
			
			Calculating lighting on an object involves several steps, including calculating the direction of light rays, determining the visibility of the light source from the surface point of the object, and then applying illumination models such as Phong or Blinn-Phong to compute the final color of the object. Here's a simplified overview of how you can calculate lighting on an object in C:

Calculate Light Direction:
Determine the direction of light rays from the light source(s) to the surface point of the object. If the light source is directional (like the sun), you only need the direction vector. If the light source is a point light, you'll need to calculate the direction vector from the surface point to the light source position.

Check Visibility:
Determine if the surface point of the object is in shadow or not. You can achieve this by casting a shadow ray from the surface point towards the light source and checking if it intersects with any other object in the scene. If it intersects, the surface point is in shadow; otherwise, it's illuminated.

Compute Illumination:
Apply an illumination model (such as Phong or Blinn-Phong) to compute the final color of the object at the surface point. This involves calculating ambient, diffuse, and specular components based on the surface properties, light properties, and view direction.








// t_colour get_sphere_colour(t_data *data, t_ray lightray, t_obj_data *obj_data, t_colour ambient)
// AMBIENT_INTENSITY: Ratio of ambient light intensity (ambient reflection).
// DIFFUSE_INTENSITY: Ratio of diffuse light intensity (diffuse reflection).
// SPECULAR_INTENSITY: Ratio of specular light intensity (specular reflection).
// SPECULAR_POWER: Specular power or shininess, controlling the size and sharpness of specular highlights.
t_colour get_sphere_colour(t_data *data, t_obj_data *obj_data, t_ray ray)
{
    t_colour result;
    double AMBIENT_INTENSITY = data->ambient.ratio; // (0.2)
    double DIFFUSE_INTENSITY = data->light.ratio;   // (0.6)
    double SPECULAR_INTENSITY = 0.2;
    double SPECULAR_POWER = 32;
    
    // Using the 'Phong reflection model'
	if (obj_data->d >= 0.0)
	{
		t_vec3 intersection_point = plus(ray.place, mult_vecdub(ray.vector, obj_data->t));
		t_vec3	normal = normalize_vector(minus(intersection_point, data->objs->center));

		// Ambient light contribution
		double ambient_red = AMBIENT_INTENSITY * data->ambient.colour.r;
		double ambient_green = AMBIENT_INTENSITY * data->ambient.colour.g;
		double ambient_blue = AMBIENT_INTENSITY * data->ambient.colour.b;

		// Diffuse light contribution
		t_vec3 light_direction = normalize_vector(minus(data->light.place, intersection_point));
		double diffuse_factor = dot_product(normal, light_direction);
		if (diffuse_factor < 0.0)
			diffuse_factor = 0.0;
		double diffuse_red = DIFFUSE_INTENSITY * diffuse_factor * data->light.colour.r;
		double diffuse_green = DIFFUSE_INTENSITY * diffuse_factor * data->light.colour.g;
		double diffuse_blue = DIFFUSE_INTENSITY * diffuse_factor * data->light.colour.b;
		
		// Specular light contribution
		t_vec3 view_direction = normalize_vector(minus(ray.place, intersection_point));
		t_vec3 reflection_direction = normalize_vector(ft_reflect(light_direction, normal));
		double specular_factor = pow(dot_product(reflection_direction, view_direction), SPECULAR_POWER);
		if (specular_factor < 0.0)
			specular_factor = 0.0;
		double specular_red = SPECULAR_INTENSITY * specular_factor * data->ambient.colour.r;
		double specular_green= SPECULAR_INTENSITY * specular_factor * data->ambient.colour.g;
		double specular_blue = SPECULAR_INTENSITY * specular_factor * data->ambient.colour.b;

		// Combine ambient, diffuse, and specular contributions
		double final_red = ambient_red + diffuse_red + specular_red;
		double final_green = ambient_green + diffuse_green + specular_green;
		double final_blue = ambient_blue + diffuse_blue + specular_blue;
		
		// Clamp final values to [0, 255]
		final_red = fmin(fmax(final_red, data->objs->colour.r), 255);
		final_green = fmin(fmax(final_green, data->objs->colour.g), 255);
		final_blue = fmin(fmax(final_blue, data->objs->colour.b), 255);

        result.r = final_red;
        result.g = final_green;
        result.b = final_blue;
		
		return result;	
	}
	else
    {
        result.r = 0;
        result.g = 0;
        result.b = 0;
		return result;
    }
	
}

C              0,0,0      0,0,-1     150

A               0.2      255,255,255

L               -10,0,0     0.5     255,255,0

sp              -5,5,-5       4     0,255,0

sp              0,0,-5       4     255,0,0

pl              0.0,0.0,-10.0     0.0,1.0,0.0     0,0,225

cy              50.0,0.0,20.6       0.0,0.0,1.0     14.2     21.42   10,0,255




WEBSERV
- https://www.npmjs.com/package/http-server
- https://nodejs.org/api/http.html
- https://www.techtarget.com/whatis/definition/Request-for-Comments-RFC
- https://blog.nginx.org/blog/http2-theory-and-practice-in-nginx-stable-13
- https://www.linode.com/docs/guides/http-get-request/
- https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
- https://m4nnb3ll.medium.com/webserv-building-a-non-blocking-web-server-in-c-98-a-42-project-04c7365e4ec7
- https://www.ibm.com/docs/en/was/9.0.5?topic=console-web-server-configuration
- https://ncona.com/2019/04/building-a-simple-server-with-cpp/
- https://kbeezie.com/nginx-configuration-examples/

-- https://github.com/Kaydooo/Webserv_42?tab=readme-ov-file
-- https://github.com/LucieLeBriquer/webserv

--------------------------------------------------
web pages info:

https://www.npmjs.com/package/http-server
https://nodejs.org/api/http.html
https://www.ietf.org/process/rfcs/
https://www.techtarget.com/whatis/definition/Request-for-Comments-RFC
https://nginx.org/en/
https://www.nginx.com/blog/http2-theory-and-practice-in-nginx-stable-13/

--------------------------------------------------

Hypertext Transfer Protocol (HTTP)  ->  protocol for distributed, collaborative, hypermedia information systems.
The communication between client and server takes place using the Hypertext Transfer Protocol (HTTP).
Pages delivered are most frequently HTML documents, which may include images, style sheets, and scripts in addition to the text content.

RFC -> 'Requests for Comments':
They define the Internet's technical foundations, such as addressing, routing and transport technologies. They recommend operational best practice and specify application protocols that are used to deliver services used by billions of people every day.
Has two sub-series, STDs and BCPs, with each numbered STD and BCP comprising one or more RFCs. 
STDs -> 'Internet Standard'
BCPs -> describe Best Current Practices in the Internet, some of which are administrative processes for the IETF.
IETF -> Internet Engineering Task Force

nginx [engine x]:
NGINX is open source software for web serving, reverse proxying, caching, load balancing, media streaming, and more. It started out as a web server designed for maximum performance and stability. In addition to its HTTP server capabilities, NGINX can also function as a proxy server for email (IMAP, POP3, and SMTP) and a reverse proxy and load balancer for HTTP, TCP, and UDP servers.

The goal of the project is to build a C++98 compatible HTTP web server from scratch. The web server can handle HTTP GET, HEAD, POST, PUT, and DELETE Requests, and can serve static files from a specified root directory or dynamic content using CGI. It is also able to handle multiple client connections concurrently with the help of select().

HTTP (Hypertext Transfer Protocol) is a protocol for sending and receiving information over the internet. 
It is the foundation of the World Wide Web and is used by web browsers and web servers to communicate with each other.

An HTTP web server is a software application that listens for and responds to HTTP requests from clients (such as web browsers). 
The main purpose of a web server is to host web content and make it available to users over the internet.

HTTP consists of requests and responses. When a client (such as a web browser) wants to retrieve a webpage from a server, 
it sends an HTTP request to the server. The server then processes the request and sends back an HTTP response


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
										HTTP request:
	
	request line:						Headers:								optional message body:		
	consists of							contain additional 						- GET method usually doesn't
	- the method, 						information about the request			  include any body, most servers
	- the path, 						- the hostname of the server, 			  respond with information
	- the HTTP version.					- the type of browser being used.		  from the URI/URL requested.
   ---------------------	
The method specifies the action
that the client wants to perform,
such as GET (to retrieve a resource) 
or POST (to submit data to the server)
   ---------------------
The path or URI specifies the location 
of the resource on the server.
   --------------------- 
The HTTP version indicates the version
of the HTTP protocol being used.

------------------------------------------------------------------------------------------
									HTTP response:

	status line:						 Headers:								  optional message body:
	consists of							 contain additional 					  - The message body contains the actual	
	- the HTTP version, 				 information about the response			    content of the response,
	- the status code, 					 - the type and size					    such as the HTML code for a webpage.	
   ---------------------				   of the content being returned.	
The status code indicates 
the result of the request,
such as 200 OK (successful) 
or 404 Not Found (resource not found). 
The reason phrase is 
a short description of the status code.
   ---------------------
Responses are grouped in five classes:
(https://developer.mozilla.org/en-US/docs/Web/HTTP/Status)
Informational responses (100 – 199)
Successful responses (200 – 299)
Redirection messages (300 – 399)
Client error responses (400 – 499)
Server error responses (500 – 599)


------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------
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



------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------
							Different parts of the project: 
						
Server Core:
The networking part of a web server that handles TCP connections and performs tasks such as listening for incoming requests and sending back responses. Responsible for the low-level networking, such as creating and managing sockets, handling input and output streams, and managing the flow of data between the server and clients.
TCP socket programming:
Socket : mechanism to give programs access to the network
- create a socket with socket()
- identify the socket with bind()
- wait for a connection with listen() and accept()
- send and receive messages with read() and write() (or send() and recv())
- close the socket with close()

   ---------------------

Request Parser:
The process that is responsible for interpreting and extracting information from HTTP requests. Receives an incoming request, parses it, and extracts the relevant information such as the method, path, headers, and message body(if present). If any syntax error was found in the request during parsing, error flags are set and parsing stops.

   ---------------------

Response Builder:
The response builder is responsible for constructing and formatting the HTTP responses that are sent back to clients in response to their requests. Building and storing the HTTP response, including the status line, headers, and message body. The response builder may also perform tasks such as setting the appropriate status code and reason phrase based on the result of the request, adding headers to the response to provide additional information about the content or the server, and formatting the message body according to the content type and encoding of the response. For example, if the server receives a request for a webpage from a client, the server will parse the request and pass it to a 'Response object'(a class) which will fetch the contents of the webpage and construct the HTTP response with the HTML content in the message body and the appropriate headers, such as the Content-Type and Content-Length headers.

   ---------------------

Configuration File:
Configuration file is a text file that contains various settings and directives that dictate how the web server should operate. These settings can include things like the port number that the web server should listen on, the location of the web server's root directory, and many other settings.

   ---------------------

CGI:
CGI is a standard for running external programs from a web server. When a user requests a web page that should be handled by a CGI program, the web server executes the program and returns the output to the user's web browser.
CGI programs are simply scripts that can be written in any programming language, such as Perl, Python, or bash, and are typically used to process data submitted by a user through a web browser, or to generate dynamic content on a web page.

   ---------------------
   
   
   
   
   
   Ports, in the context of computer networking, are identified by port numbers, which range from 0 to 65535. This range means that port numbers can be up to five digits long. Here is a breakdown of the port number ranges:

Well-Known Ports (0 to 1023): These ports are reserved for system or well-known services and protocols (e.g., HTTP uses port 80, FTP uses port 21).

Registered Ports (1024 to 49151): These ports are assigned by the Internet Assigned Numbers Authority (IANA) for user processes or applications.

Dynamic or Private Ports (49152 to 65535): These ports are used for private or temporary purposes, often assigned dynamically to client applications when they connect to a network service.

So, ports can be 1 to 5 digits long, but they must fall within the 0 to 65535 range.




# --- default server block ---
# # (All variables)
# server {
# 	server_name		=	VroomVroom					# Name of server
# 	port 			=	8080						# Listen on port for incoming connections
# 	host			=	127.0.0.1					# Server block will respond to requests for localhost (or (127.0.0.1))
# 	root			=	/www/html					# Sets the root directory for this server block
# 	max_client_size =	5000000						# File upload limit is 5MB -> 5000000
# 	index			=	/index.html		 			# File to serve when a server running (Main web page)
# 	error_page 400 	=	/config/error_page/400.html	# Files to serve when a error occurs
# 	error_page 403 	=	/config/error_page/403.html 
# 	error_page 404 	=	/config/error_page/404.html
# 	error_page 405 	=	/config/error_page/405.html
# 	error_page 406 	=	/config/error_page/406.html
# 	error_page 409 	=	/config/error_page/409.html
# 	error_page 410 	=	/config/error_page/410.html
# 	error_page 500 	=	/config/error_page/500.html
# 	error_page 505 	=	/config/error_page/505.html

# 	# Handles requests to the root URL '/cgi-bin' -> first location block context 
# 	location /cgi-bin {
# 		allowed_methods = POST GET DELETE			# Allowed_methods for that location Block
# 		root			= /www
# 	}
	
# 	# Handles requests to the root URL '/' -> second location block context
# 	location / {
# 		index 	= /index.html						# specifies the default file to serve in this location
# 		root	= /www/html	
# 	}


# 	# Handles requests to the root URL '/' -> third location block context
# 	location /img {
# 		root		= /www/html						# Local pathing to what directory should be served in this location Block
# 		autoindex	= on 							# Turns off/on directory listing. -> showes/listing of directories
# 	}
# }

-->
