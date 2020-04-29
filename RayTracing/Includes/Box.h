#pragma once

#ifndef __BOX_H_INCLUDED__
#define __BOX_H_INCLUDED__

#include "Hitable.h"

class Box : public Hitable
{
public:
	Box(Vector3 const& pointMin, Vector3 const& pointMax, Material* material);
	~Box();

	Box(Box const&) = default;
	Box(Box&&) = default;

	Box& operator=(Box const&) = default;
	Box& operator=(Box&&) = default;

	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const override;
	virtual bool BoundingBox(float time0, float time1, AABB& boundingBox) const override;

private:
	Vector3 pointMin;
	Vector3 pointMax;

	Hitable* planes;
};

#endif // __BOX_H_INCLUDED__