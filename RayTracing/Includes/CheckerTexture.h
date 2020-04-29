#pragma once

#ifndef __CHECKER_TEXTURE_H_INCLUDED__
#define __CHECKER_TEXTURE_H_INCLUDED__

#include "Texture.h"

class CheckerTexture : public Texture
{
public:
	CheckerTexture() = default;
	~CheckerTexture();

	CheckerTexture(CheckerTexture const&) = default;
	CheckerTexture(CheckerTexture&&) = default;

	CheckerTexture& operator=(CheckerTexture const&) = default;
	CheckerTexture& operator=(CheckerTexture&&) = default;

	CheckerTexture(Texture* texture0, Texture* texture1);
	virtual Vector3 Value(float u, float v, Vector3 const& point) const override;

private:
	Texture* odd;
	Texture* even;
};

#endif // __CHECKER_TEXTURE_H_INCLUDED__