#pragma once

#ifndef __CONSTANT_MEDIUM_H_INCUDED__
#define __CONSTANT_MEDIUM_H_INCUDED__

#include "Hitable.h"

class Texture;
class Material;

class ConstantMedium : public Hitable
{
public:
	ConstantMedium(Hitable* hitable, float density, Texture* albedo);
	~ConstantMedium();

	ConstantMedium(ConstantMedium const&) = default;
	ConstantMedium(ConstantMedium&&) = default;

	ConstantMedium& operator=(ConstantMedium const&) = default;
	ConstantMedium& operator=(ConstantMedium&&) = default;

	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const override;
	virtual bool BoundingBox(float time0, float time1, AABB& boundingBox) const override;

private:
	Hitable* hitable;

	float density;
};

#endif // __CONSTANT_MEDIUM_H_INCUDED__