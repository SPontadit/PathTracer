#include "Dielectric.h"

#include "MathUtility.h"

Dielectric::Dielectric(float refractionIndice)
	: Material(), refractionIndice(refractionIndice)
{
}

bool Dielectric::Scatter(Ray const& rayIn, HitRecord const& hitRecord, Vector3& attenuation, Ray& rayScattered) const
{
	Vector3 outwardNormal;
	float refractionIndiceRatio;

	Vector3 reflected = Reflect(rayIn.direction, hitRecord.normal);
	Vector3 refracted;

	float reflectProbability;
	float cosinus;

	attenuation = Vector3(1.f, 1.f, 1.f);

	if (Dot(rayIn.direction, hitRecord.normal) > 0.f) // Incident ray is inside the medium
	{
		outwardNormal = -hitRecord.normal;
		refractionIndiceRatio = refractionIndice;
		cosinus = Dot(rayIn.direction, hitRecord.normal) / rayIn.direction.Length();
		cosinus = sqrt(1.f - refractionIndice * refractionIndice * (1.f - cosinus * cosinus));
	}
	else
	{
		outwardNormal = hitRecord.normal;
		refractionIndiceRatio = 1.f / refractionIndice;
		cosinus = -Dot(rayIn.direction, hitRecord.normal) / rayIn.direction.Length();
	}

	if (Refract(rayIn.direction, outwardNormal, refractionIndiceRatio, refracted))
	{
		reflectProbability = Schlick(cosinus, refractionIndice);
	}
	else
	{
		reflectProbability = 1.f;
	}

	if (drand48() < reflectProbability)
	{
		rayScattered = Ray(hitRecord.point, reflected, rayIn.time);
	}
	else
	{
		rayScattered = Ray(hitRecord.point, refracted, rayIn.time);
	}

	return true;
}