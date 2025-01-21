#include "../include/vector4.h"
#include <math.h>

Vector4 vector4_create(float x, float y, float z, float w) {
	Vector4 v = {x, y, z, w};
	return v;
}

float vector4_length(const Vector4* v) {
	return sqrt(v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w);
}

void vector4_add(const Vector4* left, const Vector4* right, Vector4* dest) {
	dest->x = left->x + right->x;
	dest->y = left->y + right->y;
	dest->z = left->z + right->z;
	dest->w = left->w + right->w;
}

void vector4_sub(const Vector4* left, const Vector4* right, Vector4* dest) {
	dest->x = left->x - right->x;
	dest->y = left->y - right->y;
	dest->z = left->z - right->z;
	dest->w = left->w - right->w;
}

void vector4_mul(const Vector4* left, const Vector4* right, Vector4* dest) {
	dest->x = left->x * right->x;
	dest->y = left->y * right->y;
	dest->z = left->z * right->z;
	dest->w = left->w * right->w;
}

void lerp4(const Vector4 *a, const Vector4 *b, float t, Vector4 *dest) {
	dest->x = a->x + ((b->x - a->x) * t);
	dest->y = a->y + ((b->y - a->y) * t);
	dest->z = a->z + ((b->z - a->z) * t);
	dest->w = a->w + ((b->w - a->w) * t);
}

float dot4(const Vector4* a, const Vector4* b) {
	return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

float angle4(const Vector4* a, const Vector4* b) {
	float dot_product = dot4(a, b);
	return acos(dot_product/(vector4_length(a) * vector4_length(b))); 
}

float dist4(const Vector4* a, const Vector4* b) {
	float x = a->x - b->x;
	float y = a->y - b->y;
	float z = a->z - b->z;
	float w = a->w - b->w;

	return sqrt(x * x + y * y + z * z + w * w);
}

void normalize4(Vector4* v) {
	float length = vector4_length(v);

	if (length != 0) {
		v->x /= length;
		v->y /= length;
		v->z /= length;
		v->w /= length;
	}	
}

void scale4(Vector4* v, float s) {
	v->x *= s;
	v->y *= s;
	v->z *= s;
	v->w *= s;
}
