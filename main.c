#include "vector2.h"
#include <stdio.h>

int main() {
	Vector2 vector_a = vector2_create(3.0, 4.0);
	Vector2 vector_b = vector2_create(12.0, 5.0);

	Vector2 result; // Storing the result vector into a VARIABLE
	Vector2 result_sub;
	Vector2 result_mul;

	vector2_add(&vector_a, &vector_b, &result);
	vector2_sub(&vector_a, &vector_b, &result_sub);
	vector2_mul(&vector_a, &vector_b, &result_mul);

	printf("Vector A: (%.2f, %.2f)\n", vector_a.x, vector_a.y);
	printf("Vector B: (%.2f, %.2f)\n", vector_b.x, vector_b.y);
	printf("A + B = (%.2f, %.2f)\n", result.x, result.y);
	printf("A - B = (%.2f, %.2f)\n", result_sub.x, result_sub.y);
	printf("A * B = (%.2f, %.2f)\n", result_mul.x, result_mul.y);

	float length_a = vector2_length(&vector_a);

	printf("Length of the vector A: %.2f\n", length_a);

	return 0;
}
