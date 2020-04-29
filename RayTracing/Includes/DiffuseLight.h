#pragma once

#ifndef __DIFFUSE_LIGHT_H_INCLUDED__
#define __DIFFUSE_LIGHT_H_INCLUDED__

#include "Material.h"

class Texture;

class DiffuseLight : public Material
{
public:
	DiffuseLight(Texture* albedo);
	~DiffuseLight();

	DiffuseLight(DiffuseLight const&) = default;
	DiffuseLight(DiffuseLight&&) = default;

	DiffuseLight& operator=(DiffuseLight const&) = default;
	DiffuseLight& operator=(DiffuseLight&&) = default;

	virtual bool Scatter(Ray const& rayIn, HitRecord const& hitRecord, Vector3& attenuation, Ray& rayScattered) const override;
	virtual Vector3 Emitted(float u, float v, Vector3 const& point) const override;

private:
	Texture* emit;
};

#endif // __DIFFUSE_LIGHT_H_INCLUDED__