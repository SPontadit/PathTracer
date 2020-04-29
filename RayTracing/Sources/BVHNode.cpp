#include "BVHNode.h"

#include <cassert>
#include "MathUtility.h"

int BoxXCompare(const void* a, const void* b)
{
	AABB boundingBoxLeft, boundingBoxRight;

	Hitable* hitableA = *(Hitable**)a;
	Hitable* hitableB = *(Hitable**)b;

	if (!hitableA->BoundingBox(0.f, 0.f, boundingBoxLeft) || !hitableB->BoundingBox(0.f, 0.f, boundingBoxRight))
		assert(false);

	if (boundingBoxLeft.minimum.x() - boundingBoxRight.minimum.x() < 0.f)
		return -1;

	return 1;
}

int BoxYCompare(const void* a, const void* b)
{
	AABB boundingBoxLeft, boundingBoxRight;

	Hitable* hitableA = *(Hitable**)a;
	Hitable* hitableB = *(Hitable**)b;

	if (!hitableA->BoundingBox(0.f, 0.f, boundingBoxLeft) || !hitableB->BoundingBox(0.f, 0.f, boundingBoxRight))
		assert(false);

	if (boundingBoxLeft.minimum.y() - boundingBoxRight.minimum.y() < 0.f)
		return -1;

	return 1;
}

int BoxZCompare(const void* a, const void* b)
{
	AABB boundingBoxLeft, boundingBoxRight;

	Hitable* hitableA = *(Hitable**)a;
	Hitable* hitableB = *(Hitable**)b;

	if (!hitableA->BoundingBox(0.f, 0.f, boundingBoxLeft) || !hitableB->BoundingBox(0.f, 0.f, boundingBoxRight))
		assert(false);

	if (boundingBoxLeft.minimum.z() - boundingBoxRight.minimum.z() < 0.f)
		return -1;

	return 1;
}

BVHNode::BVHNode(Hitable** hitables, int size, float time0, float time1)
	: Hitable()
{
	int axis = int(3 * drand48());

	if (axis == 0)
		qsort(hitables, size, sizeof(Hitable*), BoxXCompare);
	else if (axis == 1)
		qsort(hitables, size, sizeof(Hitable*), BoxYCompare);
	else
		qsort(hitables, size, sizeof(Hitable*), BoxZCompare);

	if (size == 1)
	{
		left = right = hitables[0];
	}
	else if (size == 2)
	{
		left = hitables[0];
		right = hitables[1];
	}
	else
	{
		left = new BVHNode(hitables, size / 2, time0, time1);
		right = new BVHNode(hitables + size / 2, size - size / 2, time0, time1);
	}

	AABB boudingBoxLeft, boundingBoxRight;

	if (!left->BoundingBox(time0, time1, boudingBoxLeft) || !right->BoundingBox(time0, time1, boundingBoxRight))
		assert(false);

	boundingBox = AABB::SurroundingBox(boudingBoxLeft, boundingBoxRight);
}

bool BVHNode::Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const
{
	if (boundingBox.Hit(ray, tMin, tMax))
	{
		HitRecord leftHitRecord, rightHitRecord;

		bool hitLeft = left->Hit(ray, tMin, tMax, leftHitRecord);
		bool hitRight = right->Hit(ray, tMin, tMax, rightHitRecord);

		if (hitLeft && hitRight)
		{
			outHitRecord = leftHitRecord.time < rightHitRecord.time ? leftHitRecord : rightHitRecord;
			return true;
		}
		else if (hitLeft)
		{
			outHitRecord = leftHitRecord;
			return true;
		}
		else if (hitRight)
		{
			outHitRecord = rightHitRecord;
			return true;
		}
	}
	
	return false;
}

bool BVHNode::BoundingBox(float time0, float time1, AABB& outBoundingBox) const
{
	outBoundingBox = boundingBox;

	return true;
}
