#include "CheckerTexture.h"

CheckerTexture::CheckerTexture(Texture* texture0, Texture* texture1)
	: odd(texture0), even(texture1)
{
}

CheckerTexture::~CheckerTexture()
{
	delete odd;
	delete even;
}

Vector3 CheckerTexture::Value(float u, float v, Vector3 const& point) const
{
	float sinus = sin(10.f * point.x()) * sin(10.f * point.y()) * sin(10.f * point.z());

	if (sinus < 0.f)
		return odd->Value(u, v, point);
		
	return even->Value(u, v, point);
}