#ifndef VECTOR2_H
#define VECTOR2_H

typedef struct {
	float x;
	float y;
} Vector2;

// Creating the original vector
Vector2 vector2_create(float x, float y);

// Adding/Subtracting/Multiplying the two vectors 
void vector2_add(const Vector2* left, const Vector2* right, Vector2* dest);
void vector2_sub(const Vector2* left, const Vector2* right, Vector2* dest);
void vector2_mul(const Vector2* left, const Vector2* right, Vector2* dest);

float dot(const Vector2* a, const Vector2* b);
float angle(const Vector2* a, const Vector2* b);
float dist(const Vector2* a, const Vector2* b);

// Getting the length of the vector
float vector2_length(const Vector2* v);


#endif // VECTOR2_H
