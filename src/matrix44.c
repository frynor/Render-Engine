#include "../include/matrix44.h"
#include <math.h>
#include <stdio.h>

#define DET33(t00, t01, t02, t10, t11, t12, t20, t21, t22) (((t00) * ((t11) * (t22) - (t12) * (t21))) + ((t01) * ((t12) * (t20) - (t10) * (t22))) + ((t02) * ((t10) * (t21) - (t11) * (t20))))

Matrix44 matrix44_create(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
	Matrix44 mat = {m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33};
	return mat;
}

Matrix44 matrix44_create_default(void) {
	Matrix44 mat = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return mat;
}

Matrix44 matrix44_create_copy(const Matrix44* other) {
	Matrix44 mat = {other->m00, other->m01, other->m02, other->m03, other->m10, other->m11, other->m12, other->m13, other->m20, other->m21, other->m22, other->m23, other->m30, other->m31, other->m32, other->m33};
	return mat;	
}

void matrix44_print(const Matrix44* mat) {
	printf("%f %f %f %f\n", mat->m00, mat->m01, mat->m02, mat->m03);
	printf("%f %f %f %f\n", mat->m10, mat->m11, mat->m12, mat->m13);
	printf("%f %f %f %f\n", mat->m20, mat->m21, mat->m22, mat->m23);
	printf("%f %f %f %f\n", mat->m30, mat->m31, mat->m32, mat->m33);
}

void matrix44_add(const Matrix44* left, const Matrix44* right, Matrix44* dest) {
    if (!left || !right || !dest) return;
    
    dest->m00 = left->m00 + right->m00;
    dest->m01 = left->m01 + right->m01;
    dest->m02 = left->m02 + right->m02;
    dest->m03 = left->m03 + right->m03;
    
    dest->m10 = left->m10 + right->m10;
    dest->m11 = left->m11 + right->m11;
    dest->m12 = left->m12 + right->m12;
    dest->m13 = left->m13 + right->m13;
    
    dest->m20 = left->m20 + right->m20;
    dest->m21 = left->m21 + right->m21;
    dest->m22 = left->m22 + right->m22;
    dest->m23 = left->m23 + right->m23;
    
    dest->m30 = left->m30 + right->m30;
    dest->m31 = left->m31 + right->m31;
    dest->m32 = left->m32 + right->m32;
    dest->m33 = left->m33 + right->m33;
}

void matrix44_sub(const Matrix44* left, const Matrix44* right, Matrix44* dest) {
    if (!left || !right || !dest) return;
    
    dest->m00 = left->m00 - right->m00;
    dest->m01 = left->m01 - right->m01;
    dest->m02 = left->m02 - right->m02;
    dest->m03 = left->m03 - right->m03;
    
    dest->m10 = left->m10 - right->m10;
    dest->m11 = left->m11 - right->m11;
    dest->m12 = left->m12 - right->m12;
    dest->m13 = left->m13 - right->m13;
    
    dest->m20 = left->m20 - right->m20;
    dest->m21 = left->m21 - right->m21;
    dest->m22 = left->m22 - right->m22;
    dest->m23 = left->m23 - right->m23;
    
    dest->m30 = left->m30 - right->m30;
    dest->m31 = left->m31 - right->m31;
    dest->m32 = left->m32 - right->m32;
    dest->m33 = left->m33 - right->m33;
}

void matrix44_mul(const Matrix44* left, const Matrix44* right, Matrix44* dest) {
    if (!left || !right || !dest) return;
    
    float m00 = left->m00 * right->m00 + left->m01 * right->m10 + left->m02 * right->m20 + left->m03 * right->m30;
    float m01 = left->m00 * right->m01 + left->m01 * right->m11 + left->m02 * right->m21 + left->m03 * right->m31;
    float m02 = left->m00 * right->m02 + left->m01 * right->m12 + left->m02 * right->m22 + left->m03 * right->m32;
    float m03 = left->m00 * right->m03 + left->m01 * right->m13 + left->m02 * right->m23 + left->m03 * right->m33;
    
    float m10 = left->m10 * right->m00 + left->m11 * right->m10 + left->m12 * right->m20 + left->m13 * right->m30;
    float m11 = left->m10 * right->m01 + left->m11 * right->m11 + left->m12 * right->m21 + left->m13 * right->m31;
    float m12 = left->m10 * right->m02 + left->m11 * right->m12 + left->m12 * right->m22 + left->m13 * right->m32;
    float m13 = left->m10 * right->m03 + left->m11 * right->m13 + left->m12 * right->m23 + left->m13 * right->m33;
    
    float m20 = left->m20 * right->m00 + left->m21 * right->m10 + left->m22 * right->m20 + left->m23 * right->m30;
    float m21 = left->m20 * right->m01 + left->m21 * right->m11 + left->m22 * right->m21 + left->m23 * right->m31;
    float m22 = left->m20 * right->m02 + left->m21 * right->m12 + left->m22 * right->m22 + left->m23 * right->m32;
    float m23 = left->m20 * right->m03 + left->m21 * right->m13 + left->m22 * right->m23 + left->m23 * right->m33;
    
    float m30 = left->m30 * right->m00 + left->m31 * right->m10 + left->m32 * right->m20 + left->m33 * right->m30;
    float m31 = left->m30 * right->m01 + left->m31 * right->m11 + left->m32 * right->m21 + left->m33 * right->m31;
    float m32 = left->m30 * right->m02 + left->m31 * right->m12 + left->m32 * right->m22 + left->m33 * right->m32;
    float m33 = left->m30 * right->m03 + left->m31 * right->m13 + left->m32 * right->m23 + left->m33 * right->m33;
    
    dest->m00 = m00; dest->m01 = m01; dest->m02 = m02; dest->m03 = m03;
    dest->m10 = m10; dest->m11 = m11; dest->m12 = m12; dest->m13 = m13;
    dest->m20 = m20; dest->m21 = m21; dest->m22 = m22; dest->m23 = m23;
    dest->m30 = m30; dest->m31 = m31; dest->m32 = m32; dest->m33 = m33;
}

void matrix44_trans(const Matrix44* left, const Vector4* right, Vector4* dest) {
    if (!left || !right || !dest) return;
    
    float x = left->m00 * right->x + left->m01 * right->y + left->m02 * right->z + left->m03 * right->w;
    float y = left->m10 * right->x + left->m11 * right->y + left->m12 * right->z + left->m13 * right->w;
    float z = left->m20 * right->x + left->m21 * right->y + left->m22 * right->z + left->m23 * right->w;
    float w = left->m30 * right->x + left->m31 * right->y + left->m32 * right->z + left->m33 * right->w;
    
    dest->x = x;
    dest->y = y;
    dest->z = z;
    dest->w = w;
}

void matrix44_identity(Matrix44* mat) {
    if (!mat) return;
    
    mat->m00 = 1.0f; mat->m01 = 0.0f; mat->m02 = 0.0f; mat->m03 = 0.0f;
    mat->m10 = 0.0f; mat->m11 = 1.0f; mat->m12 = 0.0f; mat->m13 = 0.0f;
    mat->m20 = 0.0f; mat->m21 = 0.0f; mat->m22 = 1.0f; mat->m23 = 0.0f;
    mat->m30 = 0.0f; mat->m31 = 0.0f; mat->m32 = 0.0f; mat->m33 = 1.0f;
}

void matrix44_set_zero(Matrix44* mat) {
    if (!mat) return;
    
    mat->m00 = 0.0f; mat->m01 = 0.0f; mat->m02 = 0.0f; mat->m03 = 0.0f;
    mat->m10 = 0.0f; mat->m11 = 0.0f; mat->m12 = 0.0f; mat->m13 = 0.0f;
    mat->m20 = 0.0f; mat->m21 = 0.0f; mat->m22 = 0.0f; mat->m23 = 0.0f;
    mat->m30 = 0.0f; mat->m31 = 0.0f; mat->m32 = 0.0f; mat->m33 = 0.0f;
}

void matrix44_transpose(Matrix44* mat) {
    if (!mat) return;
    
    float temp;
    temp = mat->m01; mat->m01 = mat->m10; mat->m10 = temp;
    temp = mat->m02; mat->m02 = mat->m20; mat->m20 = temp;
    temp = mat->m03; mat->m03 = mat->m30; mat->m30 = temp;
    temp = mat->m12; mat->m12 = mat->m21; mat->m21 = temp;
    temp = mat->m13; mat->m13 = mat->m31; mat->m31 = temp;
    temp = mat->m23; mat->m23 = mat->m32; mat->m32 = temp;
}

float det44(const Matrix44* mat) {
    if (!mat) return 0.0f;
    
    return mat->m00 * DET33(mat->m11, mat->m12, mat->m13,
                           mat->m21, mat->m22, mat->m23,
                           mat->m31, mat->m32, mat->m33)
         - mat->m01 * DET33(mat->m10, mat->m12, mat->m13,
                           mat->m20, mat->m22, mat->m23,
                           mat->m30, mat->m32, mat->m33)
         + mat->m02 * DET33(mat->m10, mat->m11, mat->m13,
                           mat->m20, mat->m21, mat->m23,
                           mat->m30, mat->m31, mat->m33)
         - mat->m03 * DET33(mat->m10, mat->m11, mat->m12,
                           mat->m20, mat->m21, mat->m22,
                           mat->m30, mat->m31, mat->m32);
}

void matrix44_invert(Matrix44* mat) {
    if (!mat) return;
    
    float determinant = det44(mat);
    if (determinant != 0) {
        float inv_det = 1.0f / determinant;
        
        // Calculate cofactors and adjugate matrix
        float t00 =  DET33(mat->m11, mat->m12, mat->m13, mat->m21, mat->m22, mat->m23, mat->m31, mat->m32, mat->m33) * inv_det;
        float t01 = -DET33(mat->m01, mat->m02, mat->m03, mat->m21, mat->m22, mat->m23, mat->m31, mat->m32, mat->m33) * inv_det;
        float t02 =  DET33(mat->m01, mat->m02, mat->m03, mat->m11, mat->m12, mat->m13, mat->m31, mat->m32, mat->m33) * inv_det;
        float t03 = -DET33(mat->m01, mat->m02, mat->m03, mat->m11, mat->m12, mat->m13, mat->m21, mat->m22, mat->m23) * inv_det;
        
        float t10 = -DET33(mat->m10, mat->m12, mat->m13, mat->m20, mat->m22, mat->m23, mat->m30, mat->m32, mat->m33) * inv_det;
        float t11 =  DET33(mat->m00, mat->m02, mat->m03, mat->m20, mat->m22, mat->m23, mat->m30, mat->m32, mat->m33) * inv_det;
        float t12 = -DET33(mat->m00, mat->m02, mat->m03, mat->m10, mat->m12, mat->m13, mat->m30, mat->m32, mat->m33) * inv_det;
        float t13 =  DET33(mat->m00, mat->m02, mat->m03, mat->m10, mat->m12, mat->m13, mat->m20, mat->m22, mat->m23) * inv_det;
        
        float t20 =  DET33(mat->m10, mat->m11, mat->m13, mat->m20, mat->m21, mat->m23, mat->m30, mat->m31, mat->m33) * inv_det;
        float t21 = -DET33(mat->m00, mat->m01, mat->m03, mat->m20, mat->m21, mat->m23, mat->m30, mat->m31, mat->m33) * inv_det;
        float t22 =  DET33(mat->m00, mat->m01, mat->m03, mat->m10, mat->m11, mat->m13, mat->m30, mat->m31, mat->m33) * inv_det;
        float t23 = -DET33(mat->m00, mat->m01, mat->m03, mat->m10, mat->m11, mat->m13, mat->m20, mat->m21, mat->m23) * inv_det;
        
        float t30 = -DET33(mat->m10, mat->m11, mat->m12, mat->m20, mat->m21, mat->m22, mat->m30, mat->m31, mat->m32) * inv_det;
        float t31 =  DET33(mat->m00, mat->m01, mat->m02, mat->m20, mat->m21, mat->m22, mat->m30, mat->m31, mat->m32) * inv_det;
	float t32 = -DET33(mat->m00, mat->m01, mat->m02, mat->m10, mat->m11, mat->m12, mat->m30, mat->m31, mat->m32) * inv_det;
        float t33 =  DET33(mat->m00, mat->m01, mat->m02, mat->m10, mat->m11, mat->m12, mat->m20, mat->m21, mat->m22) * inv_det;
        
        mat->m00 = t00; mat->m01 = t01; mat->m02 = t02; mat->m03 = t03;
        mat->m10 = t10; mat->m11 = t11; mat->m12 = t12; mat->m13 = t13;
        mat->m20 = t20; mat->m21 = t21; mat->m22 = t22; mat->m23 = t23;
        mat->m30 = t30; mat->m31 = t31; mat->m32 = t32; mat->m33 = t33;
	}
}

void matrix44_negate(Matrix44* mat) {
    if (!mat) return;
    
    mat->m00 = -mat->m00; mat->m01 = -mat->m01; mat->m02 = -mat->m02; mat->m03 = -mat->m03;
    mat->m10 = -mat->m10; mat->m11 = -mat->m11; mat->m12 = -mat->m12; mat->m13 = -mat->m13;
    mat->m20 = -mat->m20; mat->m21 = -mat->m21; mat->m22 = -mat->m22; mat->m23 = -mat->m23;
    mat->m30 = -mat->m30; mat->m31 = -mat->m31; mat->m32 = -mat->m32; mat->m33 = -mat->m33;
}

void scale(Matrix44* mat, const Vector3* scale) {
	if (!mat) return;

	mat->m00 *= scale->x;
	mat->m01 *= scale->x;
	mat->m02 *= scale->x;
	mat->m03 *= scale->x;
	mat->m10 *= scale->y;
	mat->m11 *= scale->y;
	mat->m12 *= scale->y;
	mat->m13 *= scale->y;
	mat->m20 *= scale->z;
	mat->m21 *= scale->z;
	mat->m22 *= scale->z;
	mat->m23 *= scale->z;
}

void rotate(Matrix44 *mat, const Vector3 *eulerAxis, float angle) {
    if (!mat) return;

    float c = (float) cos(angle);
    float s = (float) sin(angle);
    float oneminusc = 1.0f - c;
    float xy = eulerAxis->x * eulerAxis->y;
    float yz = eulerAxis->y * eulerAxis->z;
    float xz = eulerAxis->x * eulerAxis->z;
    float xs = eulerAxis->x * s;
    float ys = eulerAxis->y * s;
    float zs = eulerAxis->z * s;

    float f00 = eulerAxis->x * eulerAxis->x * oneminusc + c;
    float f01 = xy * oneminusc - zs;
    float f02 = xz * oneminusc + ys;

    float f10 = xy * oneminusc + zs;
    float f11 = eulerAxis->y * eulerAxis->y * oneminusc + c;
    float f12 = yz * oneminusc - xs;

    float f20 = xz * oneminusc - ys;
    float f21 = yz * oneminusc + xs;
    float f22 = eulerAxis->z * eulerAxis->z * oneminusc + c;

    float t00 = mat->m00, t01 = mat->m01, t02 = mat->m02, t03 = mat->m03;
    float t10 = mat->m10, t11 = mat->m11, t12 = mat->m12, t13 = mat->m13;
    float t20 = mat->m20, t21 = mat->m21, t22 = mat->m22, t23 = mat->m23;

    mat->m00 = f00 * t00 + f01 * t10 + f02 * t20;
    mat->m01 = f00 * t01 + f01 * t11 + f02 * t21;
    mat->m02 = f00 * t02 + f01 * t12 + f02 * t22;
    mat->m03 = f00 * t03 + f01 * t13 + f02 * t23;

    mat->m10 = f10 * t00 + f11 * t10 + f12 * t20;
    mat->m11 = f10 * t01 + f11 * t11 + f12 * t21;
    mat->m12 = f10 * t02 + f11 * t12 + f12 * t22;
    mat->m13 = f10 * t03 + f11 * t13 + f12 * t23;

    mat->m20 = f20 * t00 + f21 * t10 + f22 * t20;
    mat->m21 = f20 * t01 + f21 * t11 + f22 * t21;
    mat->m22 = f20 * t02 + f21 * t12 + f22 * t22;
    mat->m23 = f20 * t03 + f21 * t13 + f22 * t23;
}

void translate(Matrix44 *mat, const Vector3 *translation) {
	if (!mat || !translation) return;

	mat->m30 += mat->m00 * translation->x + mat->m10 * translation->y + mat->m20 * translation->z;
	mat->m31 += mat->m01 * translation->x + mat->m11 * translation->y + mat->m21 * translation->z;
	mat->m32 += mat->m02 * translation->x + mat->m12 * translation->y + mat->m22 * translation->z;
	mat->m33 += mat->m03 * translation->x + mat->m13 * translation->y + mat->m23 * translation->z;
}
