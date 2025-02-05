#ifndef INCLUDE_CAMERA_H
#define INCLUDE_CAMERA_H

#include "../include/vector2.h"
#include "../include/vector3.h"
#include "../include/vector4.h"
#include "../include/matrix44.h"


typedef struct {
	float fov;
	float aspect;
	float zNear;
	float zFar;
	Vector3 position;
	Vector3 rotation;
	Matrix44 viewMatrix;
	Matrix44 projMatrix;
} Camera;

Camera* camera_initialize();
void camera_destroy(Camera* camera);

// Function to calculate the view matrix
void camera_calculate_view_matrix(Camera* camera);

// Function to get the Projection-View (PV) matrix
Matrix44 camera_get_pv_matrix(const Camera* camera);

void camera_create_projection(Camera* camera, float fov, float aspect, float zNear, float zFar);

#endif // INCLUDE_CAMERA_H
