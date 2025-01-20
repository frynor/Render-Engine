#ifndef MATRIX33_H
#define MATRIX33_H

#include "vector3.h"

typedef struct {
	float m00, m01, m02; // First row
	float m10, m11, m12; // Second row
	float m20, m21, m22; // Third row
} Matrix33;

void matrix33_add(const Matrix33* left, const Matrix33* right, Matrix33* dest);
void matrix33_sub(const Matrix33* left, const Matrix33* right, Matrix33* dest);
void matrix33_mul(const Matrix33* left, const Matrix33* right, Matrix33* dest);
void matrix33_trans(const Matrix33* left, const Vector3* right, Vector3* dest);

void matrix33_identity(Matrix33* mat);
void matrix33_set_zero(Matrix33* mat);
void matrix33_transpose(Matrix33* mat);
void matrix33_invert(Matrix33* mat);
void matrix33_negate(Matrix33* mat);
float det(const Matrix33* mat);

#endif // MATRIX33_H

