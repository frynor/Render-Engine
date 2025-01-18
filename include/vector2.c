#include "vector2.h"
#include <math.h>

Vector2 vector2_create(float x, float y) {
	Vector2 v = {x, y};
	return v;
}

float vector2_length(const Vector2* v) {
	return sqrt(v->x * v->x + v->y * v->y);
}

void vector2_add(const Vector2* left, const Vector2* right, Vector2* dest) {
	dest->x = left->x + right->x;
	dest->y = left->y + right->y;
}

void vector2_sub(const Vector2* left, const Vector2* right, Vector2* dest) {
	dest->x = left->x - right->x;
	dest->y = left->y - right->y;
}

void vector2_mul(const Vector2* left, const Vector2* right, Vector2* dest) {
	dest->x = left->x * right->x;
	dest->y = left->y * right->y;
}

float dot2(const Vector2* a, const Vector2* b) {
	return a->x * b->x + a->y * b->y;
}

float angle2(const Vector2* a, const Vector2* b) {
	float dot_product = dot2(a, b);
	return acos(dot_product/vector2_length(a) * vector2_length(b)); 
}

float dist2(const Vector2* a, const Vector2* b) {
	float x = a->x - b->x;
	float y = a->y - b->y;

	return sqrt(x * x + y * y);
}

void normalize2(Vector2* v) {
	float length = vector2_length(v);

	if (length != 0) {
		v->x /= length;
		v->y /= length;
	}	
}
