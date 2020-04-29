#include "Camera.h"
#include "MathUtility.h"


Camera::Camera(Vector3 lookFrom, Vector3 lookAt, Vector3 viewUp, float verticalFOV, float aspectRatio, float aperture, float focusDistance, float openTime, float closeTime)
	: origin(lookFrom), openTime(openTime), closeTime(closeTime)
{
	lensRadius = aperture / 2.f;
	float theta = verticalFOV * M_PI / 180.f;
	float halfHeigh = tan(theta / 2.f);
	float halfWidth = aspectRatio * halfHeigh;

	forward = GetUnit(lookFrom - lookAt);
	right = GetUnit(Cross(viewUp, forward));
	up = Cross(forward, right);
	lowerLeftCorner = Vector3(-halfWidth, -halfHeigh, -1.f);
	lowerLeftCorner = origin - halfWidth * focusDistance * right - halfHeigh * focusDistance * up - focusDistance * forward;

	horizontal = halfWidth * 2.f * focusDistance * right;
	vertical = halfHeigh * 2.f * focusDistance * up;
}

Ray Camera::GetRay(float u, float v)
{
	Vector3 direction = lensRadius * RandomInUnitDisk();
	Vector3 offset = right * direction.x() + up * direction.y();

	float time = openTime + drand48() * (closeTime - openTime);
	return Ray(origin + offset, lowerLeftCorner + u * horizontal + v * vertical - origin - offset, time);
}