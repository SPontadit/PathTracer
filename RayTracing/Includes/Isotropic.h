#pragma once

#ifndef __ISOTROPIC_H_INCLUDED__
#define __ISOTROPIC_H_INCLUDED__

#include "Material.h"

class Texture;

class Isotropic : public Material
{
public:
	Isotropic(Texture* albedo);
	~Isotropic();

	Isotropic(Isotropic const&) = default;
	Isotropic(Isotropic&&) = default;

	Isotropic& operator=(Isotropic const&) = default;
	Isotropic& operator=(Isotropic&&) = default;

	virtual bool Scatter(Ray const& rayIn, HitRecord const& hitRecord, Vector3& attenuation, Ray& rayScattered) const override;

private:
	Texture* albedo;
};

#endif // __ISOTROPIC_H_INCLUDED__