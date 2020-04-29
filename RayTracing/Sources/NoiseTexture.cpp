#include "NoiseTexture.h"

NoiseTexture::NoiseTexture(float scale)
	: scale(scale)
{
}

Vector3 NoiseTexture::Value(float u, float v, Vector3 const& point) const
{
	return Vector3(1.f, 1.f, 1.f) * 0.5f * (1.f + sin(scale * point.x() + 5.f * noise.Turbulence(scale * point)));
	return Vector3(1.f, 1.f, 1.f) * noise.Turbulence(point * scale);
	return Vector3(1.f, 1.f, 1.f) * 0.5f * (1.f + noise.Noise(point * scale));
}