#include <M3D/Matrix4.hpp>
#include <M3D/Quaternion.hpp>
#include <M3D/Vector3.hpp>
#include <M3D/Vector4.hpp>

#include <cmath>
#include <cassert>
#include <cstring>

namespace M3D
{
	const Matrix4 Matrix4::IDENTITY = Matrix4();
	const Matrix4 Matrix4::ZERO = Matrix4({
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	});

	Matrix4::Matrix4()
	: m{1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f}
	{
		// Nothing to do.
	}

	Matrix4::Matrix4(const float arr[16])
	{
		std::memcpy(m, arr, 16 * sizeof(float));
	}

	Matrix4::Matrix4(float entry00, float entry01, float entry02, float entry03,
		float entry10, float entry11, float entry12, float entry13,
		float entry20, float entry21, float entry22, float entry23,
		float entry30, float entry31, float entry32, float entry33)
	: m{entry00, entry01, entry02, entry03,
		entry10, entry11, entry12, entry13,
		entry20, entry21, entry22, entry23,
		entry30, entry31, entry32, entry33}
	{
		// Nothing to do.
	}

	Matrix4::Matrix4(const Matrix3& A)
	: m{A[0], A[1], A[2], 0.0f,
		A[3], A[4], A[5], 0.0f,
		A[6], A[7], A[8], 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f}
	{
		// Nothing to do.
	}

	Matrix4::Matrix4(const Quaternion& q)
	: m{1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z,
		2.0f * q.x * q.y - 2.0f * q.w * q.z,
		2.0f * q.x * q.z + 2.0f * q.w * q.y,
		0.0f,
		2.0f * q.x * q.y + 2.0f * q.w * q.z,
		1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z,
		2.0f * q.y * q.z - 2.0f * q.w * q.x,
		0.0f,
		2.0f * q.x * q.z - 2.0f * q.w * q.y,
		2.0f * q.y * q.z + 2.0f * q.w * q.x,
		1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y,
		1.0f}
	{
		// Nothing to do.
	}

	float Matrix4::operator[](std::size_t index) const
	{
		assert(index < 16);
		return m[index];
	}

	bool operator==(const Matrix4& A, const Matrix4& B)
	{
		const float epsilon = 1e-6;
		for (std::size_t i = 0; i < 16; ++i)
		{
			if (std::abs(A[i] - B[i]) > epsilon) return false;
		}

		return true;
	}

	bool operator!=(const Matrix4& A, const Matrix4& B)
	{
		return !(A == B);
	}

	Matrix4 operator+(const Matrix4& A, const Matrix4& B)
	{
		return Matrix4(
			A[0] + B[0], A[1] + B[1], A[2] + B[2], A[3] + B[3],
			A[4] + B[4], A[5] + B[5], A[6] + B[6], A[7] + B[7],
			A[8] + B[8], A[9] + B[9], A[10] + B[10], A[11] + B[11],
			A[12] + B[12], A[13] + B[13], A[14] + B[14], A[15] + B[15]
		);
	}

	Matrix4 operator-(const Matrix4& lhs, const Matrix4& rhs)
	{
		return Matrix4(
			lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3],
			lhs[4] - rhs[4], lhs[5] - rhs[5], lhs[6] - rhs[6], lhs[7] - rhs[7],
			lhs[8] - rhs[8], lhs[9] - rhs[9], lhs[10] - rhs[10], lhs[11] - rhs[11],
			lhs[12] - rhs[12], lhs[13] - rhs[13], lhs[14] - rhs[14], lhs[15] - rhs[15]
		);
	}

	Matrix4 operator-(const Matrix4& A)
	{
		return Matrix4(
			-A[0], -A[1], -A[2], -A[3],
			-A[4], -A[5], -A[6], -A[7],
			-A[8], -A[9], -A[10], -A[11],
			-A[12], -A[13], -A[14], -A[15]
		);
	}

	Matrix4 operator*(const Matrix4& A, const float s)
	{
		return Matrix4(
			A[0] * s, A[1] * s, A[2] * s, A[3] * s,
			A[4] * s, A[5] * s, A[6] * s, A[7] * s,
			A[8] * s, A[9] * s, A[10] * s, A[11] * s,
			A[12] * s, A[13] * s, A[14] * s, A[15] * s
		);
	}

	Matrix4 operator*(const float s, const Matrix4& A)
	{
		return A * s;
	}

	Vector4 operator*(const Matrix4& lhs, const Vector4& rhs)
	{
		return Vector4(
			lhs[0] * rhs.x + lhs[1] * rhs.y + lhs[2] * rhs.z + lhs[3] * rhs.w,
			lhs[4] * rhs.x + lhs[5] * rhs.y + lhs[6] * rhs.z + lhs[7] * rhs.w,
			lhs[8] * rhs.x + lhs[9] * rhs.y + lhs[10] * rhs.z + lhs[11] * rhs.w,
			lhs[12] * rhs.x + lhs[13] * rhs.y + lhs[14] * rhs.z + lhs[15] * rhs.w
		);
	}

	Vector4 operator*(const Vector4& lhs, const Matrix4& rhs)
	{
		return Vector4(
			lhs.x * rhs[0] + lhs.y * rhs[4] + lhs.z * rhs[8] + lhs.w * rhs[12],
			lhs.x * rhs[1] + lhs.y * rhs[5] + lhs.z * rhs[9] + lhs.w * rhs[13],
			lhs.x * rhs[2] + lhs.y * rhs[6] + lhs.z * rhs[10] + lhs.w * rhs[14],
			lhs.x * rhs[3] + lhs.y * rhs[7] + lhs.z * rhs[11] + lhs.w * rhs[15]
		);
	}

	Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
	{
		return Matrix4(
			lhs[0] * rhs[0] + lhs[1] * rhs[4] + lhs[2] * rhs[8] + lhs[3] * rhs[12],
			lhs[0] * rhs[1] + lhs[1] * rhs[5] + lhs[2] * rhs[9] + lhs[3] * rhs[13],
			lhs[0] * rhs[2] + lhs[1] * rhs[6] + lhs[2] * rhs[10] + lhs[3] * rhs[14],
			lhs[0] * rhs[3] + lhs[1] * rhs[7] + lhs[2] * rhs[11] + lhs[3] * rhs[15],

			lhs[4] * rhs[0] + lhs[5] * rhs[4] + lhs[6] * rhs[8] + lhs[7] * rhs[12],
			lhs[4] * rhs[1] + lhs[5] * rhs[5] + lhs[6] * rhs[9] + lhs[7] * rhs[13],
			lhs[4] * rhs[2] + lhs[5] * rhs[6] + lhs[6] * rhs[10] + lhs[7] * rhs[14],
			lhs[4] * rhs[3] + lhs[5] * rhs[7] + lhs[6] * rhs[11] + lhs[7] * rhs[15],

			lhs[8] * rhs[0] + lhs[9] * rhs[4] + lhs[10] * rhs[8] + lhs[11] * rhs[12],
			lhs[8] * rhs[1] + lhs[9] * rhs[5] + lhs[10] * rhs[9] + lhs[11] * rhs[13],
			lhs[8] * rhs[2] + lhs[9] * rhs[6] + lhs[10] * rhs[10] + lhs[11] * rhs[14],
			lhs[8] * rhs[3] + lhs[9] * rhs[7] + lhs[10] * rhs[11] + lhs[11] * rhs[15],

			lhs[12] * rhs[0] + lhs[13] * rhs[4] + lhs[14] * rhs[8] + lhs[15] * rhs[12],
			lhs[12] * rhs[1] + lhs[13] * rhs[5] + lhs[14] * rhs[9] + lhs[15] * rhs[13],
			lhs[12] * rhs[2] + lhs[13] * rhs[6] + lhs[14] * rhs[10] + lhs[15] * rhs[14],
			lhs[12] * rhs[3] + lhs[13] * rhs[7] + lhs[14] * rhs[11] + lhs[15] * rhs[15]
		);
	}

	std::ostream& operator <<(std::ostream& out, const Matrix4& A)
	{
		std::string stringMatrix[16];
		std::size_t columnLengths[4] = {0, 0, 0, 0};

		for (std::size_t i = 0; i < 4; ++i)
		{
			for (std::size_t j = 0; j < 4; ++j)
			{
				const std::string str = std::to_string(A[4 * i + j]);

				const std::size_t len = str.length();
				if (len > columnLengths[j]) columnLengths[j] = len;

				stringMatrix[4 * i + j] = str;
			}
		}

		const std::size_t totalLength = columnLengths[0] + columnLengths[1] +
			columnLengths[2] + columnLengths[3] + 3;

		out << "┌─";
		for (std::size_t i = 0; i < totalLength; ++i) out << " ";
		out << "─┐" << std::endl;

		for (std::size_t i = 0; i < 4; ++i)
		{
			out << "│";

			for (std::size_t j = 0; j < 4; ++j)
			{
				const std::string str = stringMatrix[4 * i + j];
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

	Matrix4 Matrix4::transposed() const
	{
		return Matrix4(
			m[0], m[4], m[8], m[12],
			m[1], m[5], m[9], m[13],
			m[2], m[6], m[10], m[14],
			m[3], m[7], m[11], m[15]
		);
	}

	void Matrix4::transpose()
	{
		std::swap(m[1], m[4]);
		std::swap(m[2], m[8]);
		std::swap(m[3], m[12]);
		std::swap(m[6], m[9]);
		std::swap(m[7], m[13]);
		std::swap(m[11], m[14]);
	}

	float Matrix4::determinant() const
	{
		const float det1 = m[10] * (m[15] * m[5] - m[7] * m[13]) + m[11] * (m[13] * m[6] - m[5] * m[14]) + m[9] * (m[14] * m[7] - m[6] * m[15]);
		const float det2 = m[1] * (m[10] * m[15] - m[11] * m[14]) + m[2] * (m[11] * m[13] - m[9] * m[15]) + m[3] * (m[9] * m[14] - m[10] * m[13]);
		const float det3 = m[1] * (m[6] * m[15] - m[7] * m[14]) + m[2] * (m[7] * m[13] - m[5] * m[15]) + m[3] * (m[5] * m[14] - m[6] * m[13]);
		const float det4 = m[1] * (m[6] * m[11] - m[7] * m[10]) + m[2] * (m[7] * m[9] - m[5] * m[11]) + m[3] * (m[5] * m[10] - m[6] * m[9]);

		return (m[0] * det1 - m[4] * det2 + m[8] * det3 - m[12] * det4);
	}

	// Taken from the MESA implementation of the GLU library.
	Matrix4 Matrix4::inverse() const
	{
		float inv[16];

		inv[0] =	m[5]  * m[10] * m[15] -
					m[5]  * m[11] * m[14] -
					m[9]  * m[6]  * m[15] +
					m[9]  * m[7]  * m[14] +
					m[13] * m[6]  * m[11] -
					m[13] * m[7]  * m[10];

		inv[4] =   -m[4]  * m[10] * m[15] +
					m[4]  * m[11] * m[14] +
					m[8]  * m[6]  * m[15] -
					m[8]  * m[7]  * m[14] -
					m[12] * m[6]  * m[11] +
					m[12] * m[7]  * m[10];

		inv[8] =	m[4]  * m[9]  * m[15] -
					m[4]  * m[11] * m[13] -
					m[8]  * m[5]  * m[15] +
					m[8]  * m[7]  * m[13] +
					m[12] * m[5]  * m[11] -
					m[12] * m[7]  * m[9];

		inv[12] =  -m[4]  * m[9]  * m[14] +
					m[4]  * m[10] * m[13] +
					m[8]  * m[5]  * m[14] -
					m[8]  * m[6]  * m[13] -
					m[12] * m[5]  * m[10] +
					m[12] * m[6]  * m[9];

		inv[1] =   -m[1]  * m[10] * m[15] +
					m[1]  * m[11] * m[14] +
					m[9]  * m[2]  * m[15] -
					m[9]  * m[3]  * m[14] -
					m[13] * m[2]  * m[11] +
					m[13] * m[3]  * m[10];

		inv[5] =	m[0]  * m[10] * m[15] -
					m[0]  * m[11] * m[14] -
					m[8]  * m[2]  * m[15] +
					m[8]  * m[3]  * m[14] +
					m[12] * m[2]  * m[11] -
					m[12] * m[3]  * m[10];

		inv[9] =   -m[0]  * m[9]  * m[15] +
					m[0]  * m[11] * m[13] +
					m[8]  * m[1]  * m[15] -
					m[8]  * m[3]  * m[13] -
					m[12] * m[1]  * m[11] +
					m[12] * m[3]  * m[9];

		inv[13] =	m[0]  * m[9]  * m[14] -
					m[0]  * m[10] * m[13] -
					m[8]  * m[1]  * m[14] +
					m[8]  * m[2]  * m[13] +
					m[12] * m[1]  * m[10] -
					m[12] * m[2]  * m[9];

		inv[2] =	m[1]  * m[6]  * m[15] -
					m[1]  * m[7]  * m[14] -
					m[5]  * m[2]  * m[15] +
					m[5]  * m[3]  * m[14] +
					m[13] * m[2]  * m[7]  -
					m[13] * m[3]  * m[6];

		inv[6] =   -m[0]  * m[6]  * m[15] +
					m[0]  * m[7]  * m[14] +
					m[4]  * m[2]  * m[15] -
					m[4]  * m[3]  * m[14] -
					m[12] * m[2]  * m[7]  +
					m[12] * m[3]  * m[6];

		inv[10] =   m[0]  * m[5]  * m[15] -
					m[0]  * m[7]  * m[13] -
					m[4]  * m[1]  * m[15] +
					m[4]  * m[3]  * m[13] +
					m[12] * m[1]  * m[7]  -
					m[12] * m[3]  * m[5];

		inv[14] =  -m[0]  * m[5]  * m[14] +
					m[0]  * m[6]  * m[13] +
					m[4]  * m[1]  * m[14] -
					m[4]  * m[2]  * m[13] -
					m[12] * m[1]  * m[6]  +
					m[12] * m[2]  * m[5];

		inv[3] =   -m[1]  * m[6]  * m[11] +
					m[1]  * m[7]  * m[10] +
					m[5]  * m[2]  * m[11] -
					m[5]  * m[3]  * m[10] -
					m[9]  * m[2]  * m[7]  +
					m[9]  * m[3]  * m[6];

		inv[7] =	m[0]  * m[6]  * m[11] -
					m[0]  * m[7]  * m[10] -
					m[4]  * m[2]  * m[11] +
					m[4]  * m[3]  * m[10] +
					m[8]  * m[2]  * m[7]  -
					m[8]  * m[3]  * m[6];

		inv[11] =  -m[0]  * m[5]  * m[11] +
					m[0]  * m[7]  * m[9]  +
					m[4]  * m[1]  * m[11] -
					m[4]  * m[3]  * m[9]  -
					m[8]  * m[1]  * m[7]  +
					m[8]  * m[3]  * m[5];

		inv[15] =	m[0]  * m[5]  * m[10] -
					m[0]  * m[6]  * m[9]  -
					m[4]  * m[1]  * m[10] +
					m[4]  * m[2]  * m[9]  +
					m[8]  * m[1]  * m[6]  -
					m[8]  * m[2]  * m[5];

		// Determinant.
		const float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		// Ensure that the matrix is not singular.
		assert(det != 0.0f);

		// Return a copy of the inverse of this matrix.
		const float invDet = 1.0f / det;
		for (std::size_t i = 0; i < 16; ++i) inv[i] *= invDet;
		return Matrix4(inv);
	}

	Matrix4 Matrix4::scaling(const Vector3& scaleFactors)
	{
		return Matrix4(
			scaleFactors.x, 0.0f, 0.0f, 0.0f,
			0.0f, scaleFactors.y, 0.0f, 0.0f,
			0.0f, 0.0f, scaleFactors.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4 Matrix4::scaling(const float factor)
	{
		return Matrix4(
			factor, 0.0f, 0.0f, 0.0f,
			0.0f, factor, 0.0f, 0.0f,
			0.0f, 0.0f, factor, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4 Matrix4::translation(const Vector3& translation)
	{
		return Matrix4(
			1.0f, 0.0f, 0.0f, translation.x,
			0.0f, 1.0f, 0.0f, translation.y,
			0.0f, 0.0f, 1.0f, translation.z,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4 Matrix4::angleAxis(const float angle, const Vector3& axis)
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

		return Matrix4(
			nc * axis.x * axis.x + c, nc_xy - sz, nc_xz + sy, 0.0f,
			nc_xy + sz, nc * axis.y * axis.y + c, nc_yz - sx, 0.0f,
			nc_xz - sy, nc_yz + sx, nc * axis.z * axis.z + c, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4 Matrix4::euler(const Vector3& eulerAngles)
	{
		const float s1 = std::sin(eulerAngles.x);
		const float s2 = std::sin(eulerAngles.y);
		const float s3 = std::sin(eulerAngles.z);

		const float c1 = std::cos(eulerAngles.x);
		const float c2 = std::cos(eulerAngles.y);
		const float c3 = std::cos(eulerAngles.z);

		return Matrix4(
			c2 * c3, -c2 * s3, s2, 0.0f,
			c1 * s3 + c3 * s1 * s2, c1 * c3 - s1 * s2 * s3, -c2 * s1, 0.0f,
			s1 * s3 - c1 * c3 * s2, c3 * s1 + c1 * s2 * s3, c1 * c2, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4 Matrix4::fromToRotation(const Vector3& fromDirection, const Vector3& toDirection)
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
			return Matrix4::IDENTITY;
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

	Matrix4 Matrix4::lookRotation(const Vector3& forward, const Vector3& upwards)
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
		return Matrix4(
			xAxis.x, yAxis.x, zAxis.x, 0.0f,
			xAxis.y, yAxis.y, zAxis.y, 0.0f,
			xAxis.z, yAxis.z, zAxis.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4 Matrix4::lookRotation(const Vector3& target, const Vector3& eye, const Vector3& upwards)
	{
		const Vector3 forward = target - eye;

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
		return Matrix4(
			xAxis.x, yAxis.x, zAxis.x, 0.0f,
			xAxis.y, yAxis.y, zAxis.y, 0.0f,
			xAxis.z, yAxis.z, zAxis.z, 0.0f,
			-dot(xAxis, eye), -dot(yAxis, eye), -dot(zAxis, eye), 1.0f
		);
	}
}
