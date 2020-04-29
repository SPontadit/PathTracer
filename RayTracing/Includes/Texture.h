#pragma once

#ifndef __TEXTURE_H_INCLUDED__
#define __TEXTURE_H_INCLUDED__

#include "Vector3.h"

class Texture
{
public:
	Texture() = default;
	virtual ~Texture() = default;

	Texture(Texture const&) = default;
	Texture(Texture&&) = default;

	Texture& operator=(Texture const&) = default;
	Texture& operator=(Texture&&) = default;
	
	virtual Vector3 Value(float u, float v, Vector3 const& point) const = 0;
};

#endif // __TEXTURE_H_INCLUDED__