#pragma once

#ifndef __RAY_H_INCLUDED__
#define __RAY_H_INCLUDED__

#include "Vector3.h"

struct Ray
{
	Ray() = default;
	~Ray() = default;

	Ray(Ray const&) = default;
	Ray(Ray&&) = default;

	Ray& operator=(Ray const&) = default;
	Ray& operator=(Ray&&) = default;

	Ray(Vector3 const& origin, Vector3 const& direction, float time = 0.f)
		: origin(origin), direction(direction), time(time)
	{}

	Vector3 PointAtTime(float time) const
	{
		return origin + time * direction;
	}

	Vector3 origin;
	Vector3 direction;
	float time;
};

#endif // __RAY_H_INCLUDED__