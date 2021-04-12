#include <M3D/Matrix2.hpp>

#include <cmath>
#include <cassert>
#include <cstring>
#include <iostream>

namespace M3D
{
	const Matrix2 Matrix2::IDENTITY = Matrix2();
	const Matrix2 Matrix2::ZERO = Matrix2({0.0f, 0.0f, 0.0f, 0.0f});

	Matrix2::Matrix2()
	: m{1.0f, 0.0f, 0.0f, 1.0f}
	{
		// Nothing to do.
	}

	Matrix2::Matrix2(const float arr[4])
	{
		std::memcpy(m, arr, 4 * sizeof(float));
	}

	Matrix2::Matrix2(float entry00, float entry01, float entry10, float entry11)
	: m{entry00, entry01, entry10, entry11}
	{
		// Nothing to do.
	}

	float Matrix2::operator[](std::size_t index) const
	{
		assert(index < 4);
		return m[index];
	}

	bool operator==(const Matrix2& A, const Matrix2& B)
	{
		const float epsilon = 1e-6;
		for (std::size_t i = 0; i < 4; ++i)
		{
			if (std::abs(A[i] - B[i]) > epsilon) return false;
		}

		return true;
	}

	bool operator!=(const Matrix2& A, const Matrix2& B)
	{
		return !(A == B);
	}

	Matrix2 operator+(const Matrix2& A, const Matrix2& B)
	{
		return Matrix2(
			A[0] + B[0], A[1] + B[1],
			A[2] + B[2], A[3] + B[3]
		);
	}

	Matrix2 operator-(const Matrix2& lhs, const Matrix2& rhs)
	{
		return Matrix2(
			lhs[0] - rhs[0], lhs[1] - rhs[1],
			lhs[2] - rhs[2], lhs[3] - rhs[3]
		);
	}

	Matrix2 operator-(const Matrix2& A)
	{
		return Matrix2(
			-A[0], -A[1],
			-A[2], -A[3]
		);
	}

	Matrix2 operator*(const Matrix2& A, const float s)
	{
		return Matrix2(
			A[0] * s, A[1] * s,
			A[2] * s, A[3] * s
		);
	}

	Matrix2 operator*(const float s, const Matrix2& A)
	{
		return A * s;
	}

	Vector2 operator*(const Matrix2& lhs, const Vector2& rhs)
	{
		return Vector2(
			lhs[0] * rhs.x + lhs[1] * rhs.y,
			lhs[2] * rhs.x + lhs[3] * rhs.y
		);
	}

	Vector2 operator*(const Vector2& lhs, const Matrix2& rhs)
	{
		return Vector2(
			lhs.x * rhs[0] + lhs.y * rhs[2],
			lhs.x * rhs[1] + lhs.y * rhs[3]
		);
	}

	Matrix2 operator*(const Matrix2& lhs, const Matrix2& rhs)
	{
		return Matrix2(
			lhs[0] * rhs[0] + lhs[1] * rhs[2],
			lhs[0] * rhs[1] + lhs[1] * rhs[3],

			lhs[2] * rhs[0] + lhs[3] * rhs[2],
			lhs[2] * rhs[1] + lhs[3] * rhs[3]
		);
	}

	std::ostream& operator <<(std::ostream& out, const Matrix2& A)
	{
		std::string stringMatrix[4];
		std::size_t columnLengths[2] = {0, 0};

		for (std::size_t i = 0; i < 2; ++i)
		{
			for (std::size_t j = 0; j < 2; ++j)
			{
				const std::string str = std::to_string(A[2 * i + j]);

				const std::size_t len = str.length();
				if (len > columnLengths[j]) columnLengths[j] = len;

				stringMatrix[2 * i + j] = str;
			}
		}

		const std::size_t totalLength = columnLengths[0] + columnLengths[1] + 1;

		out << "┌─";
		for (std::size_t i = 0; i < totalLength; ++i) out << " ";
		out << "─┐" << std::endl;

		for (std::size_t i = 0; i < 2; ++i)
		{
			out << "│";

			for (std::size_t j = 0; j < 2; ++j)
			{
				const std::string str = stringMatrix[2 * i + j];
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

	Matrix2 Matrix2::transposed() const
	{
		return Matrix2(
			m[0], m[2],
			m[1], m[3]
		);
	}

	void Matrix2::transpose()
	{
		std::swap(m[1], m[2]);
	}

	float Matrix2::determinant() const
	{
		return m[0] * m[3] - m[1] * m[2];
	}

	Matrix2 Matrix2::inverse() const
	{
		// Ensure that the matrix is not singular.
		const float det = determinant();
		assert(det != 0.0f);

		// Return a copy of the inverse of this matrix.
		const float invDet = 1.0f / det;
		return Matrix2(
			m[3] * invDet, -m[1] * invDet,
			-m[2] * invDet, m[0] * invDet
		);
	}

	Matrix2 Matrix2::scaling(const Vector2& scaleFactors)
	{
		return Matrix2(
			scaleFactors.x, 0.0f,
			0.0f, scaleFactors.y
		);
	}

	Matrix2 Matrix2::scaling(const float factor)
	{
		return Matrix2(
			factor, 0.0f,
			0.0f, factor
		);
	}

	Matrix2 Matrix2::angleRotation(const float angle)
	{
		const float cosTheta = std::cos(angle);
		const float sinTheta = std::sin(angle);
		return Matrix2(
			cosTheta, -sinTheta,
			sinTheta, cosTheta
		);
	}

	Matrix2 Matrix2::fromToRotation(const Vector2& fromDirection, const Vector2& toDirection)
	{
		assert(fromDirection.sqrMagnitude() > 0.0f && toDirection.sqrMagnitude() > 0.0f);

		// Compute the angle between the two vectors.
		const float theta = angle(fromDirection, toDirection);

		// Return the rotation matrix.
		return angleRotation(theta);
	}
}
