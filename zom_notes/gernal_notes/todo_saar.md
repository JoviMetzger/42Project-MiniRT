**key**

!! - done, triple check but no longer a to do
** - in progress with notes/reminders elsewhere
0_0 - omg noooo


**CURRENT SHIZZLE**

- sphere surface normal looks good, need to check rest

- check cylinder when looking straight on with z vec
	- if we look straight on, we get circle which is nice, also if move 
		around the x axix
		if move up y (or down) cylinder body gets disconnected from the caps...
	- $$$ i think it might be due to missing the other half of the cylinder... if 
		from looking straight, there is a floating cylinder above, you'll see 
		the bottom of the body, and a cap (closest to you) but also the top bit of the cap (otherwise you'd need to be right underneath the cylinder)
		so we are actually seeing the stuff correctly but seeing that part of the cylinder is missing....
	- $$$ if we only just radius, it fits better when looking from up close, straight on...

**general situation / to do's / concerns:**


0_0 - SEGFAULT

CHECK - everything time in parser i pass a string to a checking or converting func, 
	CHECK IT'S NOT NULL FS

		ORRRR DONT CHECK FOR TABS AND SHIT AND CALLL IT A SPACE MAYYYBBEEE 
			- make sure this is legit, no other breakage and no SEGFAUUUUUULTING omgver


- sphere stretches when close up

- image stretching... we aren't supposed to stretch when resizing the window (remove stretching?)

- i keep crashing/it takes too long, im not sure exactly where that's coming from/oplossing

- new jovi stuff

- worry about changing things to calculate less per pixel? (optimize but also no crash)

- got triangle stuff down, ofc not working yet tho

- are we leaving the main get_colour stuff as it is?

- how are we adding the checkerboard etc?

- we are sharing quite a lot - structs !!

!!- triple check quadratic, might work for sphere but just incase it's fucking other stuff up

**- check closest_t stuff, cause updating that but not actually resetting t or using closest

- i believe plane is good but questioning literally everything at this point...

- there's new stuff you want in the parser

- haven't gone back to textures yet

- we leak 

- inside of objects!! (at least cylinder...) - NOPE

