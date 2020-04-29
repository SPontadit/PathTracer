#include "DiffuseLight.h"

#include "Texture.h"

DiffuseLight::DiffuseLight(Texture* albedo)
	: Material(), emit(albedo)
{
}

DiffuseLight::~DiffuseLight()
{
	delete emit;
}

bool DiffuseLight::Scatter(Ray const& rayIn, HitRecord const& hitRecord, Vector3& attenuation, Ray& rayScattered) const
{
	return false;
}

Vector3 DiffuseLight::Emitted(float u, float v, Vector3 const& point) const
{
	return emit->Value(u, v, point);
}