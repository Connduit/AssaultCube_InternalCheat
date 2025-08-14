#pragma once

#include <math.h>
#include <Windows.h>
#include <string>

constexpr auto PI = 3.145297f;
extern float* matrix;

extern int windowWidth;
extern int windowHeight;

class Vector3
{
public:
	// x,y,z coords should def be private
	float x;
	float y;
	float z;

	Vector3() :
		x(0.0), y(0.0), z(0.0)
	{

	}
	Vector3(const float x, const float y, const float z) :
		x(x), y(y), z(z)
	{

	}

	// TODO: define these outside of the class/header so it looks cleaner?
	inline Vector3 operator+(const Vector3& rhs) const
	{
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	inline Vector3 operator-(const Vector3& rhs) const
	{
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	inline Vector3 operator*(const float& rhs) const
	{
		return Vector3(x * rhs, y * rhs, z * rhs);
	}

	inline Vector3 operator/(const float& rhs) const
	{
		return Vector3(x / rhs, y / rhs, z / rhs);
	}

	inline Vector3& operator+=(const Vector3& rhs)
	{
		return *this = *this + rhs;
	}

	inline Vector3& operator+=(const float& rhs)
	{
		return *this = *this + Vector3(rhs, rhs, rhs);
	}

	inline Vector3& operator-=(const Vector3& rhs)
	{
		return *this = *this - rhs;
	}

	inline Vector3& operator-=(const float& rhs)
	{
		return *this = *this - Vector3(rhs, rhs, rhs);
	}

	inline Vector3& operator*=(const float& rhs)
	{
		return *this = *this * rhs;
	}

	inline Vector3& operator/=(const float& rhs)
	{
		return *this = *this / rhs;
	}

	float Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	Vector3 Normalize() const
	{
		return *this * (1 / Length());
	}

	float Distance(const Vector3& rhs) const
	{
		return (*this - rhs).Length();
	}

	// TODO: should probs make "*this" variable private and just make a getter function for the vector
	Vector3 abs()
	{
		x = fabs(x);
		y = fabs(y);
		z = fabs(z);
		return *this;
	}

	std::string toString();

private:
};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};

//bool WorldToScreen(Vector3 pos, Vector3& screen, float matrix[16], int windowWidth, int windowHeight);
//Vector3 WorldToScreen(Vector3& pos, float matrix[16], int windowWidth, int windowHeight);
//Vector3 WorldToScreen(Vector3& pos);
Vector3 OpenGLWorldToScreen(Vector3& pos, const float matrix[16], int windowWidth, int windowHeight);
Vector3 DirectXWorldToScreen(Vector3& pos, const float matrix[16], int windowWidth, int windowHeight);

Vector3 CalcAngle(Vector3& origin, Vector3& target, bool invertYaw = false, bool invertPitch = false);

Vector3 DegreesToRadians(Vector3& vector);
float DegreesToRadians(float num);
Vector3 RadiansToDegrees(const Vector3& vector);
float RadiansToDegrees(float num);

