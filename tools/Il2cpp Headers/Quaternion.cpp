#include <M3D/Quaternion.hpp>
#include <M3D/Vector3.hpp>

#include <cmath>
#include <cassert>

namespace M3D
{
	const Quaternion Quaternion::IDENTITY = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);

	Quaternion::Quaternion()
	: w(1.0f)
	, x(0.0f)
	, y(0.0f)
	, z(0.0f)
	{
		// Nothing to do.
	}

	Quaternion::Quaternion(float w_, float x_, float y_, float z_)
	: w(w_)
	, x(x_)
	, y(y_)
	, z(z_)
	{
		// Nothing to do.
	}

	Quaternion::Quaternion(const float s, const Vector3& v)
	: w(s)
	, x(v.x)
	, y(v.y)
	, z(v.z)
	{
		// Nothing to do.
	}

	float operator==(const Quaternion& q1, const Quaternion& q2)
	{
		const float epsilon = 1e-6;
		return std::abs(q1.w - q2.w) < epsilon && std::abs(q1.x - q2.x) < epsilon
			&& std::abs(q1.y - q2.y) < epsilon && std::abs(q1.z - q2.z) < epsilon;
	}

	float operator!=(const Quaternion& q1, const Quaternion& q2)
	{
		return !(q1 == q2);
	}

	Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
	{
		return Quaternion(
			lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
			lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x,
			lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w
		);
	}

	Vector3 operator*(const Quaternion& q, const Vector3& v)
	{
		// Quaternion r = q * Quaternion(0.0f, v.x, v.y, v.z) * q.conjugate();
		// return Vector3(r.x, r.y, r.z);

		// This faster method is described:
		// http://molecularmusings.wordpress.com/2013/05/24/a-faster-quaternion-vector-multiplication/
		const Vector3 qv = Vector3(q.x, q.y, q.z);
		const Vector3 t = 2.0f * cross(qv, v);
		return v + q.w * t + cross(qv, t);
	}

	std::ostream& operator <<(std::ostream& out, const Quaternion& q)
	{
		out << q.w << " + " << q.x << "i + " << q.y << "j + " << q.z << "k";
		return out;
	}

	float Quaternion::sqrMagnitude() const
	{
		return w * w + x * x + y * y + z * z;
	}

	float Quaternion::magnitude() const
	{
		return sqrt(sqrMagnitude());
	}

	Quaternion Quaternion::normalized() const
	{
		assert(magnitude() > 0.0f);
		const float invNorm = 1.0f / magnitude();

		return Quaternion(w * invNorm, x * invNorm, y * invNorm, z * invNorm);
	}

	void Quaternion::rotateTowards(const Quaternion& target, float maxRadiansDelta)
	{
		// Relative unit quaternion rotation between this quaternion and the
		// target quaternion.
		const Quaternion relativeRotation = conjugate() * target;

		// Calculate the angle and axis of the relative quaternion rotation.
		assert(std::abs(relativeRotation.w) <= 1.0f);
		const float angle = 2.0f * std::acos(relativeRotation.w);
		const Vector3 axis(relativeRotation.x, relativeRotation.y, relativeRotation.z);

		// Apply a step of the relative rotation.
		if (angle > maxRadiansDelta)
		{
			// If the angle between the two quaternions is greater than the
			// maximum amount we are allowed to rotate by, then rotate by
			// maxRadiansDelta. Note that we need to normalize the axis as the
			// vector part of the relativeRotation quaternion is probably not
			// a unit vector (unless the scalar part is zero).
			const Quaternion delta = Quaternion::angleAxis(maxRadiansDelta, axis.normalized());
			(*this) = delta * (*this);
		}
		else
		{
			// We would overshoot, so just set this quaternion to the target.
			(*this) = target;
		}
	}

	void Quaternion::normalize()
	{
		assert(magnitude() > 0.0f);
		const float invNorm = 1.0f / magnitude();

		w *= invNorm;
		x *= invNorm;
		y *= invNorm;
		z *= invNorm;
	}

	Quaternion Quaternion::angleAxis(const float angle, const Vector3& axis)
	{
		// The axis supplied should be a unit vector. We don't automatically
		// normalize the axis for efficiency.
		assert(std::abs(axis.magnitude() - 1.0f) < 1e-6);

		const float halfAngle = 0.5f * angle;
		return Quaternion(std::cos(halfAngle), axis * std::sin(halfAngle));
	}

	Quaternion Quaternion::euler(const Vector3& eulerAngles)
	{
		const float halfPhi = 0.5f * eulerAngles.x; // Half the roll.
		const float halfTheta = 0.5f * eulerAngles.y; // Half the pitch.
		const float halfPsi = 0.5f * eulerAngles.z; // Half the yaw.

		const float cosHalfPhi = std::cos(halfPhi);
		const float sinHalfPhi = std::sin(halfPhi);
		const float cosHalfTheta = std::cos(halfTheta);
		const float sinHalfTheta = std::sin(halfTheta);
		const float cosHalfPsi = std::cos(halfPsi);
		const float sinHalfPsi = std::sin(halfPsi);

		return Quaternion(
			cosHalfPhi * cosHalfTheta * cosHalfPsi - sinHalfPhi * sinHalfTheta * sinHalfPsi,
			sinHalfPhi * cosHalfTheta * cosHalfPsi + cosHalfPhi * sinHalfTheta * sinHalfPsi,
			cosHalfPhi * sinHalfTheta * cosHalfPsi - sinHalfPhi * cosHalfTheta * sinHalfPsi,
			cosHalfPhi * cosHalfTheta * sinHalfPsi + sinHalfPhi * sinHalfTheta * cosHalfPsi
		);
	}

	Quaternion Quaternion::fromToRotation(const Vector3& fromDirection, const Vector3& toDirection)
	{
		assert(fromDirection.sqrMagnitude() > 0.0f && toDirection.sqrMagnitude() > 0.0f);
		const Vector3 unitFrom = fromDirection.normalized();
		const Vector3 unitTo = toDirection.normalized();
		const float d = dot(unitFrom, unitTo);

		if (d >= 1.0f)
		{
			// In the case where the two vectors are pointing in the same
			// direction, we simply return the identity rotation.
			return Quaternion::IDENTITY;
		}
		else if (d <= -1.0f)
		{
			// If the two vectors are pointing in opposite directions then we
			// need to supply a quaternion corresponding to a rotation of
			// PI-radians about an axis orthogonal to the fromDirection.
			Vector3 axis = cross(unitFrom, Vector3::RIGHT);
			if (axis.sqrMagnitude() < 1e-6)
			{
				// Bad luck. The x-axis and fromDirection are linearly
				// dependent (colinear). We'll take the axis as the vector
				// orthogonal to both the y-axis and fromDirection instead.
				// The y-axis and fromDirection will clearly not be linearly
				// dependent.
				axis = cross(unitFrom, Vector3::UP);
			}

			// Note that we need to normalize the axis as the cross product of
			// two unit vectors is not nececessarily a unit vector.
			return angleAxis(M_PI, axis.normalized());
		}
		else
		{
			// Scalar component.
			const float s = sqrt(unitFrom.sqrMagnitude() * unitTo.sqrMagnitude())
				+ dot(unitFrom, unitTo);

			// Vector component.
			const Vector3 v = cross(unitFrom, unitTo);

			// Return the normalized quaternion rotation.
			return Quaternion(s, v).normalized();
		}
	}

	Quaternion Quaternion::lookRotation(const Vector3& forward)
	{
		assert(forward.sqrMagnitude() > 0.0f);
		return Quaternion::fromToRotation(Vector3::FORWARD, forward);
	}

	Quaternion Quaternion::lookRotation(const Vector3& forward, const Vector3& upwards)
	{
		// Calculate the unit quaternion that rotates Vector3::FORWARD to face
		// in the specified forward direction.
		const Quaternion q1 = Quaternion::lookRotation(forward);

		// We can't preserve the upwards direction if the forward and upwards
		// vectors are linearly dependent (colinear).
		if (cross(forward, upwards).sqrMagnitude() < 1e-6)
		{
			return q1;
		}

		// Determine the upwards direction obtained after applying q1.
		const Vector3 newUp = q1 * Vector3::UP;

		// Calculate the unit quaternion rotation that rotates the newUp
		// direction to look in the specified upward direction.
		const Quaternion q2 = fromToRotation(newUp, upwards);

		// Return the combined rotation so that we first rotate to look in the
		// forward direction and then rotate to align Vector3::UPWARD with the
		// specified upward direction. There is no need to normalize the result
		// as both q1 and q2 are unit quaternions.
		return q2 * q1;
	}

	Quaternion Quaternion::conjugate() const
	{
		return Quaternion(w, -x, -y, -z);
	}

	Quaternion Quaternion::inverse() const
	{
		const float sqr = sqrMagnitude();
		assert(sqr > 0.0f);

		const float invSqr = 1.0f / sqr;
		return Quaternion(w * invSqr, -x * invSqr, -y * invSqr, -z * invSqr);
	}

	float dot(const Quaternion& lhs, const Quaternion& rhs)
	{
		return lhs.w * rhs.w + lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	float angle(const Quaternion& from, const Quaternion& to)
	{
		const Quaternion relativeRotation = from.conjugate() * to;
		assert(std::abs(relativeRotation.w) <= 1.0f);
		return 2.0f * std::acos(relativeRotation.w);
	}
}
