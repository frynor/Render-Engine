#include "../include/quaternion.h"

Quaternion quaternion_create(float x, float y, float z, float w) {
	Quaternion q = {x, y, z, w};
	return q;
}
