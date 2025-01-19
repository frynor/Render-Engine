#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct {
	float x;
	float y;
	float z;
} Vector3;

// Creating the original vector
Vector3 vector3_create(float x, float y, float z);

// Getting the length of the vector
float vector3_length(const Vector3* v);

// Adding/Subtracting/Multiplying the two vectors 
void vector3_add(const Vector3* left, const Vector3* right, Vector3* dest);
void vector3_sub(const Vector3* left, const Vector3* right, Vector3* dest);
void vector3_mul(const Vector3* left, const Vector3* right, Vector3* dest);
void cross3(const Vector3* one, const Vector3* two, Vector3* dest);
void lerp3(const Vector3* a, const Vector3* b, float t, Vector3* dest);

// Dot product/Angle/Distance in vectors
float dot3(const Vector3* a, const Vector3* b);
float angle3(const Vector3* a, const Vector3* b);
float dist3(const Vector3* a, const Vector3* b);

// Vector normalization
void normalize3(Vector3* v);

void scale3(Vector3* v, float s);

#endif // VECTOR3_H

