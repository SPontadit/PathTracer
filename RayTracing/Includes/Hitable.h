#pragma once

#ifndef __HITABLE_H_INCLUDED__
#define __HITABLE_H_INCLUDED__

#include "Ray.h"
#include "AABB.h"

class Material;

struct HitRecord
{
	float u;
	float v;
	float time;
	Vector3 point;
	Vector3 normal;
	Material* material;
};

class Hitable
{
public:
	Hitable() = default;
	virtual ~Hitable() = default;

	Hitable(Hitable const&) = default;
	Hitable(Hitable&&) = default;

	Hitable& operator=(Hitable const&) = default;
	Hitable& operator=(Hitable&&) = default;

	Hitable(Material* material);
	
	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const = 0;
	virtual bool BoundingBox(float time0, float time1, AABB& boundingBox) const = 0;

	Material* GetMaterial() const;

protected:
	Material* material;
};

#endif // __HITABLE_H_INCLUDED__