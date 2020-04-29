#pragma once

#ifndef __METAL_H_INCLUDED__
#define __METALko_H_INCLUDED__

#include "Material.h"

class Metal : public Material
{
public:
	Metal(Vector3 const& albedo, float fuzz);
	virtual ~Metal() = default;

	Metal(Metal const&) = default;
	Metal(Metal&&) = default;

	Metal& operator=(Metal const&) = default;
	Metal& operator=(Metal&&) = default;

	virtual bool Scatter(Ray const& rayIn, HitRecord const& hitRecord, Vector3& attenuation, Ray& rayScattered) const override;

private:
	Vector3 albedo;
	float fuzz;
};

#endif // __METAL_H_INCLUDED__