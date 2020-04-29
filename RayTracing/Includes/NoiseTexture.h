#pragma once

#ifndef __NOISE_TEXTURE_H_INCLUDED__
#define __NOISE_TEXTURE_H_INCLUDED__

#include "Texture.h"
#include "Perlin.h"

class NoiseTexture : public Texture
{
public:
	NoiseTexture(float scale = 1.f);
	~NoiseTexture() = default;

	NoiseTexture(NoiseTexture const&) = default;
	NoiseTexture(NoiseTexture&&) = default;

	NoiseTexture& operator=(NoiseTexture const&) = default;
	NoiseTexture& operator=(NoiseTexture&&) = default;

	virtual Vector3 Value(float u, float v, Vector3 const& point) const override;

private:
	Perlin noise;
	float scale;
};

#endif // __NOISE_TEXTURE_H_INCLUDED__