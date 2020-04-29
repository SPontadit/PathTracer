#pragma once

#ifndef __FLIP_NORMALS_H_INCLUDED__
#define __FLIP_NORMALS_H_INCLUDED__

#include "Hitable.h"

class FlipNormals : public Hitable
{
public:
	FlipNormals(Hitable* hitable);
	~FlipNormals();

	FlipNormals(FlipNormals const&) = default;
	FlipNormals(FlipNormals&&) = default;

	FlipNormals& operator=(FlipNormals const&) = default;
	FlipNormals& operator=(FlipNormals&&) = default;

	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const override;
	virtual bool BoundingBox(float time0, float time1, AABB& boundingBox) const override;

private:
	Hitable* hitable;
};

#endif // __FLIP_NORMALS_H_INCLUDED__