#ifndef QUATERNION_H
#define QUATERNION_H

#define MAX(a, b) (((a)>(b))? (a) : (b))
#define MIN(a, b) (((a)<(b))? (a) : (b))

#include "../include/vector2.h"
#include "../include/vector3.h" 
#include "../include/vector4.h"
#include "../include/matrix44.h"

typedef struct {
	float x, y, z, w;
} Quaternion;

// Constructor equivalents
Quaternion quaternion_create(float x, float y, float z, float w);
Quaternion quaternion_from_axis_angle(const Vector3* axis, float angle);
Quaternion quaternion_copy(const Quaternion* q);

// Basic operations
void quaternion_set_identity(Quaternion* q);
float quaternion_length(const Quaternion* q);
void quaternion_normalize(Quaternion* q);
void quaternion_negate(Quaternion* q);

// Multiplication operations (replacing operator overloading)
Quaternion quaternion_multiply(const Quaternion* q1, const Quaternion* q2);
Vector3 quaternion_multiply_vector3(const Quaternion* q, const Vector3* v);
Vector4 quaternion_multiply_vector4(const Quaternion* q, const Vector4* v);

// Conversion and special operations
Matrix44 quaternion_to_matrix(const Quaternion* q);
void quaternion_set_axis_angle(Quaternion* q, const Vector3* axis, float angle);
Quaternion quaternion_slerp(const Quaternion* a, const Quaternion* b, float blend);
void quaternion_look_rotation(Quaternion* q, const Vector3* forward, const Vector3* up);
void quaternion_from_matrix(Quaternion* q, const Matrix44* matrix);

#endif // QUATERNION_H
