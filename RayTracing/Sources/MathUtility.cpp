#include "MathUtility.h"

Vector3 RandomInUnitSphere()
{
	Vector3 point;

	do
	{
		point = 2.0f * Vector3(drand48(), drand48(), drand48()) - Vector3(1.f, 1.f, 1.f);
	} while (point.SquarredLength() >= 1.f);

	return point;
}

Vector3 RandomInUnitDisk()
{
	Vector3 point;

	do
	{
		point = 2.f * Vector3(drand48(), drand48(), 0.f) - Vector3(1.f, 1.f, 0.f);
	} while (Dot(point, point) >= 1.f);

	return point;
}


Vector3 Reflect(Vector3 const& incident, Vector3 const& normal)
{
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
	// incident & normal => Unitaire
	// Dot(I, N) = cos(O)
	// I = A + B | R = A - B
	// B = Dot(incident, normal) * normal = magnitude de la projection de I en direction de N
	
	// I = A + cos(O) * N
	// A = I - cos(O) * N

	// R = A - cos(O) * N
	// R = I - cos(O) * N - cos(O) * N
	// R = I - 2 * cos(O) * N

	return incident - 2.0f * Dot(incident, normal) * normal;
}

bool Refract(Vector3 const& incident, Vector3 const& normal, float refractionIndiceRatio, Vector3& outRefracted)
{
	Vector3 unitIncident = GetUnit(incident);
	float IDotN = Dot(unitIncident, normal);
	float discriminant = 1.f - (refractionIndiceRatio * refractionIndiceRatio) * (1.f - IDotN * IDotN);

	if (discriminant > 0.f)
	{
		outRefracted = refractionIndiceRatio * (unitIncident - IDotN * normal) - normal * sqrt(discriminant);
		return true;
	}

	return false;
}

float Schlick(float cosinus, float refractionIndice)
{
	float r0 = (1.f - refractionIndice) / (1.f + refractionIndice);
	r0 *= r0;

	return r0 + (1.f - r0) * pow((1.f - cosinus), 5);
}

float ffmin(float a, float b)
{
	return a < b ? a : b;
}

float ffmax(float a, float b)
{
	return a > b ? a : b;
}

float TrilinearInterpolation(float value[2][2][2], float u, float v, float w)
{
	// Remap interpolation value to smooth value - use Hermite Cubic Spline
	u = u * u * (3.f - 2.f * u);
	v = v * v * (3.f - 2.f * v);
	w = w * w * (3.f - 2.f * w);

	float accumulatiion = 0.f;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				accumulatiion += (i * u + (1 - i) * (1 - u)) *
					(j * v + (1 - j) * (1 - v)) *
					(k * w + (1 - k) * (1 - w)) * value[i][j][k];
			}
		}
	}

	return accumulatiion;
}

float Lerp(float value0, float value1, float time)
{
	return value0 * (1.f - time) + value1 * time;
}

float TrilinearInterpolation(Vector3 value[2][2][2], float u, float v, float w)
{
	// Remap interpolation value to smooth value - use Hermite Cubic Spline
	float uu = u * u * (3.f - 2.f * u);
	float vv = v * v * (3.f - 2.f * v);
	float ww = w * w * (3.f - 2.f * w);

	float accumulation = 0.f;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				Vector3 weight(u - i, v - j, w - k);

				accumulation += (i * uu + (1 - i) * (1 - uu)) *
								 (j * vv + (1 - j) * (1 - vv)) *
								 (k * ww + (1 - k) * (1 - ww)) * Dot(value[i][j][k], weight);
			}
		}
	}

	return accumulation;
}

void GetSphereUV(Vector3 const& point, float& u, float& v)
{
	float phi = atan2(point.z(), point.x());
	float theta = asin(point.y());

	u = 1.f - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
}

float DegToRad(float angle)
{
	return (M_PI / 180.f) * angle;
}