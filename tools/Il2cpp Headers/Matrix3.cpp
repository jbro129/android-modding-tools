#include <M3D/Matrix3.hpp>

#include <cmath>
#include <cassert>
#include <cstring>

namespace M3D
{
	const Matrix3 Matrix3::IDENTITY = Matrix3();
	const Matrix3 Matrix3::ZERO = Matrix3({0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f});

	Matrix3::Matrix3()
	: m{1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}
	{
		// Nothing to do.
	}

	Matrix3::Matrix3(const float arr[9])
	{
		std::memcpy(m, arr, 9 * sizeof(float));
	}

	Matrix3::Matrix3(float entry00, float entry01, float entry02,
		float entry10, float entry11, float entry12,
		float entry20, float entry21, float entry22)
	: m{entry00, entry01, entry02, entry10, entry11, entry12, entry20, entry21, entry22}
	{
		// Nothing to do.
	}

	float Matrix3::operator[](std::size_t index) const
	{
		assert(index < 9);
		return m[index];
	}

	bool operator==(const Matrix3& A, const Matrix3& B)
	{
		const float epsilon = 1e-6;
		for (std::size_t i = 0; i < 9; ++i)
		{
			if (std::abs(A[i] - B[i]) > epsilon) return false;
		}

		return true;
	}

	bool operator!=(const Matrix3& A, const Matrix3& B)
	{
		return !(A == B);
	}

	Matrix3 operator+(const Matrix3& A, const Matrix3& B)
	{
		return Matrix3(
			A[0] + B[0], A[1] + B[1], A[2] + B[2],
			A[3] + B[3], A[4] + B[4], A[5] + B[5],
			A[6] + B[6], A[7] + B[7], A[8] + B[8]
		);
	}

	Matrix3 operator-(const Matrix3& lhs, const Matrix3& rhs)
	{
		return Matrix3(
			lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2],
			lhs[3] - rhs[3], lhs[4] - rhs[4], lhs[5] - rhs[5],
			lhs[6] - rhs[6], lhs[7] - rhs[7], lhs[8] - rhs[8]
		);
	}

	Matrix3 operator-(const Matrix3& A)
	{
		return Matrix3(
			-A[0], -A[1], -A[2],
			-A[3], -A[4], -A[5],
			-A[6], -A[7], -A[8]
		);
	}

	Matrix3 operator*(const Matrix3& A, const float s)
	{
		return Matrix3(
			A[0] * s, A[1] * s, A[2] * s,
			A[3] * s, A[4] * s, A[5] * s,
			A[6] * s, A[7] * s, A[8] * s
		);
	}

	Matrix3 operator*(const float s, const Matrix3& A)
	{
		return A * s;
	}

	Vector3 operator*(const Matrix3& lhs, const Vector3& rhs)
	{
		return Vector3(
			lhs[0] * rhs.x + lhs[1] * rhs.y + lhs[2] * rhs.z,
			lhs[3] * rhs.x + lhs[4] * rhs.y + lhs[5] * rhs.z,
			lhs[6] * rhs.x + lhs[7] * rhs.y + lhs[8] * rhs.z
		);
	}

	Vector3 operator*(const Vector3& lhs, const Matrix3& rhs)
	{
		return Vector3(
			lhs.x * rhs[0] + lhs.y * rhs[3] + lhs.z * rhs[6],
			lhs.x * rhs[1] + lhs.y * rhs[4] + lhs.z * rhs[7],
			lhs.x * rhs[2] + lhs.y * rhs[5] + lhs.z * rhs[8]
		);
	}

	Matrix3 operator*(const Matrix3& lhs, const Matrix3& rhs)
	{
		return Matrix3(
			lhs[0] * rhs[0] + lhs[1] * rhs[3] + lhs[2] * rhs[6],
			lhs[0] * rhs[1] + lhs[1] * rhs[4] + lhs[2] * rhs[7],
			lhs[0] * rhs[2] + lhs[1] * rhs[5] + lhs[2] * rhs[8],

			lhs[3] * rhs[0] + lhs[4] * rhs[3] + lhs[5] * rhs[6],
			lhs[3] * rhs[1] + lhs[4] * rhs[4] + lhs[5] * rhs[7],
			lhs[3] * rhs[2] + lhs[4] * rhs[5] + lhs[5] * rhs[8],

			lhs[6] * rhs[0] + lhs[7] * rhs[3] + lhs[8] * rhs[6],
			lhs[6] * rhs[1] + lhs[7] * rhs[4] + lhs[8] * rhs[7],
			lhs[6] * rhs[2] + lhs[7] * rhs[5] + lhs[8] * rhs[8]
		);
	}

	std::ostream& operator <<(std::ostream& out, const Matrix3& A)
	{
		std::string stringMatrix[9];
		std::size_t columnLengths[3] = {0, 0, 0};

		for (std::size_t i = 0; i < 3; ++i)
		{
			for (std::size_t j = 0; j < 3; ++j)
			{
				const std::string str = std::to_string(A[3 * i + j]);

				const std::size_t len = str.length();
				if (len > columnLengths[j]) columnLengths[j] = len;

				stringMatrix[3 * i + j] = str;
			}
		}

		const std::size_t totalLength = columnLengths[0] + columnLengths[1] +
			columnLengths[2] + 2;

		out << "┌─";
		for (std::size_t i = 0; i < totalLength; ++i) out << " ";
		out << "─┐" << std::endl;

		for (std::size_t i = 0; i < 3; ++i)
		{
			out << "│";

			for (std::size_t j = 0; j < 3; ++j)
			{
				const std::string str = stringMatrix[3 * i + j];
				const std::size_t len = str.length();

				for (std::size_t k = 0; k < columnLengths[j] - len; ++k)
				{
					out << " ";
				}

				out << " " << str;
			}

			out << " │" << std::endl;
		}

		out << "└─";
		for (std::size_t i = 0; i < totalLength; ++i) out << " ";
		out << "─┘";

		return out;
	}

	Matrix3 Matrix3::transposed() const
	{
		return Matrix3(
			m[0], m[3], m[6],
			m[1], m[4], m[7],
			m[2], m[5], m[8]
		);
	}

	void Matrix3::transpose()
	{
		std::swap(m[1], m[3]);
		std::swap(m[2], m[6]);
		std::swap(m[5], m[7]);
	}

	float Matrix3::determinant() const
	{
		return m[0] * m[4] * m[8] + m[1] * m[5] * m[6] + m[2] * m[3] * m[7]
			- m[6] * m[4] * m[2] - m[7] * m[5] * m[0] - m[8] * m[3] * m[1];
	}

	Matrix3 Matrix3::inverse() const
	{
		// Ensure that the matrix is not singular.
		const float det = determinant();
		assert(det != 0.0f);

		// Return a copy of the inverse of this matrix.
		const float invDet = 1.0f / det;
		return Matrix3(
			(m[4] * m[8] - m[5] * m[7]) * invDet,
			(m[7] * m[2] - m[8] * m[1]) * invDet,
			(m[1] * m[5] - m[2] * m[4]) * invDet,
			(m[6] * m[5] - m[3] * m[8]) * invDet,
			(m[0] * m[8] - m[6] * m[2]) * invDet,
			(m[3] * m[2] - m[0] * m[5]) * invDet,
			(m[3] * m[7] - m[6] * m[4]) * invDet,
			(m[6] * m[1] - m[0] * m[7]) * invDet,
			(m[0] * m[4] - m[3] * m[1]) * invDet
		);
	}

	Matrix3 Matrix3::angleAxis(const float angle, const Vector3& axis)
	{
		const float c = std::cos(angle);
		const float s = std::sin(angle);

		const float nc = 1.0f - c;

		const float nc_xy = nc * axis.x * axis.y;
		const float nc_yz = nc * axis.y * axis.z;
		const float nc_xz = nc * axis.x * axis.z;

		const float sx = s * axis.x;
		const float sy = s * axis.y;
		const float sz = s * axis.z;

		return Matrix3(
			nc * axis.x * axis.x + c,
			nc_xy - sz,
			nc_xz + sy,
			nc_xy + sz,
			nc * axis.y * axis.y + c,
			nc_yz - sx,
			nc_xz - sy,
			nc_yz + sx,
			nc * axis.z * axis.z + c
		);
	}

	Matrix3 Matrix3::euler(const Vector3& eulerAngles)
	{
		const float s1 = std::sin(eulerAngles.x);
		const float s2 = std::sin(eulerAngles.y);
		const float s3 = std::sin(eulerAngles.z);

		const float c1 = std::cos(eulerAngles.x);
		const float c2 = std::cos(eulerAngles.y);
		const float c3 = std::cos(eulerAngles.z);

		return Matrix3(
			c2 * c3,
			-c2 * s3,
			s2,
			c1 * s3 + c3 * s1 * s2,
			c1 * c3 - s1 * s2 * s3,
			-c2 * s1,
			s1 * s3 - c1 * c3 * s2,
			c3 * s1 + c1 * s2 * s3,
			c1 * c2
		);
	}

	Matrix3 Matrix3::fromToRotation(const Vector3& fromDirection, const Vector3& toDirection)
	{
		assert(fromDirection.sqrMagnitude() > 0.0f && toDirection.sqrMagnitude() > 0.0f);
		const Vector3 unitFrom = fromDirection.normalized();
		const Vector3 unitTo = toDirection.normalized();
		const float d = dot(unitFrom, unitTo);

		if (d >= 1.0f)
		{
			// In the case where the two vectors are pointing in the same
			// direction, we simply return the identity matrix - corresponding
			// to no rotation.
			return Matrix3::IDENTITY;
		}
		else if (d <= -1.0f)
		{
			// If the two vectors are pointing in opposite directions then we
			// need to supply a rotation matrix corresponding to a rotation of
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
			// Determine the axis of rotation.
			Vector3 unitAxis = cross(fromDirection, toDirection);
			unitAxis.normalize();

			// Find the angle between the two vectors.
			const float theta = angle(fromDirection, toDirection);

			// Construct the rotation matrix.
			return angleAxis(theta, unitAxis);
		}
	}

	Matrix3 Matrix3::lookRotation(const Vector3& forward, const Vector3& upwards)
	{
		// The forward and upwards vectors should not be linearly dependent
		// (colinear).
		assert(cross(forward, upwards).sqrMagnitude() != 0.0f);

		// We rotate so that the z-axis points in the specified forward
		// direction.
		const Vector3 zAxis = forward.normalized();

		// The x-axis is now orthogonal to both the z-axis and the specified
		// up direction. Note that the z-axis is pointing out of the screen
		// in the right-handed coordinate system.
		const Vector3 xAxis = cross(upwards, zAxis).normalized();

		// Now the real y-axis is determined to be the vector orthogonal to both
		// the zAxis and xAxis. This is necessary because we don't know whether
		// the specified upwards direction is orthogonal to the specified
		// forward direction.
		const Vector3 yAxis = cross(zAxis, xAxis).normalized();

		// Finally return the rotation matrix.
		return Matrix3(
			xAxis.x, yAxis.x, zAxis.x,
			xAxis.y, yAxis.y, zAxis.y,
			xAxis.z, yAxis.z, zAxis.z
		);
	}
}
