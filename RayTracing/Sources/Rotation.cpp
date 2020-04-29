#include "Rotation.h"

#include "MathUtility.h";

RotationY::RotationY(Hitable* hitable, float angle)
	: Hitable(), hitable(hitable)
{
	float radians = DegToRad(angle);

	sinTheta = sin(radians);
	cosTheta = cos(radians);

	hasBox = hitable->BoundingBox(0.f, 1.f, boundingBox);

	Vector3 minimum(FLT_MAX, FLT_MAX, FLT_MAX);
	Vector3 maximum(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				float x = i * boundingBox.maximum.x() + (1 - i) * boundingBox.minimum.x();
				float y = j * boundingBox.maximum.y() + (1 - j) * boundingBox.minimum.y();
				float z = k * boundingBox.maximum.z() + (1 - k) * boundingBox.minimum.z();
			
				float newX = cosTheta * x + sinTheta * z;
				float newZ = -sinTheta * x + cosTheta * z;

				Vector3 tester(newX, y, newZ);

				for (int c = 0; c < 2; c++)
				{
					if (tester[c] > maximum[c])
						maximum[c] = tester[c];

					if (tester[c] < minimum[c])
						minimum[c] = tester[c];
				}
			}
		}
	}

	boundingBox = AABB(minimum, maximum);
}

RotationY::~RotationY()
{
	delete hitable;
}

bool RotationY::Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const
{
	Vector3 origin = ray.origin;
	Vector3 direction = ray.direction;

	origin[0] = cosTheta * ray.origin[0] - sinTheta * origin[2];
	origin[2] = sinTheta * ray.origin[0] + cosTheta * origin[2];

	direction[0] = cosTheta * ray.direction[0] - sinTheta * direction[2];
	direction[2] = sinTheta * ray.direction[0] + cosTheta * direction[2];

	Ray rotatedRay(origin, direction, ray.time);

	if (hitable->Hit(rotatedRay, tMin, tMax, outHitRecord))
	{
		Vector3 point = outHitRecord.point;
		Vector3 normal = outHitRecord.normal;

		point[0] = cosTheta * outHitRecord.point[0] + sinTheta * outHitRecord.point[2];
		point[2] = -sinTheta * outHitRecord.point[0] + cosTheta * outHitRecord.point[2];

		normal[0] = cosTheta * outHitRecord.normal[0] + sinTheta * outHitRecord.normal[2];
		normal[2] = -sinTheta * outHitRecord.normal[0] + cosTheta * outHitRecord.normal[2];

		outHitRecord.point = point;
		outHitRecord.normal = normal;

		return true;
	}

	return false;
}

bool RotationY::BoundingBox(float time0, float time1, AABB& boundingBox) const
{
	boundingBox = this->boundingBox;

	return hasBox;
}
