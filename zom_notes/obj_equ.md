*/
/**
 * 
 * float Cylinder::intersect(Vector pos, Vector dir)
{   
    float a = (dir.x * dir.x) + (dir.z * dir.z);
    float b = 2*(dir.x*(pos.x-center.x) + dir.z*(pos.z-center.z));
    float c = (pos.x - center.x) * (pos.x - center.x) + (pos.z - center.z) * (pos.z - center.z) - (radius*radius);
    
    float delta = b*b - 4*(a*c);
	if(fabs(delta) < 0.001) return -1.0; 
    if(delta < 0.0) return -1.0;
    
    float t1 = (-b - sqrt(delta))/(2*a);
    float t2 = (-b + sqrt(delta))/(2*a);
    float t;
    
    if (t1>t2) t = t2;
    else t = t1;
    
    float r = pos.y + t*dir.y;
    
    if ((r >= center.y) and (r <= center.y + height))return t;
    else return -1;
}

* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the sphere.
Vector Cylinder::normal(Vector p)
    Vector n = Vector (p.x-center.x,0,p.z-center.z);
    n.normalise();
    return (n);
*/

pl              2,0,-3       0.0,1.0,0.0     0,255,225
pl              0,0,-5       0.0,1.0,0.0     0,255,0
pl              -2,0,-3       0.0,1.0,0.0     0,0,22


weird orange cycle stuff
pl              2,0,-3       0,0.2,-1    255,255,255
pl              0,5,5       0,1,-1    255,0,0
pl              1,2,1       0,0,0    255,0,255



big blobby orange curve
pl              0,5,5       0,1,-1    255,0,0

nothing?
pl              1,2,1       0,0,0    255,0,255


white cycle
pl              2,0,-3       0,0.2,-1    255,255,255