#pragma once

#ifndef __AABB_H_INCLUDED__
#define __AABB_H_INCLUDED__

#include "Ray.h"

class AABB
{
public:
	AABB() = default;
	~AABB() = default;

	AABB(AABB const&) = default;
	AABB(AABB&&) = default;

	AABB& operator=(AABB const&) = default;
	AABB& operator=(AABB&&) = default;

	AABB(Vector3 const& minimum, Vector3 const& maximum);

	bool Hit(Ray const& ray, float tMin, float tMax) const;

	static AABB SurroundingBox(AABB const& box0, AABB const& box1);

	Vector3 minimum;
	Vector3 maximum;
};

#endif // __AABB_H_INCLUDED__
