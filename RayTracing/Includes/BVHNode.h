#pragma once

#ifndef __BVH_NODE_H_INCLUDED__
#define __BVH_NODE_H_INCLUDED__

#include "Hitable.h"
#include "AABB.h"

class BVHNode : public Hitable
{
public:
	BVHNode() = default;
	~BVHNode() = default;

	BVHNode(BVHNode const&) = default;
	BVHNode(BVHNode&&) = default;

	BVHNode& operator=(BVHNode const&) = default;
	BVHNode& operator=(BVHNode&&) = default;

	BVHNode(Hitable** hitables, int size, float time0, float time1);

	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const override;
	virtual bool BoundingBox(float time0, float time1, AABB& outBoundingBox) const override;

private:
	Hitable* left;
	Hitable* right;

	AABB boundingBox;
};

#endif // __BVH_NODE_H_INCLUDED__