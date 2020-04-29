#include "Translate.h"

Translate::Translate(Hitable* hitable, Vector3 const& offset)
	: Hitable(), hitable(hitable), offset(offset)
{
}

Translate::~Translate()
{
	delete hitable;
}

bool Translate::Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const
{
	Ray offsetRay(ray.origin - offset, ray.direction, ray.time);

	if (hitable->Hit(offsetRay, tMin, tMax, outHitRecord))
	{
		outHitRecord.point += offset;
		return true;
	}

	return false;
}

bool Translate::BoundingBox(float time0, float time1, AABB& boundingBox) const
{
	if (hitable->BoundingBox(time0, time1, boundingBox))
	{
		boundingBox = AABB(boundingBox.minimum + offset, boundingBox.maximum + offset);
		return true;
	}

	return false;
}