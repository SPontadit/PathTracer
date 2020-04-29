#include "Isotropic.h"

#include "Texture.h"
#include "MathUtility.h"

Isotropic::Isotropic(Texture* albedo)
	: Material(), albedo(albedo)
{
}

Isotropic::~Isotropic()
{
	delete albedo;
}

bool Isotropic::Scatter(Ray const& rayIn, HitRecord const& hitRecord, Vector3& attenuation, Ray& rayScattered) const
{
	rayScattered = Ray(hitRecord.point, RandomInUnitSphere());

	attenuation = albedo->Value(hitRecord.u, hitRecord.v, hitRecord.point);

	return true;
}