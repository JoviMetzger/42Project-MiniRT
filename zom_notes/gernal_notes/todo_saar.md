


--------------------------------------------------------------------------
--- to do now ---

!!!
 - surface normals

 - cylinder shape - still wronnnngggggggg
 - inside cylinder + sphere
 - window resizing "when..." subject pdf


 - prep eval files, some basic/simple, some more complicated
 - norm everything
 - check all TODO comments

+
 - cylinder vector 1,1,1 ... check
 - anything else we can do to improve speed?
 - do we want loading messages/rending while window open (without pop up)


!!!!! ft_handle_mouse_click heap butter overflowed when i threw the window and droped it quickly

--------------------------------------------------------------------------


PARSER:

L              -2,0,-1    0.7    0,/255,0 - IS NOT AN ERROR.... SHOULD BE

normals:

TRIANGLE
obj norm = 0.000000 0.000000 1.000000

SPHERE
obj norm = -0.099434 0.988974 0.109744

CYLINDER - 0,1,1
obj norm = 0.000000 0.707107 0.707107

literally no idea if good or no, triangle should be since it's flat on 0,0,1


//// shadow function notes:


// WITH THIS CODE: 
// mult + plus
// two lights, 10 + -10 no shadow = good
// one light -10, shadow on red but not blue = bad
// one light 10, shadow on green (looks like the blue sphere shadowed on top) = bad

// WITH:
// div seems to give no shadows at all..
// div + plus
// one light 10, no shadow = good
// one light -10, no shadow = bad
// two lights, 10 + -10 no shadow = good

// WITHOUT OBJ WHILE + MULT + PLUS
// one -10, good shadows
// one 10 totally fucked
// two lights, loads of light and fucked shadow on blue = bad

// WITHOUT OBJ WHILE + DIV + PLUS
// two lights, no shadow = good
// one -10 no shaodw = bad
// one 10 

// CONCLUSION: div no shadow, obj while no real difference, fix it with mult and plus

// div seems to give no shadows at all..
// inter_p = division_vec_dub(data->pix[i]->og_ray.vector, data->pix[i]->hit_t);
// sometimes mult/div, sometimes minus/plus (i think no more minus tho)


// L             -10,0,-4    0.6   0,200,255
// L             10,0,-4    0.6   0,200,255

// sp                 -3,0,-25        4          0,0,255
// sp                 -1,0,-30        4          255,0,0
// sp                  -5,0,-20        4           0,255,0


