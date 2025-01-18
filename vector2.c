#include "vector2.h"
#include <math.h>

Vector2 vector2_create(float x, float y) {
	Vector2 v = {x, y};
	return v;
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

float vector2_length(const Vector2* v) {
	return sqrt(v->x * v->x + v->y * v->y);
}
