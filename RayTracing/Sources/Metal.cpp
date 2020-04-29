#include "Metal.h"

#include "MathUtility.h"

Metal::Metal(Vector3 const& albedo, float fuzz)
	: Material(), albedo(albedo)
{
	this->fuzz = fuzz > 1.0f ? 1.0f : fuzz;
}

bool Metal::Scatter(Ray const& rayIn, HitRecord const& hitRecord, Vector3& attenuation, Ray& rayScattered) const
{
	Vector3 reflected = Reflect(GetUnit(rayIn.direction), hitRecord.normal);
	rayScattered = Ray(hitRecord.point, reflected + fuzz * RandomInUnitSphere(), rayIn.time);
	attenuation = albedo;

	return (Dot(rayScattered.direction, hitRecord.normal) > 0.0f);
}
