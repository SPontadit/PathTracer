#pragma once

#ifndef __MATH_UTILITY_H_INCLUDED__
#define __MATH_UTILITY_H_INCLUDED__

#include "Vector3.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define srand48(t) srand(t)
#define drand48() ((double)rand()/RAND_MAX)


Vector3 RandomInUnitSphere();

Vector3 RandomInUnitDisk();

Vector3 Reflect(Vector3 const& incident, Vector3 const& normal);

bool Refract(Vector3 const& incident, Vector3 const& normal, float refractionIndiceRatio, Vector3& outRefracted);

float Schlick(float cosinus, float refractionIndice);

float ffmin(float a, float b);

float ffmax(float a, float b);

float Lerp(float value0, float value1, float time);

float TrilinearInterpolation(float value[2][2][2], float u, float v, float w);

float TrilinearInterpolation(Vector3 value[2][2][2], float u, float v, float w);

void GetSphereUV(Vector3 const& point, float& u, float& v);

float DegToRad(float angle);

#endif // __MATH_UTILITY_H_INCLUDED__