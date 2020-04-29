#pragma once

#ifndef __ROTATION_H_INCLUDED__
#define __ROTATION_H_INCLUDED__

#include "Hitable.h"

class RotationY : public Hitable
{
public:
	RotationY(Hitable* hitable, float angle);
	~RotationY();

	RotationY(RotationY const&) = default;
	RotationY(RotationY&&) = default;

	RotationY& operator=(RotationY const&) = default;
	RotationY& operator=(RotationY&&) = default;

	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const override;
	virtual bool BoundingBox(float time0, float time1, AABB& boundingBox) const override;

private:
	Hitable* hitable;
	float sinTheta;
	float cosTheta;

	bool hasBox;
	AABB boundingBox;
};

#endif // __ROTATION_H_INCLUDED__