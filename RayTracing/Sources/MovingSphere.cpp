#include "MovingSphere.h"

MovingSphere::MovingSphere(Vector3 center0, Vector3 center1, float time0, float time1, float radius, Material* material)
	: center0(center0), center1(center1), time0(time0), time1(time1), radius(radius), material(material)
{
}

MovingSphere::~MovingSphere()
{
	delete material;
}

bool MovingSphere::Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const
{
	Vector3 oc = ray.origin - Center(ray.time);
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
			outHitRecord.normal = (outHitRecord.point - Center(ray.time)) / radius;
			outHitRecord.material = material;
			return true;
		}


		temp = (-B + sqrt(discriminant)) / A;
		if (temp < tMax && temp > tMin)
		{
			outHitRecord.time = temp;
			outHitRecord.point = ray.PointAtTime(temp);
			outHitRecord.normal = (outHitRecord.point - Center(ray.time)) / radius;
			outHitRecord.material = material;
			return true;
		}
	}

	return false;
}

bool MovingSphere::BoundingBox(float time0, float time1, AABB& outBoundingBox) const
{
	AABB boundingBox0(center0 - Vector3(radius, radius, radius), center0 + Vector3(radius, radius, radius));
	AABB boundingBox1(center1 - Vector3(radius, radius, radius), center1 + Vector3(radius, radius, radius));

	outBoundingBox = AABB::SurroundingBox(boundingBox0, boundingBox1);
	
	return true;
}

Vector3 MovingSphere::Center(float time) const
{
	return center0 + ((time - time0) / (time1 - time0) * (center1 - center0));
}