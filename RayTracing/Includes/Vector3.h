#pragma once

#ifndef __VECTOR3_H_INCLUDED__
#define __VECTOR3_H_INCLUDED__

#include <cmath>
#include <iostream>

struct Vector3
{
	Vector3() = default;
	~Vector3() = default;

	Vector3(float x, float y, float z)
	{
		values[0] = x;
		values[1] = y;
		values[2] = z;
	}

	inline float x() const { return values[0]; }
	inline float y() const { return values[1]; }
	inline float z() const { return values[2]; }
	inline float r() const { return values[0]; }
	inline float g() const { return values[1]; }
	inline float b() const { return values[2]; }
	
	inline const Vector3& operator+() const { return *this; }
	inline Vector3 operator-() const { return Vector3(-values[0], -values[1], -values[2]); }
	inline float operator[](int i) const { return values[i]; }
	inline float& operator[](int i) { return values[i]; }

	inline Vector3& operator+=(const Vector3& other);
	inline Vector3& operator-=(const Vector3& other);
	inline Vector3& operator*=(const Vector3& other);
	inline Vector3& operator/=(const Vector3& other);
	inline Vector3& operator*=(const float t);
	inline Vector3& operator/=(const float t);
	
	inline float Length() const { return sqrt(values[0] * values[0] + values[1] * values[1] + values[2] * values[2]); }
	inline float SquarredLength() const { return values[0] * values[0] + values[1] * values[1] + values[2] * values[2]; }
	inline void MakeUnit();
	inline Vector3 GetUnit() const;

	float values[3];
};

inline std::istream& operator>>(std::istream& stream, Vector3& vector)
{
	stream >> vector.values[0] >> vector.values[1] >> vector.values[2];
	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, Vector3 const& vector)
{
	stream << vector.values[0] << " " << vector.values[1] << " " << vector.values[2];
	return stream;
}

inline void Vector3::MakeUnit()
{
	float k = 1.0f / Length();
	values[0] *= k;
	values[1] *= k;
	values[2] *= k;
}



inline Vector3& Vector3::operator+=(Vector3 const& other)
{
	values[0] += other.values[0];
	values[1] += other.values[1];
	values[2] += other.values[2];
	return *this;
}

inline Vector3& Vector3::operator-=(Vector3 const& other)
{
	values[0] -= other.values[0];
	values[1] -= other.values[1];
	values[2] -= other.values[2];
	return *this;
}

inline Vector3& Vector3::operator*=(Vector3 const& other)
{
	values[0] *= other.values[0];
	values[1] *= other.values[1];
	values[2] *= other.values[2];
	return *this;
}

inline Vector3& Vector3::operator/=(Vector3 const& other)
{
	values[0] /= other.values[0];
	values[1] /= other.values[1];
	values[2] /= other.values[2];
	return *this;
}

inline Vector3& Vector3::operator*=(const float t)
{
	values[0] *= t;
	values[1] *= t;
	values[2] *= t;
	return *this;
}

inline Vector3& Vector3::operator/=(const float t)
{
	float k = 1.0f / t;

	values[0] *= k;
	values[1] *= k;
	values[2] *= k;
	return *this;
}


inline Vector3 operator+(Vector3 const& vector1, Vector3 const& vector2)
{
	return Vector3(vector1.values[0] + vector2.values[0], 
				   vector1.values[1] + vector2.values[1],
				   vector1.values[2] + vector2.values[2]);
}

inline Vector3 operator-(Vector3 const& vector1, Vector3 const& vector2)
{
	return Vector3(vector1.values[0] - vector2.values[0], 
				   vector1.values[1] - vector2.values[1],
				   vector1.values[2] - vector2.values[2]);
}

inline Vector3 operator*(Vector3 const& vector1, Vector3 const& vector2)
{
	return Vector3(vector1.values[0] * vector2.values[0], 
				   vector1.values[1] * vector2.values[1],
				   vector1.values[2] * vector2.values[2]);
}

inline Vector3 operator/(Vector3 const& vector1, Vector3 const& vector2)
{
	return Vector3(vector1.values[0] / vector2.values[0], 
				   vector1.values[1] / vector2.values[1],
				   vector1.values[2] / vector2.values[2]);
}

inline Vector3 operator*(float t, Vector3 const& vector)
{
	return Vector3(vector.values[0] * t, vector.values[1] * t, vector.values[2] * t);
}

inline Vector3 operator/(float t, Vector3 const& vector)
{
	return Vector3(vector.values[0] / t, vector.values[1] / t, vector.values[2] / t);
}

inline Vector3 operator*(Vector3 const& vector, float t)
{
	return Vector3(vector.values[0] * t, vector.values[1] * t, vector.values[2] * t);
}

inline Vector3 operator/(Vector3 const& vector, float t)
{
	return Vector3(vector.values[0] / t, vector.values[1] / t, vector.values[2] / t);
}

inline Vector3 GetUnit(Vector3 const& vector)
{
	return vector / vector.Length();
}

inline float Dot(Vector3 const& vector1, Vector3 const& vector2)
{
	return vector1.values[0] * vector2.values[0] +
		   vector1.values[1] * vector2.values[1] +
		   vector1.values[2] * vector2.values[2];
}

inline Vector3 Cross(Vector3 const& vector1, Vector3 const& vector2)
{
	return Vector3( (vector1.values[1] * vector2.values[2] - vector1.values[2]  * vector2.values[1]),
					(-(vector1.values[0] * vector2.values[2] - vector1.values[2] * vector2.values[0])),
					(vector1.values[0] * vector2.values[1] - vector1.values[1] * vector2.values[0]));
}



#endif // __VECTOR3_H_INCLUDED__