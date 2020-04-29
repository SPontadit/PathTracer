#pragma once

#ifndef __TRANSLATE_H_INCLUDED__
#define __TRANSLATE_H_INCLUDED__

#include "Hitable.h"

class Translate : public Hitable
{
public:
	Translate(Hitable* hitable, Vector3 const& offset);
	~Translate();

	Translate(Translate const&) = default;
	Translate(Translate&&) = default;

	Translate& operator=(Translate const&) = default;
	Translate& operator=(Translate&&) = default;

	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const override;
	virtual bool BoundingBox(float time0, float time1, AABB& boundingBox) const override;

private:
	Hitable* hitable;
	Vector3 offset;
};

#endif // __TRANSLATE_H_INCLUDED__