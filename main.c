#include "vector2.h"
#include <stdio.h>

int main() {
	Vector2 vector_a = vector2_create(3.0, 4.0);
	Vector2 vector_b = vector2_create(12.0, 5.0);

	Vector2 result; // Storing the result vector into a VARIABLE
	
	vector2_add(&vector_a, &vector_b, &result);

	printf("Vector A: (%.2f, %.2f)\n", vector_a.x, vector_a.y);
	printf("Vector B: (%.2f, %.2f)\n", vector_b.x, vector_b.y);
	printf("A + B = (%.2f, %.2f)\n", result.x, result.y);

	float length_a = vector2_length(&vector_a);

	printf("Length of the vector A: %.2f\n", length_a);

	return 0;
}
