#include "XYZRectangle.h"

XYRectangle::XYRectangle(float x0, float x1, float y0, float y1, float k, Material* material)
	: Hitable(material), x0(x0), x1(x1), y0(y0), y1(y1), k(k)
{
}

bool XYRectangle::Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const
{
	float time = (k - ray.origin.z()) / ray.direction.z();

	if (time < tMin || time > tMax)
		return false;

	float x = ray.origin.x() + time * ray.direction.x();
	float y = ray.origin.y() + time * ray.direction.y();
	
	if (x < x0 || x > x1 || y < y0 || y > y1)
		return false;

	outHitRecord.u = (x - x0) / (x1 - x0);
	outHitRecord.v = (y - y0) / (y1 - y0);

	outHitRecord.point = ray.PointAtTime(time);
	outHitRecord.time = time;
	outHitRecord.material = material;
	outHitRecord.normal = Vector3(0.f, 0.f, 1.f);

	return true;
}

bool XYRectangle::BoundingBox(float time0, float time1, AABB& boundingBox) const
{
	boundingBox = AABB(Vector3(x0, y0, k - 0.0001f), Vector3(x1, y1, k + 0.0001f));

	return true;
}


XZRectangle::XZRectangle(float x0, float x1, float z0, float z1, float k, Material* material)
	: Hitable(material), x0(x0), x1(x1), z0(z0), z1(z1), k(k)
{
}

bool XZRectangle::Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const
{
	float time = (k - ray.origin.y()) / ray.direction.y();

	if (time < tMin || time > tMax)
		return false;

	float x = ray.origin.x() + time * ray.direction.x();
	float z = ray.origin.z() + time * ray.direction.z();

	if (x < x0 || x > x1 || z < z0 || z > z1)
		return false;

	outHitRecord.u = (x - x0) / (x1 - x0);
	outHitRecord.v = (z - z0) / (z1 - z0);

	outHitRecord.point = ray.PointAtTime(time);
	outHitRecord.time = time;
	outHitRecord.material = material;
	outHitRecord.normal = Vector3(0.f, 1.f, 0.f);

	return true;
}

bool XZRectangle::BoundingBox(float time0, float time1, AABB& boundingBox) const
{
	boundingBox = AABB(Vector3(x0, k - 0.0001f, z0), Vector3(x1, k + 0.0001f, z1));

	return true;
}


YZRectangle::YZRectangle(float y0, float y1, float z0, float z1, float k, Material* material)
	: Hitable(material), y0(y0), y1(y1), z0(z0), z1(z1), k(k)
{
}

bool YZRectangle::Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const
{
	float time = (k - ray.origin.x()) / ray.direction.x();

	if (time < tMin || time > tMax)
		return false;

	float y = ray.origin.y() + time * ray.direction.y();
	float z = ray.origin.z() + time * ray.direction.z();

	if (y < y0 || y > y1 || z < z0 || z > z1)
		return false;

	outHitRecord.u = (y - y0) / (y1 - y0);
	outHitRecord.v = (z - z0) / (z1 - z0);

	outHitRecord.point = ray.PointAtTime(time);
	outHitRecord.time = time;
	outHitRecord.material = material;
	outHitRecord.normal = Vector3(1.f, 0.f, 0.f);

	return true;
}

bool YZRectangle::BoundingBox(float time0, float time1, AABB& boundingBox) const
{
	boundingBox = AABB(Vector3(k - 0.0001f, y0, z0), Vector3(k + 0.0001f, y1, z1));

	return true;
}