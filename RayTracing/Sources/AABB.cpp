#include "AABB.h"

#include "MathUtility.h"

AABB::AABB(Vector3 const& minimum, Vector3 const& maximum)
	: minimum(minimum), maximum(maximum)
{
}

bool AABB::Hit(Ray const& ray, float tMin, float tMax) const
{
	for (int a = 0; a < 3; a++)
	{
		float inverseDirection = 1.f / ray.direction[a];
		float t0 = (minimum[a] - ray.origin[a]) * inverseDirection;
		float t1 = (maximum[a] - ray.origin[a]) * inverseDirection;

		if (inverseDirection < 0.f)
		{
			std::swap(t0, t1);
		}

		tMin = ffmax(t0, tMin);
		tMax = ffmin(t1, tMax);

		if (tMax <= tMin)
			return false;
	}

	return true;
}

AABB AABB::SurroundingBox(AABB const& box0, AABB const& box1)
{
	Vector3 small(ffmin(box0.minimum.x(), box1.minimum.x()),
		ffmin(box0.minimum.y(), box1.minimum.y()),
		ffmin(box0.minimum.z(), box1.minimum.z()));

	Vector3 big(ffmax(box0.maximum.x(), box1.maximum.x()),
		ffmax(box0.maximum.y(), box1.maximum.y()),
		ffmax(box0.maximum.z(), box1.maximum.z()));

	return AABB(small, big);
}