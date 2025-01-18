#ifndef VECTOR2_H
#define VECTOR2_H

typedef struct {
	float x;
	float y;
} Vector2;

// Creating the original vector
Vector2 vector2_create(float x, float y);

// Adding the two vectors 
void vector2_add(const Vector2* left, const Vector2* right, Vector2* dest);

// Getting the length of the vector
float vector2_length(const Vector2* v);


#endif // VECTOR2_H
