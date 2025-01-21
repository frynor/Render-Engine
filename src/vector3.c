#include "../include/vector3.h"
#include <math.h>

Vector3 vector3_create(float x, float y, float z) {
	Vector3 v = {x, y, z};
	return v;
}

float vector3_length(const Vector3* v) {
	return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

void vector3_add(const Vector3* left, const Vector3* right, Vector3* dest) {
	dest->x = left->x + right->x;
	dest->y = left->y + right->y;
	dest->z = left->z + right->z;
}

void vector3_sub(const Vector3* left, const Vector3* right, Vector3* dest) {
	dest->x = left->x - right->x;
	dest->y = left->y - right->y;
	dest->z = left->z - right->z;
}

void vector3_mul(const Vector3* left, const Vector3* right, Vector3* dest) {
	dest->x = left->x * right->x;
	dest->y = left->y * right->y;
	dest->z = left->z * right->z;
}

void cross3(const Vector3* one, const Vector3* two, Vector3* dest) {
	dest->x = (one->y * two->z) - (one->z * two->y);
	dest->y = (one->z * two->x) - (one->x * two->y);
	dest->z = (one->x * two->y) - (one->y * two->x);
}

void lerp3(const Vector3 *a, const Vector3 *b, float t, Vector3 *dest) {
	dest->x = a->x + ((b->x - a->x) * t);
	dest->y = a->y + ((b->y - a->y) * t);
	dest->z = a->z + ((b->z - a->z) * t);
}

float dot3(const Vector3* a, const Vector3* b) {
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

float angle3(const Vector3* a, const Vector3* b) {
	float dot_product = dot3(a, b);
	return acos(dot_product/(vector3_length(a) * vector3_length(b))); 
}

float dist3(const Vector3* a, const Vector3* b) {
	float x = a->x - b->x;
	float y = a->y - b->y;
	float z = a->z - b->z;

	return sqrt(x * x + y * y + z * z);
}

void normalize3(Vector3* v) {
	float length = vector3_length(v);

	if (length != 0) {
		v->x /= length;
		v->y /= length;
		v->z /= length;
	}	
}

void scale3(Vector3* v, float s) {
	v->x *= s;
	v->y *= s;
	v->z *= s;
}
