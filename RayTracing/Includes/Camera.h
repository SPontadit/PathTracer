#pragma once

#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

#include "Ray.h"

class Camera
{
public:
	Camera(Vector3 lookFrom, Vector3 lookAt, Vector3 up, float verticalFOV, float aspectRation, float aperture, float focusDistance, float openTime, float closeTime);
	~Camera() {}

	Camera(Camera const&) = default;
	Camera(Camera&&) = default;

	Camera& operator=(Camera const&) = default;
	Camera& operator=(Camera&&) = default;

	Ray GetRay(float u, float v);

private:
	Vector3 origin;
	Vector3 lowerLeftCorner;
	Vector3 horizontal;
	Vector3 vertical;

	Vector3 right;
	Vector3 up;
	Vector3 forward;

	float openTime;
	float closeTime;
	float lensRadius;
};

#endif // __CAMERA_H_INCLUDED__