#include "ConstantMedium.h"

#include "Isotropic.h"
#include "MathUtility.h"

ConstantMedium::ConstantMedium(Hitable* hitable, float density, Texture* albedo)
	: Hitable(), hitable(hitable), density(density)
{
	material = new Isotropic(albedo);
}

ConstantMedium::~ConstantMedium()
{
	delete material;
}

bool ConstantMedium::Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const
{
	bool db = false;

	HitRecord hitRecord1, hitRecord2;

	if (hitable->Hit(ray, -FLT_MAX, FLT_MAX, hitRecord1))
	{
		if (hitable->Hit(ray, hitRecord1.time + 0.0001f, FLT_MAX, hitRecord2))
		{
			hitRecord1.time = hitRecord1.time < tMin ? tMin : hitRecord1.time;
			hitRecord2.time = hitRecord2.time > tMax ? tMax : hitRecord2.time;

			if (hitRecord1.time >= hitRecord2.time)
				return false;

			hitRecord1.time = hitRecord1.time < 0.f ? 0.f : hitRecord1.time;

			float distanceInsideBoundary = (hitRecord2.time - hitRecord1.time) * ray.direction.Length();
			float hitDistance = -(1.f / density) * log(drand48());

			if (hitDistance < distanceInsideBoundary)
			{
				outHitRecord.time = hitRecord1.time + hitDistance / ray.direction.Length();
				outHitRecord.point = ray.PointAtTime(outHitRecord.time);
				outHitRecord.normal = Vector3(1.f, 0.f, 0.f); // arbitraty
				outHitRecord.material = material;

				return true;
			}
		}
	}

	return false;
}

bool ConstantMedium::BoundingBox(float time0, float time1, AABB& boundingBox) const
{
	return hitable->BoundingBox(time0, time1, boundingBox);
}