#pragma once

#ifndef __MOVING_SPHERE_H_INCLUDED__
#define __MOVING_SPHERE_H_INCLUDED__

#include "Hitable.h"

class MovingSphere : public Hitable
{
public:
	MovingSphere() = default;
	~MovingSphere();

	MovingSphere(MovingSphere const&) = default;
	MovingSphere(MovingSphere&&) = default;

	MovingSphere& operator=(MovingSphere const&) = default;
	MovingSphere& operator=(MovingSphere&&) = default;

	MovingSphere(Vector3 center0, Vector3 center1, float time0, float time1, float radius, Material* material);

	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const override;
	virtual bool BoundingBox(float time0, float time1, AABB& outBoundingBox) const override;

	Vector3 Center(float time) const;

private:
	Vector3 center0;
	Vector3 center1;
	
	float time0;
	float time1;
	float radius;
	
	Material* material;
};

#endif // __MOVING_SPHERE_H_INCLUDED__