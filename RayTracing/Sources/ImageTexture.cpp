#include "ImageTexture.h"

ImageTexture::ImageTexture(unsigned char* data, int width, int height)
	: data(data), width(width), height(height)
{
}

Vector3 ImageTexture::Value(float u, float v, Vector3 const& point) const
{
	int i = u * width;
	int j = (1.f - v) * height;

	if (i < 0)
		i = 0;

	if (j < 0)
		j = 0;

	if (i > width - 1)
		i = width - 1;

	if (j > height - 1)
		j = height - 1;

	unsigned char* color = &data[3 * width * j + 3 * i];

	return Vector3(color[0], color[1], color[2]) / 255.f;
}
