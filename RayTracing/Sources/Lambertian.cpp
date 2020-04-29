#include "Lambertian.h"

#include "MathUtility.h"
#include "Texture.h"

Lambertian::Lambertian(Texture* albedo)
	: Material(), albedo(albedo)
{
}

Lambertian::~Lambertian()
{
	delete albedo;
}

bool Lambertian::Scatter(Ray const& rayIn, HitRecord const& hitRecord, Vector3& attenuation, Ray& rayScattered) const
{
	Vector3 target = hitRecord.point + hitRecord.normal + RandomInUnitSphere();

	rayScattered = Ray(hitRecord.point, target - hitRecord.point, rayIn.time);
	attenuation = albedo->Value(hitRecord.u, hitRecord.v, hitRecord.point);
	
	return true;
}