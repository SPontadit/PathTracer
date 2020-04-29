#include "Box.h"

#include "XYZRectangle.h"
#include "FlipNormals.h"
#include "HitableList.h"

Box::Box(Vector3 const& pointMin, Vector3 const& pointMax, Material* material)
	: Hitable(), pointMin(pointMin), pointMax(pointMax)
{
	Hitable** list = new Hitable*[6];

	list[0] = new XYRectangle(pointMin.x(), pointMax.x(), pointMin.y(), pointMax.y(), pointMax.z(), material);
	list[1] = new FlipNormals(new XYRectangle(pointMin.x(), pointMax.x(), pointMin.y(), pointMax.y(), pointMin.z(), material));
	
	list[2] = new XZRectangle(pointMin.x(), pointMax.x(), pointMin.z(), pointMax.z(), pointMax.y(), material);
	list[3] = new FlipNormals(new XZRectangle(pointMin.x(), pointMax.x(), pointMin.y(), pointMax.y(), pointMin.y(), material));
	
	list[4] = new YZRectangle(pointMin.y(), pointMax.y(), pointMin.z(), pointMax.z(), pointMax.x(), material);
	list[5] = new FlipNormals(new YZRectangle(pointMin.y(), pointMax.y(), pointMin.z(), pointMax.z(), pointMin.x(), material));

	planes = new HitableList(list, 6);
}

Box::~Box()
{
	delete planes;
}

bool Box::Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const
{
	return planes->Hit(ray, tMin, tMax, outHitRecord);
}

bool Box::BoundingBox(float time0, float time1, AABB& boundingBox) const
{
	boundingBox = AABB(pointMin, pointMax);
	
	return true;
}