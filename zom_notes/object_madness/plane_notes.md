


/**
 * 	right???
 * 		if camera pos = 0,0,50
 * 		
 * 		first plane (blue) is behind camera, second plane (green) is infront of camera
 * 		but since the blue is explanding everywhere, the plane looks blue
 * 
 * 		pl              0.0,70.0,0.0       0.0,1.0,0.0     0,0,255 		BLUE
 *		pl              0.0,-60.0,0.0       0.0,1.0,0.0     0,255,0 	GREEN
 *
 * 
 *		pl              0.0,60.0,0.0       0.0,1.0,0.0     0,0,255
 *		pl              0.0,20.0,0.0       0.0,1.0,0.0     0,255,0 
 * 		if blue plane - 0,-70,0 and green - 0,-60,0
 * 		plane is green since it's closes to camera and so shows first, blue plane is underneath...
 */


/**
 * 
		C              0,0,30      0,0,-1     70

A               0.2      255,255,255

L               5,5,0     0.7     255,255,255


pl              0.0,50.0,0.0       0.0,1.0,0.0     0,0,255

sp              0,0,-10       2     255,0,0

sp              -2,0,-10       2     200,100,255



cy              50.0,0.0,20.6       0.0,0.0,1.0     14.2            21.42       10,0,255

				

				
--------------------------------------------------------------------------------

C              -50.0,0,20      0,0,1     70

A               0.2      255,255,255

L              -40.0,50.0,0.0      0.6         10,0,255


pl              0.0,0.0,-10.0       0.0,1.0,0.0     0,0,255


sp              0.0,0.0,20.6        12.6            10,0,255


cy              0.0,0.0,-50.6       0.0,0.0,1.0     14.2            21.42       10,0,255

 * 
 */