#pragma once

#ifndef __XY_RECTANGLE_H_INCLUDED__
#define __XY_RECTANGLE_H_INCLUDED__

#include "Hitable.h"

class XYRectangle : public Hitable
{
public:
	XYRectangle() = default;
	~XYRectangle() = default;

	XYRectangle(XYRectangle const&) = default;
	XYRectangle(XYRectangle&&) = default;

	XYRectangle& operator=(XYRectangle const&) = default;
	XYRectangle& operator=(XYRectangle&&) = default;

	XYRectangle(float x0, float x1, float y0, float y1, float k, Material* material);

	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const override;
	virtual bool BoundingBox(float time0, float time1, AABB& boundingBox) const override;

private:
	float x0;
	float x1;
	float y0;
	float y1;
	float k;
};

class XZRectangle : public Hitable
{
public:
	XZRectangle() = default;
	~XZRectangle() = default;

	XZRectangle(XZRectangle const&) = default;
	XZRectangle(XZRectangle&&) = default;

	XZRectangle& operator=(XZRectangle const&) = default;
	XZRectangle& operator=(XZRectangle&&) = default;

	XZRectangle(float x0, float x1, float z0, float z1, float k, Material* material);

	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const override;
	virtual bool BoundingBox(float time0, float time1, AABB& boundingBox) const override;

private:
	float x0;
	float x1;
	float z0;
	float z1;
	float k;
};

class YZRectangle : public Hitable
{
public:
	YZRectangle() = default;
	~YZRectangle() = default;

	YZRectangle(YZRectangle const&) = default;
	YZRectangle(YZRectangle&&) = default;

	YZRectangle& operator=(YZRectangle const&) = default;
	YZRectangle& operator=(YZRectangle&&) = default;

	YZRectangle(float y0, float y1, float z0, float z1, float k, Material* material);

	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const override;
	virtual bool BoundingBox(float time0, float time1, AABB& boundingBox) const override;

private:
	float y0;
	float y1;
	float z0;
	float z1;
	float k;
};

#endif // __XYZ_RECTANGLE_H_INCLUDED__