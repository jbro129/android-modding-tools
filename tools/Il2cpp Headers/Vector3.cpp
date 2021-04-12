#include <M3D/Vector3.hpp>
#include <M3D/Vector4.hpp>


#include <cmath>
#include <cassert>

namespace M3D
{
	const Vector3 Vector3::FORWARD	= Vector3(0.0f, 0.0f, 1.0f);
	const Vector3 Vector3::BACK		= Vector3(0.0f, 0.0f, -1.0f);
	const Vector3 Vector3::UP		= Vector3(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::DOWN		= Vector3(0.0f, -1.0f, 0.0f);
	const Vector3 Vector3::RIGHT	= Vector3(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::LEFT		= Vector3(-1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::ONE		= Vector3(1.0f, 1.0f, 1.0f);
	const Vector3 Vector3::ZERO		= Vector3(0.0f, 0.0f, 0.0f);

	Vector3::Vector3()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
	{
		// Nothing to do.
	}

	Vector3::Vector3(float x_, float y_, float z_)
	: x(x_)
	, y(y_)
	, z(z_)
	{
		// Nothing to do.
	}

	Vector3::Vector3(const Vector4& v)
	: x(v.x)
	, y(v.y)
	, z(v.z)
	{
		// Nothing to do.
	}

	float operator==(const Vector3& v1, const Vector3& v2)
	{
		const float epsilon = 1e-6;
		return std::abs(v1.x - v2.x) < epsilon && std::abs(v1.y - v2.y) < epsilon
			&& std::abs(v1.z - v2.z) < epsilon;
	}

	float operator!=(const Vector3& v1, const Vector3& v2)
	{
		return !(v1 == v2);
	}

	Vector3 operator+(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	Vector3& operator+=(Vector3& v1, const Vector3& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		v1.z += v2.z;

		return v1;
	}

	Vector3 operator-(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	Vector3& operator-=(Vector3& v1, const Vector3& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		v1.z -= v2.z;

		return v1;
	}

	Vector3 operator-(const Vector3& v)
	{
		return Vector3(-v.x, -v.y, -v.z);
	}

	Vector3 operator*(const Vector3& v, const float s)
	{
		return Vector3(v.x * s, v.y * s, v.z * s);
	}

	Vector3& operator*=(Vector3& v, const float s)
	{
		v.x *= s;
		v.y *= s;
		v.z *= s;

		return v;
	}

	Vector3 operator*(const float s, const Vector3& v)
	{
		return v * s;
	}

	Vector3 operator/(const Vector3& v, const float s)
	{
		assert(s != 0.0f);
		return v * (1.0f / s);
	}

	Vector3& operator/=(Vector3& v, const float s)
	{
		assert(s != 0.0f);
		v.x /= s;
		v.y /= s;
		v.z /= s;

		return v;
	}

	std::ostream& operator <<(std::ostream& out, const Vector3& v)
	{
		out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		return out;
	}

	float Vector3::sqrMagnitude() const
	{
		// Take the dot product of this vector with itself.
		return dot(*this, *this);
	}

	float Vector3::magnitude() const
	{
		return sqrt(sqrMagnitude());
	}

	Vector3 Vector3::normalized() const
	{
		assert(sqrMagnitude() != 0.0f);
		const float invLength = 1.0f / magnitude();
		return *this * invLength;
	}

	void Vector3::normalize()
	{
		assert(sqrMagnitude() != 0.0f);
		const float invLength = 1.0f / magnitude();

		x *= invLength;
		y *= invLength;
		z *= invLength;
	}

	Vector3 scale(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}

	float dot(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	Vector3 cross(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		);
	}

	Vector3 lerp(const Vector3& from, const Vector3& to, float factor)
	{
		return from * (1.0f - factor) + to * factor;
	}

	float angle(const Vector3& from, const Vector3& to)
	{
		const float cosTheta = dot(from, to) / sqrt(from.sqrMagnitude() * to.sqrMagnitude());
		return std::acos(std::fmin(1.0f, cosTheta));
	}

	float sqrDistance(const Vector3& p1, const Vector3& p2)
	{
		return (p1 - p2).sqrMagnitude();
	}

	float distance(const Vector3& p1, const Vector3& p2)
	{
		return (p1 - p2).magnitude();
	}
}
