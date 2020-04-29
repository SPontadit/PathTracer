#include "Sphere.h"

#include "MathUtility.h"

Sphere::Sphere(Vector3 center, float radius, Material* material)
	: Hitable(material), center(center), radius(radius)
{
}

Sphere::~Sphere()
{
	delete material;
}

bool Sphere::Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const
{
	Vector3 oc = ray.origin - center;
	float A = Dot(ray.direction, ray.direction);
	float B = Dot(ray.direction, oc);
	float C = Dot(oc, oc) - radius * radius;

	float discriminant = B * B - A * C;

	if (discriminant > 0.0f)
	{
		float temp = (-B - sqrt(discriminant)) / A;

		if (temp < tMax && temp > tMin)
		{
			outHitRecord.time = temp;
			outHitRecord.point = ray.PointAtTime(temp);
			outHitRecord.normal = (outHitRecord.point - center) / radius;
			GetSphereUV(outHitRecord.normal, outHitRecord.u, outHitRecord.v);
			outHitRecord.material = material;
			return true;
		}


		temp = (-B + sqrt(discriminant)) / A;
		if (temp < tMax && temp > tMin)
		{
			outHitRecord.time = temp;
			outHitRecord.point = ray.PointAtTime(temp);
			outHitRecord.normal = (outHitRecord.point - center) / radius;
			GetSphereUV(outHitRecord.normal, outHitRecord.u, outHitRecord.v);
			outHitRecord.material = material;
			return true;
		}
	}

	return false;
}

bool Sphere::BoundingBox(float time0, float time1, AABB& outBoundingBox) const
{
	outBoundingBox = AABB(center - Vector3(radius, radius, radius), center + Vector3(radius, radius, radius));

	return true;
}