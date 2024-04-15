
// from jovi <3

/* quadratic equation:
 *  a = d * d (dot product of ray direction with itself)
 *  b = 2 * oc * d (dot product of vector from ray origin to sphere center with ray direction, doubled)
 *  c = oc * oc -r^2 (dot product of vector from ray origin to sphere center with itself, minus radius squared)
 *  d = b^2 - 4ac (discriminant)
 * 
 *  If the discriminant b^2 - 4ac is negative, 
 *  there are no real solutions to the quadratic equation,
 *  meaning the ray does not intersect the sphere.
 * 
 *  If the discriminant is non-negative, there are potentially two real solutions, 
 *  representing the points where the ray intersects the sphere. 
 *  These solutions are given by the roots of the quadratic equation. 
 *  The smaller root is chosen as the parameter 't' for the intersection point 
 *  closer to the ray's origin.
 */