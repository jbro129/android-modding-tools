#include <M3D/Vector4.hpp>

#include <cmath>
#include <cassert>

namespace M3D
{
	const Vector4 Vector4::FORWARD	= Vector4(0.0f, 0.0f, 1.0f, 0.0f);
	const Vector4 Vector4::BACK		= Vector4(0.0f, 0.0f, -1.0f, 0.0f);
	const Vector4 Vector4::UP		= Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	const Vector4 Vector4::DOWN		= Vector4(0.0f, -1.0f, 0.0f, 0.0f);
	const Vector4 Vector4::RIGHT	= Vector4(1.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::LEFT		= Vector4(-1.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::ONE		= Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	const Vector4 Vector4::ZERO		= Vector4(0.0f, 0.0f, 0.0f, 0.0f);

	Vector4::Vector4()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
	, w(0.0f)
	{
		// Nothing to do.
	}

	Vector4::Vector4(float x_, float y_, float z_, float w_)
	: x(x_)
	, y(y_)
	, z(z_)
	, w(w_)
	{
		// Nothing to do.
	}

	Vector4::Vector4(const Vector3& v)
	: x(v.x)
	, y(v.y)
	, z(v.z)
	, w(0.0f)
	{
		// Nothing to do.
	}

	Vector4::Vector4(const Vector3& v, float w_)
	: x(v.x)
	, y(v.y)
	, z(v.z)
	, w(w_)
	{
		// Nothing to do.
	}

	float operator==(const Vector4& v1, const Vector4& v2)
	{
		const float epsilon = 1e-6;
		return std::abs(v1.x - v2.x) < epsilon &&
			std::abs(v1.y - v2.y) < epsilon &&
			std::abs(v1.z - v2.z) < epsilon &&
			std::abs(v1.w - v2.w) < epsilon;
	}

	float operator!=(const Vector4& v1, const Vector4& v2)
	{
		return !(v1 == v2);
	}

	Vector4 operator+(const Vector4& v1, const Vector4& v2)
	{
		return Vector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
	}

	Vector4 operator-(const Vector4& v1, const Vector4& v2)
	{
		return Vector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
	}

	Vector4 operator-(const Vector4& v)
	{
		return Vector4(-v.x, -v.y, -v.z, -v.w);
	}

	Vector4 operator*(const Vector4& v, const float s)
	{
		return Vector4(v.x * s, v.y * s, v.z * s, v.w * s);
	}

	Vector4 operator*(const float s, const Vector4& v)
	{
		return v * s;
	}

	Vector4 operator/(const Vector4& v, const float s)
	{
		assert(s != 0.0f);
		return v * (1.0f / s);
	}

	std::ostream& operator <<(std::ostream& out, const Vector4& v)
	{
		out << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
		return out;
	}

	float Vector4::sqrMagnitude() const
	{
		// Take the dot product of this vector with itself.
		return dot(*this, *this);
	}

	float Vector4::magnitude() const
	{
		return sqrt(sqrMagnitude());
	}

	Vector4 Vector4::normalized() const
	{
		assert(sqrMagnitude() != 0.0f);
		const float invLength = 1.0f / magnitude();
		return (*this) * invLength;
	}

	void Vector4::normalize()
	{
		assert(sqrMagnitude() != 0.0f);
		const float invLength = 1.0f / magnitude();

		x *= invLength;
		y *= invLength;
		z *= invLength;
		w *= invLength;
	}

	Vector4 scale(const Vector4& v1, const Vector4& v2)
	{
		return Vector4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
	}

	float dot(const Vector4& lhs, const Vector4& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
	}

	float sqrDistance(const Vector4& p1, const Vector4& p2)
	{
		return (p1 - p2).sqrMagnitude();
	}

	float distance(const Vector4& p1, const Vector4& p2)
	{
		return (p1 - p2).magnitude();
	}
}
