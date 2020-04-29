#pragma once

#ifndef __HITABLE_LIST_H_INCLUDED__
#define __HITABLE_LIST_H_INCLUDED__

#include "Hitable.h"

class HitableList : public Hitable
{
public:
	~HitableList() = default;

	HitableList(HitableList const&) = default;
	HitableList(HitableList&&) = default;

	HitableList& operator=(HitableList const&) = default;
	HitableList& operator=(HitableList&&) = default;

	HitableList(Hitable** hitables, int count);

	virtual bool Hit(Ray const& ray, float tMin, float tMax, HitRecord& outHitRecord) const override;
	virtual bool BoundingBox(float time0, float time1, AABB& boundingBox) const override;

private:
	Hitable** hitables;
	int size;
};

#endif // __HITABLE_LIST_H_INCLUDED__