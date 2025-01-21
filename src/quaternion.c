#include "../include/quaternion.h"
#include <math.h>

Quaternion quaternion_create(float x, float y, float z, float w) {
	Quaternion q = {x, y, z, w};
	return q;
}

Quaternion quaternion_copy(const Quaternion* q) {
	Quaternion quat = {q->x, q->y, q->z, q->w};
	return quat;
}

void quaternion_set_identity(Quaternion* q) {
	q->x = 0;
	q->y = 0;
	q->z = 0;
	q->w = 1;
}

float quaternion_length(const Quaternion* q) {
	return sqrt(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);	
}

void quaternion_normalize(Quaternion* q) {
	float mag = quaternion_length(q);

	q->x /= mag;
	q->y /= mag;
	q->z /= mag;
	q->w /= mag;
}

void quaternion_negate(Quaternion* q) {
	q->x *= -1.0f;
	q->y *= -1.0f;
	q->z *= -1.0f;
	q->w *= -1.0f;
}

Quaternion quaternion_from_axis_angle(const Vector3* axis, float angle) {
	Matrix44 rot;
	Quaternion q;
	rotate(&rot, axis, angle);

	quaternion_from_matrix(&q, &rot);
	quaternion_normalize(&q);
	return q;
}

Matrix44 quaternion_to_matrix(const Quaternion* q) {
	Matrix44 matrix;

	float xy = q->x * q->y;
	float xz = q->x * q->z;
	float xw = q->x * q->w;
	float yz = q->y * q->z;
	float yw = q->y * q->w;
	float zw = q->z * q->w;
	float xSquared = q->x * q->x;
	float ySquared = q->y * q->y;
	float zSquared = q->z * q->z;

	matrix.m00 = 1 - 2 * (ySquared + zSquared);
	matrix.m01 = 2 * (xy - zw);
	matrix.m02 = 2 * (xz + yw);
	matrix.m03 = 0;
	matrix.m10 = 2 * (xy + zw);
	matrix.m11 = 1 - 2 * (xSquared + zSquared);
	matrix.m12 = 2 * (yz - xw);
	matrix.m13 = 0;
	matrix.m20 = 2 * (xz - yw);
	matrix.m21 = 2 * (yz + xw);
	matrix.m22 = 1 - 2 * (xSquared + ySquared);
	matrix.m23 = 0;
	matrix.m30 = 0;
	matrix.m31 = 0;
	matrix.m32 = 0;
	matrix.m33 = 1;

	return matrix;
}

// Multiplication operations
Quaternion quaternion_multiply(const Quaternion* q1, const Quaternion* q2) {
    return quaternion_create(
        q1->x * q2->w + q1->w * q2->x + q1->y * q2->z - q1->z * q2->y,
        q1->y * q2->w + q1->w * q2->y + q1->z * q2->x - q1->x * q2->z,
        q1->z * q2->w + q1->w * q2->z + q1->x * q2->y - q1->y * q2->x,
        q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z
    );
}

Vector3 quaternion_multiply_vector3(const Quaternion* q, const Vector3* v) {
    Matrix44 trans = quaternion_to_matrix(q);
    Vector4 mod = matrix44_multiply_vector4(&trans, &(Vector4){v->x, v->y, v->z, 0});
    return (Vector3){mod.x, mod.y, mod.z};
}

Vector4 quaternion_multiply_vector4(const Quaternion* q, const Vector4* v) {
    Matrix44 trans = quaternion_to_matrix(q);
    return matrix44_multiply_vector4(&trans, v);
}

void quaternion_set_axis_angle(Quaternion* q, const Vector3* axis, float angle) {
    Matrix44 rot;
    rotate(&rot, axis, angle);

    quaternion_from_matrix(q, &rot);
    quaternion_normalize(q);
}

Quaternion quaternion_slerp(const Quaternion* a, const Quaternion* b, float blend) {
    Quaternion result;
    float dot = a->w * b->w + a->x * b->x + a->y * b->y + a->z * b->z;
    float blendI = 1.0f - blend;

    if (dot < 0) {
        result.w = blendI * a->w + blend * -b->w;
        result.x = blendI * a->x + blend * -b->x;
        result.y = blendI * a->y + blend * -b->y;
        result.z = blendI * a->z + blend * -b->z;
    } else {
        result.w = blendI * a->w + blend * b->w;
        result.x = blendI * a->x + blend * b->x;
        result.y = blendI * a->y + blend * b->y;
        result.z = blendI * a->z + blend * b->z;
    }

    quaternion_normalize(&result);
    return result;
}

void quaternion_look_rotation(Quaternion* q, const Vector3* forward, const Vector3* up) {
    Vector3 normalized_forward = *forward;
    Vector3 normalized_up = *up;

    normalize3(&normalized_forward);
    normalize3(&normalized_up);
    Vector3 right;
    cross3(&normalized_forward, &normalized_up, &right);

    Matrix44 rot = {0};
    rot.m00 = right.x;
    rot.m10 = right.y;
    rot.m20 = right.z;

    rot.m01 = normalized_up.x;
    rot.m11 = normalized_up.y;
    rot.m21 = normalized_up.z;

    rot.m02 = normalized_forward.x;
    rot.m12 = normalized_forward.y;
    rot.m22 = normalized_forward.z;
    rot.m33 = 1;

    quaternion_from_matrix(q, &rot);
    quaternion_normalize(q);
}

void quaternion_from_matrix(Quaternion* q, const Matrix44* matrix) {
    float m00 = matrix->m00;
    float m01 = matrix->m01;
    float m02 = matrix->m02;
    float m10 = matrix->m10;
    float m11 = matrix->m11;
    float m12 = matrix->m12;
    float m20 = matrix->m20;
    float m21 = matrix->m21;
    float m22 = matrix->m22;

    float s;
    float tr = m00 + m11 + m22;
    
    if (tr >= 0.0f) {
        s = sqrtf(tr + 1.0f);
        q->w = s * 0.5f;
        s = 0.5f / s;
        q->x = (m21 - m12) * s;
        q->y = (m02 - m20) * s;
        q->z = (m10 - m01) * s;
    } else {
        float max = MAX(MAX(m00, m11), m22);
        if (max == m00) {
            s = sqrtf(m00 - (m11 + m22) + 1.0f);
            q->x = s * 0.5f;
            s = 0.5f / s;
            q->y = (m01 + m10) * s;
            q->z = (m20 + m02) * s;
            q->w = (m21 - m12) * s;
        } else if (max == m11) {
            s = sqrtf(m11 - (m22 + m00) + 1.0f);
            q->y = s * 0.5f;
            s = 0.5f / s;
            q->z = (m12 + m21) * s;
            q->x = (m01 + m10) * s;
            q->w = (m02 - m20) * s;
        } else {
            s = sqrtf(m22 - (m00 + m11) + 1.0f);
            q->z = s * 0.5f;
            s = 0.5f / s;
            q->x = (m20 + m02) * s;
            q->y = (m12 + m21) * s;
            q->w = (m10 - m01) * s;
        }
    }
}
