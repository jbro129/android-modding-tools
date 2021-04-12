#include <M3D/Vector2.hpp>

#include <cmath>
#include <cassert>

namespace M3D
{
	const Vector2 Vector2::UP		= Vector2(0.0f, 1.0f);
	const Vector2 Vector2::DOWN		= Vector2(0.0f, -1.0f);
	const Vector2 Vector2::RIGHT	= Vector2(1.0f, 0.0f);
	const Vector2 Vector2::LEFT		= Vector2(-1.0f, 0.0f);
	const Vector2 Vector2::ONE		= Vector2(1.0f, 1.0f);
	const Vector2 Vector2::ZERO		= Vector2(0.0f, 0.0f);

	Vector2::Vector2()
	: x(0.0f)
	, y(0.0f)
	{
		// Nothing to do.
	}

	Vector2::Vector2(float x_, float y_)
	: x(x_)
	, y(y_)
	{
		// Nothing to do.
	}

	float operator==(const Vector2& v1, const Vector2& v2)
	{
		const float epsilon = 1e-6;
		return std::abs(v1.x - v2.x) < epsilon && std::abs(v1.y - v2.y) < epsilon;
	}

	float operator!=(const Vector2& v1, const Vector2& v2)
	{
		return !(v1 == v2);
	}

	Vector2 operator+(const Vector2& v1, const Vector2& v2)
	{
		return Vector2(v1.x + v2.x, v1.y + v2.y);
	}

	Vector2 operator-(const Vector2& v1, const Vector2& v2)
	{
		return Vector2(v1.x - v2.x, v1.y - v2.y);
	}

	Vector2 operator-(const Vector2& v)
	{
		return Vector2(-v.x, -v.y);
	}

	Vector2 operator*(const Vector2& v, const float s)
	{
		return Vector2(v.x * s, v.y * s);
	}

	Vector2 operator*(const float s, const Vector2& v)
	{
		return v * s;
	}

	Vector2 operator/(const Vector2& v, const float s)
	{
		assert(s != 0.0f);
		return v * (1.0f / s);
	}

	std::ostream& operator <<(std::ostream& out, const Vector2& v)
	{
		out << "(" << v.x << ", " << v.y << ")";
		return out;
	}

	float Vector2::sqrMagnitude() const
	{
		// Take the dot product of this vector with itself.
		return dot(*this, *this);
	}

	float Vector2::magnitude() const
	{
		return sqrt(sqrMagnitude());
	}

	Vector2 Vector2::normalized() const
	{
		assert(sqrMagnitude() != 0.0f);
		const float invLength = 1.0f / magnitude();
		return *this * invLength;
	}

	void Vector2::normalize()
	{
		assert(sqrMagnitude() != 0.0f);
		const float invLength = 1.0f / magnitude();

		x *= invLength;
		y *= invLength;
	}

	Vector2 scale(const Vector2& v1, const Vector2& v2)
	{
		return Vector2(v1.x * v2.x, v1.y * v2.y);
	}

	float dot(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	float angle(const Vector2& from, const Vector2& to)
	{
		const float cosTheta = dot(from, to) / sqrt(from.sqrMagnitude() * to.sqrMagnitude());
		return std::acos(std::fmin(1.0f, cosTheta));
	}

	float sqrDistance(const Vector2& p1, const Vector2& p2)
	{
		return (p1 - p2).sqrMagnitude();
	}

	float distance(const Vector2& p1, const Vector2& p2)
	{
		return (p1 - p2).magnitude();
	}
}
