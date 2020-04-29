#pragma once

#ifndef __PERLIN_H_INCLUDED__
#define __PERLIN_H_INCLUDED__

#include "Vector3.h"

class Perlin
{
public:
	Perlin();
	~Perlin();

	Perlin(Perlin const&) = default;
	Perlin(Perlin&&) = default;

	Perlin& operator=(Perlin const&) = default;
	Perlin& operator=(Perlin&&) = default;
	
	float Noise(Vector3 const& point) const;

	float Turbulence(Vector3 const& point, int depth = 7) const;


private:
	Vector3* randomVector;
	float* randomFloat;
	int* permutationX;
	int* permutationY;
	int* permutationZ;


	Vector3* GenerateVector();
	float* GenerateFloat();
	int* GeneratePermutationTable();
	void Permute(int* point, int size);
};




#endif // __PERLIN_H_INCLUDED__
