#ifndef MATRIX44_H
#define MATRIX44_H

#include "vector3.h"
#include "vector4.h"

typedef struct {
	float m00, m01, m02, m03; // First row
	float m10, m11, m12, m13; // Second row
	float m20, m21, m22, m23; // Third row
	float m30, m31, m32, m33; // Fourth row
} Matrix44;

void matrix44_add(const Matrix44* left, const Matrix44* right, Matrix44* dest);
void matrix44_sub(const Matrix44* left, const Matrix44* right, Matrix44* dest);
void matrix44_mul(const Matrix44* left, const Matrix44* right, Matrix44* dest);
void matrix44_trans(const Matrix44* left, const Vector4* right, Vector4* dest);

void scale(Matrix44* mat, const Vector3* scale);
void rotate(Matrix44* mat, const Vector3* eulerAxis, float angle);

void matrix44_identity(Matrix44* mat);
void matrix44_set_zero(Matrix44* mat);
void matrix44_transpose(Matrix44* mat);
void matrix44_invert(Matrix44* mat);
void matrix44_negate(Matrix44* mat);
float det44(const Matrix44* mat);

#endif // MATRIX44_H


