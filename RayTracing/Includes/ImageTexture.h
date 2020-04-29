#pragma once

#ifndef __IMAGE_TEXTURE_H_INCLUDED__
#define __IMAGE_TEXTURE_H_INCLUDED__

#include "Texture.h"

class ImageTexture : public Texture
{
public:
	ImageTexture(unsigned char* data, int width, int height);
	~ImageTexture() = default;

	ImageTexture(ImageTexture const&) = default;
	ImageTexture(ImageTexture&&) = default;

	ImageTexture& operator=(ImageTexture const&) = default;
	ImageTexture& operator=(ImageTexture&&) = default;


	virtual Vector3 Value(float u, float v, Vector3 const& point) const override;

private:
	unsigned char* data;
	int width;
	int height;
};

#endif // __IMAGE_TEXTURE_H_INCLUDED__