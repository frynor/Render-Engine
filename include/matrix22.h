#ifndef MATRIX22_H
#define MATRIX22_H

#include "vector2.h"

// 2x2 Matrix
typedef struct {
	float m00, m01; // First row
	float m10, m11; // Second row
} Matrix22;

void matrix22_add(const Matrix22* left, const Matrix22* right, Matrix22* dest);
void matrix22_sub(const Matrix22* left, const Matrix22* right, Matrix22* dest);
void matrix22_mul(const Matrix22* left, const Matrix22* right, Matrix22* dest);
void matrix22_trans(const Matrix22* left, const Vector2* right, Vector2* dest);

void matrix22_identity(Matrix22* mat);
void matrix22_set_zero(Matrix22* mat);
void matrix22_transpose(Matrix22* mat);
void matrix22_invert(Matrix22* mat);
void matrix22_negate(Matrix22* mat);
float det(const Matrix22* mat);

#endif // MATRIX22_H
