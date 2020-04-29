#include "ConstantTexture.h"

ConstantTexture::ConstantTexture(Vector3 color)
	: Texture(), color(color)
{
}

Vector3 ConstantTexture::Value(float u, float v, Vector3 const& point) const
{
	return color;
}