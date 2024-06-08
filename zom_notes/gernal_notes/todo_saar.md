


--- not implementing ---

 - dont do window resizing

 - dont do textures, remove extra code

 - no inside objects (but actually have to for cylinder...?)



--- to do now ---

 - cyl normals!

 - find any calculation that can happen in parsing and not per pixel

 - fix the cylinder:
 		 - cap normal ok?
		 - when cylinder is turned etc, z vec isnt quite ok
	++ if 0,1,0 0r 1,0,0 and a little to one side, it's lopsided without straight edges...
		cutting ends is not quite right for a laying cylinder

 - what is cyl vec 1,1,1 supposed to do?

 - sphere stretching

 - light array in parser 

