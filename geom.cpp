#include <iostream>

#include "geom.h"
#include "constants.h"



// Calculates clip coordinates based on OpenGL's model-view-projection matrix and converts them to screen space
bool OpenGLWorldToScreen(Vector3 pos, Vector3& screen, const float matrix[16], int windowWidth, int windowHeight)
{
	Vector4 clipCoords;

	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f) {
		return false;
	}

	Vector3 NDC(clipCoords.x / clipCoords.w, clipCoords.y / clipCoords.w, clipCoords.z / clipCoords.w);

	screen.x = (windowWidth / 2.0f) * (NDC.x + 1.0f);
	screen.y = (windowHeight / 2.0f) * (1.0f - NDC.y); // Y is inverted in screen space

	return true;
}

// Similar function for DirectX with column-major matrices
bool DirectXWorldToScreen(Vector3 pos, Vector3& screen, const float matrix[16], int windowWidth, int windowHeight)
{
	Vector4 clipCoords;

	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
	clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
	clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
	clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

	if (clipCoords.w < 0.1f) {
		return false;
	}

	Vector3 NDC(clipCoords.x / clipCoords.w, clipCoords.y / clipCoords.w, clipCoords.z / clipCoords.w);

	screen.x = (windowWidth / 2.0f) * (NDC.x + 1.0f);
	screen.y = (windowHeight / 2.0f) * (1.0f - NDC.y);

	return true;
}

// Wrapper function for OpenGL, assuming the user only calls this for OpenGL purposes
Vector3 OpenGLWorldToScreen(Vector3& pos, const float matrix[16], int windowWidth, int windowHeight)
{
	Vector3 screen;

	if (OpenGLWorldToScreen(pos, screen, matrix, windowWidth, windowHeight))
		return screen;

	return Vector3(0.0f, 0.0f, 0.0f); // Return a default vector if not visible
}

Vector3 DirectXWorldToScreen(Vector3& pos, const float matrix[16], int windowWidth, int windowHeight)
{
	Vector3 screen;
	if (DirectXWorldToScreen(pos, screen, matrix, windowWidth, windowHeight))
		return screen;
	return Vector3(0.0f, 0.0f, 0.0f); // Return a default vector if not visible
}

Vector3 CalcAngle(Vector3& origin, Vector3& target, bool invertYaw, bool invertPitch)
{
	Vector3 results = Vector3();
	Vector3 delta = target - origin;

	float distance = origin.Distance(target);
	if (distance == 0.0f)
	{
		return results;
	}

	float yawSign = invertYaw ? -1.0f : 1.0f;
	float pitchSign = invertPitch ? -1.0f : 1.0f;

	results.x = yawSign * RadiansToDegrees(atan2f(delta.y, delta.x));
	results.y = pitchSign * RadiansToDegrees(asinf(delta.z / distance));

	return results;

}

Vector3 DegreesToRadians(Vector3 vector)
{
	return Vector3(DegreesToRadians(vector.x), DegreesToRadians(vector.y), DegreesToRadians(vector.z));
}

float DegreesToRadians(float num)
{
	return num / 180.0f * PI;
}

Vector3 RadiansToDegrees(const Vector3& vector)
{
	return Vector3(vector.x * 180.f / PI, vector.y * 180.f / PI, vector.z * 180.f / PI);
	//return Vector3(vector.x / PI * 180.0f, vector.y / PI * 180.0f, vector.z / PI * 180.0f);
}

float RadiansToDegrees(float num)
{
	return num * 180.0f / PI;
	//return num / PI * 180.0f;
}

std::string Vector3::toString()
{
	return std::string();
}
