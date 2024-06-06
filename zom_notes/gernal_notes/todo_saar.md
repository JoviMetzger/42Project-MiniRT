


--- no implementing ---

 - dont do window resizing

 - dont do textures, remove extra code

 - no inside objects (but actually have to for cylinder...)



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

 - new stuff for parser?

#include <stdio.h>
#include <math.h>

// Structure to represent a 3D point or vector
typedef struct {
    double x;
    double y;
    double z;
} Vector3;

// Function to calculate the length (magnitude) of a vector
double vector_length(Vector3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Function to normalize a vector
Vector3 normalize_vector(Vector3 v) {
    double length = vector_length(v);
    Vector3 normalized = {v.x / length, v.y / length, v.z / length};
    return normalized;
}

// Function to calculate the normal vector at the intersection point on the cylinder
Vector3 calculate_normal(Vector3 intersection_point) {
    // Create the normal vector from the cylinder's axis to the intersection point
    Vector3 normal_vector = {intersection_point.x, intersection_point.y, 0};

    // Normalize the normal vector
    Vector3 normal_vector_normalized = normalize_vector(normal_vector);

    return normal_vector_normalized;
}

int main() {
    // Example intersection point on the cylinder
    Vector3 intersection_point = {3.0, 4.0, 5.0};  // x=3, y=4, z=5

    // Calculate the normal vector
    Vector3 normal_vector = calculate_normal(intersection_point);

    // Print the normal vector
    printf("Normal Vector: (%f, %f, %f)\n", normal_vector.x, normal_vector.y, normal_vector.z);

    return 0;
}
