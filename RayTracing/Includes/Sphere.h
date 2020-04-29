#pragma once

#ifndef __SPHERE_H_INCLUDED__
#define __SPHERE_H_INCLUDED__

#include "Hitable.h"

class Sphere : public Hitable
{
public:
	Sphere() = default;
	~Sphere();

	Sphere(Sphere const&) = default;
	Sphere(Sphere&&) = default;

	Sphere& operator=(Sphere const&) = default;
	Sphere& operator=(Sphere&&) = default;

	Sphere(Vector3 center, float radius, Material* material);

	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const override;
	virtual bool BoundingBox(float time0, float time1, AABB& outBoundingBox) const override;

	Vector3 center;
	float radius;
};

#endif // __SPHERE_H_INCLUDED__