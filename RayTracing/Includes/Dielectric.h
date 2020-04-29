#pragma once

#ifndef __DIELECTRIC_H_INCLUDE__
#define __DIELECTRIC_H_INCLUDE__

#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(float refractionIndice);
	virtual ~Dielectric() = default;

	Dielectric(Dielectric const&) = default;
	Dielectric(Dielectric&&) = default;

	Dielectric& operator=(Dielectric const&) = default;
	Dielectric& operator=(Dielectric&&) = default;

	virtual bool Scatter(Ray const& rayIn, HitRecord const& hitRecord, Vector3& attenuation, Ray& rayScattered) const override;

private:
	float refractionIndice;
};

#endif // __DIELECTRIC_H_INCLUDE__