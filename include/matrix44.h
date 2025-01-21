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

Matrix44 matrix44_create(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
Matrix44 matrix44_create_default(void);
Matrix44 matrix44_create_copy(const Matrix44* other);
void matrix44_print(const Matrix44* mat);

void matrix44_add(const Matrix44* left, const Matrix44* right, Matrix44* dest);
void matrix44_sub(const Matrix44* left, const Matrix44* right, Matrix44* dest);
void matrix44_mul(const Matrix44* left, const Matrix44* right, Matrix44* dest);
void matrix44_trans(const Matrix44* left, const Vector4* right, Vector4* dest);

void scale(Matrix44* mat, const Vector3* scale);
void rotate(Matrix44* mat, const Vector3* eulerAxis, float angle);
void translate(Matrix44* mat, const Vector3* translation);

void matrix44_identity(Matrix44* mat);
void matrix44_set_zero(Matrix44* mat);
void matrix44_transpose(Matrix44* mat);
void matrix44_invert(Matrix44* mat);
void matrix44_negate(Matrix44* mat);
float det44(const Matrix44* mat);

#endif // MATRIX44_H


