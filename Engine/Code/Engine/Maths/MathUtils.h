#pragma once

class Vec3;
class Vec2;
class AABB2;

float Clamp(float value, float min, float max);
float CosDegrees(float degrees);
float SinDegrees(float degrees);
float DotProduct(const Vec3& a, const Vec3& b);
float TanDegrees(float degrees);
float Atan2Degrees(float y, float x);
float RangeMap(float inputValue, float inputBegin, float inputEnd, float outputBegin, float outputEnd);
bool Disc_AABB2Collision(const Vec2& center, const float& radius, AABB2& box);
float Interpolate(const float& start, const float& end, float delta);