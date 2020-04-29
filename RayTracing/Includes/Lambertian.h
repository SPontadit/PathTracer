#pragma once

#ifndef __LAMBERTIAN_H_INCLUDED__
#define __LAMBERTIAN_H_INCLUDED__

#include "Material.h"

class Texture;

class Lambertian : public Material
{
public:
	Lambertian(Texture* albedo);
	~Lambertian();

	Lambertian(Lambertian const&) = default;
	Lambertian(Lambertian&&) = default;

	Lambertian& operator=(Lambertian const&) = default;
	Lambertian& operator=(Lambertian&&) = default;

	virtual bool Scatter(Ray const& rayIn, HitRecord const& hitRecord, Vector3& attenuation, Ray& rayScattered) const override;

private:
	Texture* albedo;
};

#endif // __LAMBERTIAN_H_INCLUDED__