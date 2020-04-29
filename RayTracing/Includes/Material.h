#pragma once

#ifndef __MATERIAL_H_INCLUDED__
#define __MATERIAL_H_INCLUDED__

#include "Ray.h"
#include "Hitable.h"

class Material
{
public:
	Material() = default;
	virtual ~Material() = default;

	Material(Material const&) = default;
	Material(Material&&) = default;

	Material& operator=(Material const&) = default;
	Material& operator=(Material&&) = default;

	virtual bool Scatter(Ray const& rayIn, HitRecord const& hitRecord, Vector3& attenuation, Ray& rayScattered) const = 0;

	virtual Vector3 Emitted(float u, float v, Vector3 const& point) const
	{
		return Vector3(0.f, 0.f, 0.f);
	}
};


#endif // __MATERIAL_H_INCLUDED__