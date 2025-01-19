#ifndef VECTOR4_H
#define VECTOR4_H

typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vector4;

// Creating the original vector
Vector4 vector4_create(float x, float y, float z, float w);

// Getting the length of the vector
float vector4_length(const Vector4* v);

// Adding/Subtracting/Multiplying the two vectors 
void vector4_add(const Vector4* left, const Vector4* right, Vector4* dest);
void vector4_sub(const Vector4* left, const Vector4* right, Vector4* dest);
void vector4_mul(const Vector4* left, const Vector4* right, Vector4* dest);
void lerp4(const Vector4* a, const Vector4* b, float t, Vector4* dest);

// Dot product/Angle/Distance in vectors
float dot4(const Vector4* a, const Vector4* b);
float angle4(const Vector4* a, const Vector4* b);
float dist4(const Vector4* a, const Vector4* b);

// Vector normalization
void normalize4(Vector4* v);

void scale4(Vector4* v, float s);

#endif // VECTOR4_H

