#include "include/vector2.h"
#include "include/vector3.h"
#include <stdio.h>

int main() {
	// 2D vectors
	Vector2 vector_a = vector2_create(3.0, 4.0);
	Vector2 vector_b = vector2_create(12.0, 5.0);

	Vector2 result; // Storing the result vector into a VARIABLE
	Vector2 result_sub;
	Vector2 result_mul;

	vector2_add(&vector_a, &vector_b, &result);
	vector2_sub(&vector_a, &vector_b, &result_sub);
	vector2_mul(&vector_a, &vector_b, &result_mul);

	// 3D vectors
	Vector3 vector_x = vector3_create(6.0, 7.0, 8.0);
	Vector3 vector_y = vector3_create(9.0, 10.0, 11.0);
	Vector3 result3;

	vector3_add(&vector_x, &vector_y, &result3);
	

	printf("Vector A: (%.2f, %.2f)\n", vector_a.x, vector_a.y);
	printf("Vector B: (%.2f, %.2f)\n", vector_b.x, vector_b.y);
	printf("A + B = (%.2f, %.2f)\n", result.x, result.y);
	printf("A - B = (%.2f, %.2f)\n", result_sub.x, result_sub.y);
	printf("A * B = (%.2f, %.2f)\n", result_mul.x, result_mul.y);

	float length_a = vector2_length2(&vector_a);

	printf("Length of the vector A: %.2f\n", length_a);

	printf("Vector X: (%.2f, %.2f, %.2f)\n", vector_x.x, vector_x.y, vector_x.z);
	printf("Vector Y: (%.2f, %.2f, %.2f)\n", vector_y.x, vector_y.y, vector_y.z);
	printf("X + Y: (%.2f, %.2f, %.2f)\n", result3.x, result3.y, result3.z);

	return 0;
}
