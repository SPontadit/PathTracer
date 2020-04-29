#pragma once

#ifndef __CONSTANT_TEXTURE_H_INCLUDED__
#define __CONSTANT_TEXTURE_H_INCLUDED__

#include "Texture.h"

class ConstantTexture : public Texture
{
public:
	ConstantTexture() = default;
	~ConstantTexture() = default;

	ConstantTexture(ConstantTexture const&) = default;
	ConstantTexture(ConstantTexture&&) = default;

	ConstantTexture& operator=(ConstantTexture const&) = default;
	ConstantTexture& operator=(ConstantTexture&&) = default;

	ConstantTexture(Vector3 color);

	virtual Vector3 Value(float u, float v, Vector3 const& point) const override;

private:
	Vector3 color;
};

#endif // __CONSTANT_TEXTURE_H_INCLUDED__