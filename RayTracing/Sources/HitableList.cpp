#include "HitableList.h"

HitableList::HitableList(Hitable** hitables, int size)
	: hitables(hitables), size(size)
{
}

bool HitableList::Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const
{
	HitRecord record;
	bool hasHit = false;
	double closest = tMax;

	for (int i = 0; i < size; i++)
	{
		if (hitables[i]->Hit(ray, tMin, closest, record))
		{
			hasHit = true;
			closest = record.time;
			outHitRecord = record;
		}
	}

	return hasHit;
}

bool HitableList::BoundingBox(float time0, float time1, AABB& boundingBox) const
{
	if (size < 1)
		return false;

	AABB tempBox;

	bool firstElement = hitables[0]->BoundingBox(time0, time1, tempBox);

	if (!firstElement)
		return false;

	boundingBox = tempBox;

	for (int i = 1; i < size; i++)
	{
		if (hitables[i]->BoundingBox(time0, time1, tempBox))
		{
			boundingBox = AABB::SurroundingBox(boundingBox, tempBox);
		}
		else
		{
			return false;
		}
	}

	return true;
}