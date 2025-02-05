#include "../include/cameraPerspective.h"
#include <stdlib.h>

Camera* camera_initialize() {
	Camera* cam = (Camera*)malloc(sizeof(Camera));
	if (!cam) {
		return NULL;
	}
	cam->position = (Vector3){0.0f, 0.0f, 0.0f};
	cam->rotation = (Vector3){0.0f, 0.0f, 0.0f};
	matrix44_identity(&cam->viewMatrix);
	matrix44_identity(&cam->projMatrix);

	return cam;
}
