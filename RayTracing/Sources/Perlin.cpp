#include "Perlin.h"

#include "MathUtility.h"

Perlin::Perlin()
{
	randomFloat = GenerateFloat();
	randomVector = GenerateVector();

	permutationX = GeneratePermutationTable();
	permutationY = GeneratePermutationTable();
	permutationZ = GeneratePermutationTable();
}

Perlin::~Perlin()
{
	delete randomFloat;
	delete randomVector;

	delete permutationX;
	delete permutationY;
	delete permutationZ;
}

float Perlin::Noise(Vector3 const& point) const
{
	int i = floor(point.x());
	int j = floor(point.y());
	int k = floor(point.z());

	float u = point.x() - i;
	float v = point.y() - j;
	float w = point.z() - k;


	Vector3 value[2][2][2];

	for (int di = 0; di < 2; di++)
	{
		for (int dj = 0; dj < 2; dj++)
		{
			for (int dk = 0; dk < 2; dk++)
			{
				value[di][dj][dk] = randomVector[permutationX[(i + di) & 255] ^ permutationY[(j + dj) & 255] ^ permutationZ[(k + dk) & 255]];
			}
		}
	}

	return TrilinearInterpolation(value, u, v, w);
}

float Perlin::Turbulence(Vector3 const& point, int depth) const
{
	float accumulation = 0.f;
	Vector3 tmpPoint = point;

	float weight = 1.f;

	for (int i = 0; i < depth; ++i)
	{
		accumulation += weight * Noise(tmpPoint);
		weight *= 0.5f;
		tmpPoint *= 2.0f;
	}

	return fabs(accumulation);
}


Vector3* Perlin::GenerateVector()
{
	Vector3* vectors = new Vector3[256];

	for (int i = 0; i < 256; i++)
	{
		vectors[i] = GetUnit(Vector3(2.f * drand48() - 1.f, 2.f * drand48() - 1.f, 2.f * drand48() - 1.f));
	}

	return vectors;
}

float* Perlin::GenerateFloat()
{
	float* values = new float[256];

	for (int i = 0; i < 256; i++)
	{
		values[i] = drand48();
	}

	return values;
}

void Perlin::Permute(int* point, int size)
{
	for (int i = size - 1; i > 0; i--)
	{
		int target = int(drand48() * (i + 1));
		int temp = point[i];
		point[i] = point[target];
		point[target] = temp;
	}
}

int* Perlin::GeneratePermutationTable()
{
	int* permutationTable = new int[256];

	for (int i = 0; i < 256; i++)
	{
		permutationTable[i] = i;
	}

	Permute(permutationTable, 256);

	return permutationTable;
}