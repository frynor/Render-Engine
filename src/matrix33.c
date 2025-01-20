#include "../include/matrix33.h"

void matrix33_add(const Matrix33* left, const Matrix33* right, Matrix33* dest) {
    if (!left || !right || !dest) return;
    
    dest->m00 = left->m00 + right->m00;
    dest->m01 = left->m01 + right->m01;
    dest->m02 = left->m02 + right->m02;
    
    dest->m10 = left->m10 + right->m10;
    dest->m11 = left->m11 + right->m11;
    dest->m12 = left->m12 + right->m12;
    
    dest->m20 = left->m20 + right->m20;
    dest->m21 = left->m21 + right->m21;
    dest->m22 = left->m22 + right->m22;
}

void matrix33_sub(const Matrix33* left, const Matrix33* right, Matrix33* dest) {
    if (!left || !right || !dest) return;
    
    dest->m00 = left->m00 - right->m00;
    dest->m01 = left->m01 - right->m01;
    dest->m02 = left->m02 - right->m02;
    
    dest->m10 = left->m10 - right->m10;
    dest->m11 = left->m11 - right->m11;
    dest->m12 = left->m12 - right->m12;
    
    dest->m20 = left->m20 - right->m20;
    dest->m21 = left->m21 - right->m21;
    dest->m22 = left->m22 - right->m22;
}

void matrix33_mul(const Matrix33* left, const Matrix33* right, Matrix33* dest) {
    if (!left || !right || !dest) return;
    
    float m00 = left->m00 * right->m00 + left->m01 * right->m10 + left->m02 * right->m20;
    float m01 = left->m00 * right->m01 + left->m01 * right->m11 + left->m02 * right->m21;
    float m02 = left->m00 * right->m02 + left->m01 * right->m12 + left->m02 * right->m22;
    
    float m10 = left->m10 * right->m00 + left->m11 * right->m10 + left->m12 * right->m20;
    float m11 = left->m10 * right->m01 + left->m11 * right->m11 + left->m12 * right->m21;
    float m12 = left->m10 * right->m02 + left->m11 * right->m12 + left->m12 * right->m22;
    
    float m20 = left->m20 * right->m00 + left->m21 * right->m10 + left->m22 * right->m20;
    float m21 = left->m20 * right->m01 + left->m21 * right->m11 + left->m22 * right->m21;
    float m22 = left->m20 * right->m02 + left->m21 * right->m12 + left->m22 * right->m22;
    
    dest->m00 = m00; dest->m01 = m01; dest->m02 = m02;
    dest->m10 = m10; dest->m11 = m11; dest->m12 = m12;
    dest->m20 = m20; dest->m21 = m21; dest->m22 = m22;
}

void matrix33_trans(const Matrix33* left, const Vector3* right, Vector3* dest) {
    if (!left || !right || !dest) return;
    
    float x = left->m00 * right->x + left->m01 * right->y + left->m02 * right->z;
    float y = left->m10 * right->x + left->m11 * right->y + left->m12 * right->z;
    float z = left->m20 * right->x + left->m21 * right->y + left->m22 * right->z;
    
    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void matrix33_identity(Matrix33* mat) {
    if (!mat) return;
    
    mat->m00 = 1.0f; mat->m01 = 0.0f; mat->m02 = 0.0f;
    mat->m10 = 0.0f; mat->m11 = 1.0f; mat->m12 = 0.0f;
    mat->m20 = 0.0f; mat->m21 = 0.0f; mat->m22 = 1.0f;
}

void matrix33_set_zero(Matrix33* mat) {
    if (!mat) return;
    
    mat->m00 = 0.0f; mat->m01 = 0.0f; mat->m02 = 0.0f;
    mat->m10 = 0.0f; mat->m11 = 0.0f; mat->m12 = 0.0f;
    mat->m20 = 0.0f; mat->m21 = 0.0f; mat->m22 = 0.0f;
}

void matrix33_transpose(Matrix33* mat) {
    if (!mat) return;
    
    float temp;
    temp = mat->m01; mat->m01 = mat->m10; mat->m10 = temp;
    temp = mat->m02; mat->m02 = mat->m20; mat->m20 = temp;
    temp = mat->m12; mat->m12 = mat->m21; mat->m21 = temp;
}

float det33(const Matrix33* mat) {
    if (!mat) return 0.0f;
    
    return mat->m00 * (mat->m11 * mat->m22 - mat->m12 * mat->m21)
         - mat->m01 * (mat->m10 * mat->m22 - mat->m12 * mat->m20)
         + mat->m02 * (mat->m10 * mat->m21 - mat->m11 * mat->m20);
}

void matrix33_invert(Matrix33* mat) {
    if (!mat) return;
    
    float determinant = det33(mat);
    if (determinant != 0) {
        float inv_det = 1.0f / determinant;
        
        float t00 = (mat->m11 * mat->m22 - mat->m21 * mat->m12) * inv_det;
        float t01 = -(mat->m01 * mat->m22 - mat->m21 * mat->m02) * inv_det;
        float t02 = (mat->m01 * mat->m12 - mat->m11 * mat->m02) * inv_det;
        
        float t10 = -(mat->m10 * mat->m22 - mat->m20 * mat->m12) * inv_det;
        float t11 = (mat->m00 * mat->m22 - mat->m20 * mat->m02) * inv_det;
        float t12 = -(mat->m00 * mat->m12 - mat->m10 * mat->m02) * inv_det;
        
        float t20 = (mat->m10 * mat->m21 - mat->m20 * mat->m11) * inv_det;
        float t21 = -(mat->m00 * mat->m21 - mat->m20 * mat->m01) * inv_det;
        float t22 = (mat->m00 * mat->m11 - mat->m10 * mat->m01) * inv_det;
        
        mat->m00 = t00; mat->m01 = t01; mat->m02 = t02;
        mat->m10 = t10; mat->m11 = t11; mat->m12 = t12;
        mat->m20 = t20; mat->m21 = t21; mat->m22 = t22;
    }
}

void matrix33_negate(Matrix33* mat) {
    if (!mat) return;
    
    mat->m00 = -mat->m00; mat->m01 = -mat->m01; mat->m02 = -mat->m02;
    mat->m10 = -mat->m10; mat->m11 = -mat->m11; mat->m12 = -mat->m12;
    mat->m20 = -mat->m20; mat->m21 = -mat->m21; mat->m22 = -mat->m22;
}
