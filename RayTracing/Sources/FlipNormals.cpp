#include "FlipNormals.h"

FlipNormals::FlipNormals(Hitable* hitable)
	: Hitable(), hitable(hitable)
{
}

FlipNormals::~FlipNormals()
{
	delete hitable;
}

bool FlipNormals::Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const
{
	if (hitable->Hit(ray, tMin, tMax, outHitRecord))
	{
		outHitRecord.normal = -outHitRecord.normal;
		return true;
	}

	return false;
}

bool FlipNormals::BoundingBox(float time0, float time1, AABB& boundingBox) const
{
	return hitable->BoundingBox(time0, time1, boundingBox);
}