//=====================================================================================================================
//	�t�@�C����:	UtlMath.cpp
//	�쐬��:		�����O�X
//=====================================================================================================================
//	�X�V����
//		-ver 1.00	2016 / 06 / 27	�����O�X
//		-ver 1.01	2016 / 07 / 01	�����O�X	�߂�l�� std::tuple ���g�p
//		-ver 1.02	2016 / 07 / 16	�����O�X	�����E�����E���Ȃǂ�UtlShape�ɕ���
//=====================================================================================================================
//	�t�@�C���̐���
//				Vector, Matrix �ȂǕ����E���w�n
//=====================================================================================================================

//====================================
//�@���@�C���N���[�h�@��
//====================================
#include "UtlMath.h"

//====================================
//�@���O��ԁFt_lib
//====================================
namespace t_lib
{
	//=====================================================================================================================
	// 2D Vector
	//=====================================================================================================================

	Vector2& Vector2::operator += (const Vector2& v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}

	Vector2& Vector2::operator -= (const Vector2& v)
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}

	Vector2& Vector2::operator *= (float t)
	{
		x *= t;
		y *= t;

		return *this;
	}

	Vector2& Vector2::operator /= (float t)
	{
		float inv = F_ONE / t;

		x *= inv;
		y *= inv;

		return *this;
	}

	Vector2 Vector2::operator / (float t) const
	{
		float inv = F_ONE / t;

		return Vector2(x * inv, y * inv);
	}

	//=============================================================================
	// �֐����F		init
	// �����F		0�x�N�g���쐬
	//=============================================================================
	Vector2& Vector2::initialize()
	{
		*this = VEC2_ZERO;

		return *this;
	}

	//=============================================================================
	// �֐����F		normalize
	// �����F		���K��
	//=============================================================================
	Vector2& Vector2::normalize()
	{
		float len = length();

		if(!len)
		{
			x = y = F_ZERO;

			return *this;
		}

		float inv = F_ONE / len;

		x *= inv;
		y *= inv;

		return *this;
	}

	//=============================================================================
	// �֐����F		length
	// �����F		�����̎擾
	//=============================================================================
	float Vector2::length() const
	{
		return sqrtf(x * x + y * y);
	}

	//=============================================================================
	// �֐����F		lerp
	// �����F		const Vector2& v	��x�N�g��
	// �����F		float t				����
	// �����F		�Ăяo���x�N�g��(this)�@�Ɗ�x�N�g��(v)�@�̊Ԃ�
	//				����(t)�@�ɂ��A���`��Ԃ����x�N�g�����擾����
	//=============================================================================
	Vector2 Vector2::lerp(const Vector2& v, float t) const
	{
		return *this + (v - *this) * t;
	}

	//=====================================================================================================================
	// 3D Vector
	//=====================================================================================================================

	Vector3& Vector3::operator += (const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	Vector3& Vector3::operator -= (const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	Vector3& Vector3::operator *= (float t)
	{
		x *= t;
		y *= t;
		z *= t;

		return *this;
	}

	Vector3& Vector3::operator /= (float t)
	{
		float inv = F_ONE / t;

		x *= inv;
		y *= inv;
		z *= inv;

		return *this;
	}

	Vector3 Vector3::operator / (float t) const
	{
		float inv = F_ONE / t;

		return Vector3(x * inv, y * inv, z * inv);
	}

	//=============================================================================
	// �֐����F		init
	// �����F		0�x�N�g���쐬
	//=============================================================================
	Vector3& Vector3::initialize()
	{
		*this = VEC3_ZERO;

		return *this;
	}

	//=============================================================================
	// �֐����F		normalize
	// �����F		���K��
	//=============================================================================
	Vector3& Vector3::normalize()
	{
		float len = length();

		if(!len)
		{
			x = y = z = F_ZERO;

			return *this;
		}

		float inv = F_ONE / len;

		x *= inv;
		y *= inv;
		z *= inv;

		return *this;
	}

	//=============================================================================
	// �֐����F		length
	// �����F		�����̎擾
	//=============================================================================
	float Vector3::length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	//=============================================================================
	// �֐����F		get_normalized
	// �����F		normalize���ꂽ�x�N�g���̎擾
	//=============================================================================
	Vector3 Vector3::get_normalized() const
	{
		float len = length();

		if(len > 0.0f)
		{
			float inv_len = 1.0f / len;
			return Vector3(x * inv_len, y * inv_len, z * inv_len);
		}

		return VEC3_ZERO;
	}

	//=============================================================================
	// �֐����F		angle_by_vec3
	// �����F		�����x�N�g���Ƃ́@�����p�@���擾����
	//=============================================================================
	float Vector3::angle_by_vec3(const Vector3& v) const
	{
		return std::acos(dot(v) / (this->length() * v.length()));
	}

	//=============================================================================
	// �֐����F		is_vertical
	// �����F		�x�N�g�����m��������
	//=============================================================================
	bool Vector3::is_vertical(const Vector3& v) const
	{
		return is_in(dot(v), -CALC_EPS, CALC_EPS);
	}

	//=============================================================================
	// �֐����F		is_parallel
	// �����F		�x�N�g�����m�����s��
	//=============================================================================
	bool Vector3::is_parallel(const Vector3& v) const
	{
		return is_in(cross(v).length_sq(), -CALC_EPS, CALC_EPS);
	}

	//=============================================================================
	// �֐����F		is_angle_sharp_by_vec
	// �����F		�x�N�g���̐����p�x���s�p��
	//=============================================================================
	bool Vector3::is_angle_sharp_by_vec(const Vector3& v) const
	{
		return (dot(v) >= 0.0f);
	}

	//=============================================================================
	// �֐����F		along
	// �����F		�@���ɉ������@�x�N�g�����擾����
	//=============================================================================
	Vector3 Vector3::along(const Vector3& nor) const
	{
		return (*this - nor * dot(nor)).normalize();
	}

	//=============================================================================
	// �֐����F		reflect
	// �����F		�@���ɔ��˂����@�x�N�g�����擾����
	//=============================================================================
	Vector3 Vector3::reflect(const Vector3& nor) const
	{
		return  (*this - nor * (2.0f * dot(nor))).normalize();
	}

	//=============================================================================
	// �֐����F		cross
	// �����F		�����x�N�g���Ƃ́@�O�ρ@���擾����
	//=============================================================================
	Vector3 Vector3::cross(const Vector3& v) const
	{
		return Vector3(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x);
	}

	//=============================================================================
	// �֐����F		lerp
	// �����F		const Vector3& v	��x�N�g��
	// �����F		float t				����
	// �����F		�Ăяo���x�N�g��(this)�@�Ɗ�x�N�g��(v)�@�̊Ԃ�
	//				����(t)�@�ɂ��A���`��Ԃ����x�N�g�����擾����
	//=============================================================================
	Vector3 Vector3::lerp(const Vector3& v, float t) const
	{
		return *this + (v - *this) * t;
	}

	//=============================================================================
	// �֐����F		transform
	// �����F		Matrix�ɂ��A���s�ړ���� 4�����x�N�g�� ���擾����
	//=============================================================================
	Vector4 Vector3::transform(const Matrix& t) const
	{
		return Vector4(
			t.m[0][0] * x + t.m[1][0] * y + t.m[2][0] * z + t.m[3][0],
			t.m[0][1] * x + t.m[1][1] * y + t.m[2][1] * z + t.m[3][1],
			t.m[0][2] * x + t.m[1][2] * y + t.m[2][2] * z + t.m[3][2],
			t.m[0][3] * x + t.m[1][3] * y + t.m[2][3] * z + t.m[3][3]);
	}

	//=============================================================================
	// �֐����F		transform_coord
	// �����F		Matrix�ɂ��A���s�ړ���� 3�����x�N�g�� ���擾����
	//=============================================================================
	Vector3 Vector3::transform_coord(const Matrix& t) const
	{
		float inv_nor = F_ONE / (t.m[0][3] * x + t.m[1][3] * y + t.m[2][3] * z + t.m[3][3]);

		return Vector3(
			(t.m[0][0] * x + t.m[1][0] * y + t.m[2][0] * z + t.m[3][0]) * inv_nor,
			(t.m[0][1] * x + t.m[1][1] * y + t.m[2][1] * z + t.m[3][1]) * inv_nor,
			(t.m[0][2] * x + t.m[1][2] * y + t.m[2][2] * z + t.m[3][2]) * inv_nor);
	}

	//=============================================================================
	// �֐����F		transform_normal
	// �����F		Matrix�ɂ��A�@���x�N�g���̕��s�ړ�
	//=============================================================================
	Vector3 Vector3::transform_normal(const Matrix& t) const
	{
		return Vector3(
			t.m[0][0] * x + t.m[1][0] * y + t.m[2][0] * z,
			t.m[0][1] * x + t.m[1][1] * y + t.m[2][1] * z,
			t.m[0][2] * x + t.m[1][2] * y + t.m[2][2] * z);
	}

	//=====================================================================================================================
	// 4D Vector
	//=====================================================================================================================

	Vector4::Vector4(const Vector2 & v, float tz, float tw) :
		x(v.x), y(v.y), z(tz), w(tw)
	{}

	Vector4& Vector4::operator += (const Vector4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	Vector4& Vector4::operator -= (const Vector4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}

	Vector4& Vector4::operator *= (float t)
	{
		x *= t;
		y *= t;
		z *= t;
		w *= t;

		return *this;
	}

	Vector4& Vector4::operator /= (float t)
	{
		float inv = F_ONE / t;

		x *= inv;
		y *= inv;
		z *= inv;
		w *= inv;

		return *this;
	}

	Vector4 Vector4::operator / (float t) const
	{
		float inv = F_ONE / t;

		return Vector4(x * inv, y * inv, z * inv, w * inv);
	}

	bool Vector4::operator == (const Vector4& v) const
	{
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	bool Vector4::operator != (const Vector4& v) const
	{
		return x != v.x || y != v.y || z != v.z || w != v.w;
	}

	//=============================================================================
	// �֐����F		init
	// �����F		0�x�N�g���쐬
	//=============================================================================
	Vector4& Vector4::initialize()
	{
		*this = VEC4_ZERO;

		return *this;
	}

	//=============================================================================
	// �֐����F		normalize
	// �����F		���K��
	//=============================================================================
	Vector4& Vector4::normalize()
	{
		float len = length();

		if(!len)
		{
			x = y = z = w = F_ZERO;

			return *this;
		}

		float inv = F_ONE / len;

		x *= inv;
		y *= inv;
		z *= inv;
		w *= inv;

		return *this;
	}

	//=============================================================================
	// �֐����F		length
	// �����F		�����̎擾
	//=============================================================================
	float Vector4::length() const
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	//=============================================================================
	// �֐����F		dot
	// �����F		����
	//=============================================================================
	float Vector4::dot(const Vector4& t) const
	{
		return this->x * t.x + this->y * t.y + this->z * t.z + this->w * t.w;
	}

	//=============================================================================
	// �֐����F		lerp
	// �����F		const Vector4& v	��x�N�g��
	// �����F		float t				����
	// �����F		�Ăяo���x�N�g��(this)�@�Ɗ�x�N�g��(v)�@�̊Ԃ�
	//				����(t)�@�ɂ��A���`��Ԃ����x�N�g�����擾����
	//=============================================================================
	Vector4 Vector4::lerp(const Vector4& v, float t) const
	{
		return *this + (v - *this) * t;
	}

	//=====================================================================================================================
	// Matrix
	//=====================================================================================================================

	Matrix::Matrix(
		float t11, float t12, float t13, float t14,
		float t21, float t22, float t23, float t24,
		float t31, float t32, float t33, float t34,
		float t41, float t42, float t43, float t44) :
		_11(t11), _12(t12), _13(t13), _14(t14),
		_21(t21), _22(t22), _23(t23), _24(t24),
		_31(t31), _32(t32), _33(t33), _34(t34),
		_41(t41), _42(t42), _43(t43), _44(t44)
	{}

	Matrix& Matrix::operator *= (const Matrix& mat)
	{
		return multiply(mat);
	}

	Matrix& Matrix::operator += (const Matrix& mat)
	{
		_11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
		_21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
		_31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
		_41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;

		return *this;
	}

	Matrix& Matrix::operator -= (const Matrix& mat)
	{
		_11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
		_21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
		_31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
		_41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;

		return *this;
	}

	Matrix& Matrix::operator *= (float t)
	{
		_11 *= t; _12 *= t; _13 *= t; _14 *= t;
		_21 *= t; _22 *= t; _23 *= t; _24 *= t;
		_31 *= t; _32 *= t; _33 *= t; _34 *= t;
		_41 *= t; _42 *= t; _43 *= t; _44 *= t;

		return *this;
	}

	Matrix& Matrix::operator /= (float t)
	{
		float inv = F_ONE / t;

		_11 *= inv; _12 *= inv; _13 *= inv; _14 *= inv;
		_21 *= inv; _22 *= inv; _23 *= inv; _24 *= inv;
		_31 *= inv; _32 *= inv; _33 *= inv; _34 *= inv;
		_41 *= inv; _42 *= inv; _43 *= inv; _44 *= inv;

		return *this;
	}

	Matrix Matrix::operator - () const
	{
		return Matrix(
			-_11, -_12, -_13, -_14,
			-_21, -_22, -_23, -_24,
			-_31, -_32, -_33, -_34,
			-_41, -_42, -_43, -_44);
	}

	Matrix Matrix::operator * (const Matrix& mat) const
	{
		return Matrix(*this).multiply(mat);
	}

	Matrix Matrix::operator + (const Matrix& mat) const
	{
		return Matrix(
			_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
			_21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
			_31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
			_41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44);
	}

	Matrix Matrix::operator - (const Matrix& mat) const
	{
		return Matrix(
			_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
			_21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
			_31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
			_41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44);
	}

	Matrix Matrix::operator * (float t) const
	{
		return Matrix(
			_11 * t, _12 * t, _13 * t, _14 * t,
			_21 * t, _22 * t, _23 * t, _24 * t,
			_31 * t, _32 * t, _33 * t, _34 * t,
			_41 * t, _42 * t, _43 * t, _44 * t);
	}

	Matrix Matrix::operator / (float t) const
	{
		float inv = F_ONE / t;

		return Matrix(
			_11 * inv, _12 * inv, _13 * inv, _14 * inv,
			_21 * inv, _22 * inv, _23 * inv, _24 * inv,
			_31 * inv, _32 * inv, _33 * inv, _34 * inv,
			_41 * inv, _42 * inv, _43 * inv, _44 * inv);
	}

	Matrix operator * (float t, const Matrix& mat)
	{
		return Matrix(
			t * mat._11, t * mat._12, t * mat._13, t * mat._14,
			t * mat._21, t * mat._22, t * mat._23, t * mat._24,
			t * mat._31, t * mat._32, t * mat._33, t * mat._34,
			t * mat._41, t * mat._42, t * mat._43, t * mat._44);
	}

	bool Matrix::operator == (const Matrix& mat) const
	{
		return memcmp(this, &mat, sizeof(Matrix)) == 0;
	}

	bool Matrix::operator != (const Matrix& mat) const
	{
		return memcmp(this, &mat, sizeof(Matrix)) != 0;
	}

	//=============================================================================
	// �֐����F		identity
	// �����F		�P�ʍs�񉻂���
	//=============================================================================
	Matrix& Matrix::identity()
	{
		*this = MTX_IDT;

		return *this;
	}

	//=============================================================================
	// �֐����F		inverse
	// �����F		�t�s�񉻂���
	//				�� ���s�����ꍇ�͌��̍s����ێ�����
	//=============================================================================
	Matrix& Matrix::inverse()
	{
		float det, tmp[3], inv[16];

		tmp[0] = m[2][2] * m[3][3] - m[2][3] * m[3][2];
		tmp[1] = m[1][2] * m[3][3] - m[1][3] * m[3][2];
		tmp[2] = m[1][2] * m[2][3] - m[1][3] * m[2][2];
		inv[0] = m[1][1] * tmp[0] - m[2][1] * tmp[1] + m[3][1] * tmp[2];
		inv[4] = -m[1][0] * tmp[0] + m[2][0] * tmp[1] - m[3][0] * tmp[2];

		tmp[0] = m[1][0] * m[2][1] - m[2][0] * m[1][1];
		tmp[1] = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		tmp[2] = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		inv[8] = m[3][3] * tmp[0] - m[2][3] * tmp[1] + m[1][3] * tmp[2];
		inv[12] = -m[3][2] * tmp[0] + m[2][2] * tmp[1] - m[1][2] * tmp[2];

		det =
			m[0][0] * inv[0] + m[0][1] * inv[4] +
			m[0][2] * inv[8] + m[0][3] * inv[12];

		if(det == F_ZERO)
		{
			return *this;
		}

		tmp[0] = m[2][2] * m[3][3] - m[2][3] * m[3][2];
		tmp[1] = m[0][2] * m[3][3] - m[0][3] * m[3][2];
		tmp[2] = m[0][2] * m[2][3] - m[0][3] * m[2][2];
		inv[1] = -m[0][1] * tmp[0] + m[2][1] * tmp[1] - m[3][1] * tmp[2];
		inv[5] = m[0][0] * tmp[0] - m[2][0] * tmp[1] + m[3][0] * tmp[2];

		tmp[0] = m[0][0] * m[2][1] - m[2][0] * m[0][1];
		tmp[1] = m[3][0] * m[0][1] - m[0][0] * m[3][1];
		tmp[2] = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		inv[9] = -m[3][3] * tmp[0] - m[2][3] * tmp[1] - m[0][3] * tmp[2];
		inv[13] = m[3][2] * tmp[0] + m[2][2] * tmp[1] + m[0][2] * tmp[2];

		tmp[0] = m[1][2] * m[3][3] - m[1][3] * m[3][2];
		tmp[1] = m[0][2] * m[3][3] - m[0][3] * m[3][2];
		tmp[2] = m[0][2] * m[1][3] - m[0][3] * m[1][2];
		inv[2] = m[0][1] * tmp[0] - m[1][1] * tmp[1] + m[3][1] * tmp[2];
		inv[6] = -m[0][0] * tmp[0] + m[1][0] * tmp[1] - m[3][0] * tmp[2];

		tmp[0] = m[0][0] * m[1][1] - m[1][0] * m[0][1];
		tmp[1] = m[3][0] * m[0][1] - m[0][0] * m[3][1];
		tmp[2] = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		inv[10] = m[3][3] * tmp[0] + m[1][3] * tmp[1] + m[0][3] * tmp[2];
		inv[14] = -m[3][2] * tmp[0] - m[1][2] * tmp[1] - m[0][2] * tmp[2];

		tmp[0] = m[1][2] * m[2][3] - m[1][3] * m[2][2];
		tmp[1] = m[0][2] * m[2][3] - m[0][3] * m[2][2];
		tmp[2] = m[0][2] * m[1][3] - m[0][3] * m[1][2];
		inv[3] = -m[0][1] * tmp[0] + m[1][1] * tmp[1] - m[2][1] * tmp[2];
		inv[7] = m[0][0] * tmp[0] - m[1][0] * tmp[1] + m[2][0] * tmp[2];

		inv[11] =
			-m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) +
			m[1][0] * (m[0][1] * m[2][3] - m[0][3] * m[2][1]) -
			m[2][0] * (m[0][1] * m[1][3] - m[0][3] * m[1][1]);

		inv[15] =
			m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
			m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) +
			m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1]);

		det = F_ONE / det;

		unsigned int i, j;

		for(i = 0; i < 4; i++)
		{
			for(j = 0; j < 4; j++)
			{
				m[i][j] = inv[4 * i + j] * det;
			}
		}

		return *this;
	}

	//=============================================================================
	// �֐����F		multiply
	// �����F		�s��̊|�����킹
	//=============================================================================
	Matrix& Matrix::multiply(const Matrix& mat)
	{
		int i, j;

		for(i = 0; i < 4; i++)
		{
			for(j = 0; j < 4; j++)
			{
				this->m[i][j] =
					this->m[i][0] * mat.m[0][j] +
					this->m[i][1] * mat.m[1][j] +
					this->m[i][2] * mat.m[2][j] +
					this->m[i][3] * mat.m[3][j];
			}
		}

		return *this;
	}

	//=============================================================================
	// �֐����F		rot_quaternion
	// �����F		Quaternion�ɂ���]
	//=============================================================================
	Matrix& Matrix::rot_quaternion(const Quaternion& q)
	{
		m[0][0] = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
		m[0][1] = 2.0f * (q.x *q.y + q.z * q.w);
		m[0][2] = 2.0f * (q.x * q.z - q.y * q.w);

		m[1][0] = 2.0f * (q.x * q.y - q.z * q.w);
		m[1][1] = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
		m[1][2] = 2.0f * (q.y *q.z + q.x *q.w);

		m[2][0] = 2.0f * (q.x * q.z + q.y * q.w);
		m[2][1] = 2.0f * (q.y *q.z - q.x *q.w);
		m[2][2] = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);

		return *this;
	}

	//=============================================================================
	// �֐����F		translation
	// �����F		Quaternion�ɂ���]
	//=============================================================================
	Matrix& Matrix::translation(const Vector3& v)
	{
		_41 += v.x;
		_42 += v.y;
		_43 += v.z;

		return *this;
	}

	//=============================================================================
	// �֐����F		rot_yaw_pitch_roll
	// �����F		yaw pitch roll �ɂ���]
	//=============================================================================
	Matrix& Matrix::rot_yaw_pitch_roll(float yaw, float pitch, float roll)
	{
		float sroll, croll, spitch, cpitch, syaw, cyaw;

		sroll = sinf(roll);
		croll = cosf(roll);
		spitch = sinf(pitch);
		cpitch = cosf(pitch);
		syaw = sinf(yaw);
		cyaw = cosf(yaw);

		m[0][0] = sroll * spitch * syaw + croll * cyaw;
		m[0][1] = sroll * cpitch;
		m[0][2] = sroll * spitch * cyaw - croll * syaw;
		m[0][3] = 0.0f;

		m[1][0] = croll * spitch * syaw - sroll * cyaw;
		m[1][1] = croll * cpitch;
		m[1][2] = croll * spitch * cyaw + sroll * syaw;
		m[1][3] = 0.0f;

		m[2][0] = cpitch * syaw;
		m[2][1] = -spitch;
		m[2][2] = cpitch * cyaw;
		m[2][3] = 0.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = F_ONE;

		return *this;
	}

	//=============================================================================
	// �֐����F		rot_yaw_pitch_roll
	// �����F		yaw pitch roll �ɂ���]
	//=============================================================================
	Matrix& Matrix::rot_yaw_pitch_roll(const Vector3 & v)
	{
		return this->rot_yaw_pitch_roll(v.y, v.x, v.z);
	}

	//=============================================================================
	// �֐����F		scaling
	// �����F		�g�k
	//=============================================================================
	Matrix& Matrix::scaling(const Vector3& v)
	{
		_11 = v.x;
		_22 = v.y;
		_33 = v.z;

		return *this;
	}

	//=====================================================================================================================
	// Quaternion
	//=====================================================================================================================

	Quaternion& Quaternion::operator += (const Quaternion& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	Quaternion& Quaternion::operator -= (const Quaternion& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}

	Quaternion& Quaternion::operator *= (float t)
	{
		x *= t;
		y *= t;
		z *= t;
		w *= t;

		return *this;
	}

	Quaternion& Quaternion::operator /= (float t)
	{
		float inv = F_ONE / t;

		x *= inv;
		y *= inv;
		z *= inv;
		w *= inv;

		return *this;
	}

	Quaternion Quaternion::operator / (float t) const
	{
		float inv = F_ONE / t;

		return Quaternion(x * inv, y * inv, z * inv, w * inv);
	}

	bool Quaternion::operator == (const Quaternion& v) const
	{
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	bool Quaternion::operator != (const Quaternion& v) const
	{
		return x != v.x || y != v.y || z != v.z || w != v.w;
	}

	//=============================================================================
	// �֐����F		identity
	// �����F		������
	//=============================================================================
	Quaternion& Quaternion::identity()
	{
		*this = Quaternion();

		return *this;
	}

	//=============================================================================
	// �֐����F		normalize
	// �����F		���K��
	//=============================================================================
	Quaternion& Quaternion::normalize()
	{
		float len = length();

		if(!len)
		{
			x = y = z = w = F_ZERO;

			return *this;
		}

		float inv = F_ONE / len;

		x *= inv;
		y *= inv;
		z *= inv;
		w *= inv;

		return *this;
	}

	//=============================================================================
	// �֐����F		inverse
	// �����F		����������Đ��K������
	//=============================================================================
	Quaternion& Quaternion::inverse()
	{
		float inv = F_ONE / length_sq();

		x = -x * inv;
		y = -y * inv;
		z = -z * inv;
		w = w * inv;

		return *this;
	}

	//=============================================================================
	// �֐����F		multiply
	// �����F		���K��
	//=============================================================================
	Quaternion& Quaternion::multiply(const Quaternion& t)
	{
		x = t.w * x + t.x * w + t.y * z - t.z * y;
		y = t.w * y - t.x * z + t.y * w + t.z * x;
		z = t.w * z + t.x * y - t.y * x + t.z * w;
		w = t.w * w - t.x * x - t.y * y - t.z * z;

		return *this;
	}

	//=============================================================================
	// �֐����F		ln
	// �����F		���R�ΐ�
	//=============================================================================
	Quaternion& Quaternion::ln()
	{
		float tmp = ((w >= F_ONE || w == -F_ONE) ? (F_ONE) : (acosf(w) / sqrtf(F_ONE - w * w)));

		x *= tmp;
		y *= tmp;
		z *= tmp;
		w = F_ZERO;

		return *this;
	}

	//=============================================================================
	// �֐����F		length
	// �����F		�����̎擾
	//=============================================================================
	float Quaternion::length() const
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	//=============================================================================
	// �֐����F		dot
	// �����F		����
	//=============================================================================
	float Quaternion::dot(const Quaternion& t) const
	{
		return this->x * t.x + this->y * t.y + this->z * t.z + this->w * t.w;
	}

	//=============================================================================
	// �֐����F		rot_axis
	// �����F		�x�N�g���ƌX������ Quaternion�쐬
	//=============================================================================
	Quaternion Quaternion::rot_axis(const Vector3& v, const float& t) const
	{
		return Quaternion(v * sinf(t * 0.5f), cos(t * 0.5f));
	}

	//=============================================================================
	// �֐����F		rot_yaw_pitch_roll
	// �����F		yaw, pitch, roll���� Quaternion�쐬
	//=============================================================================
	Quaternion Quaternion::rot_yaw_pitch_roll(const float& yaw, const float& pitch, const float& roll) const
	{
		float s_yaw, c_yaw, s_pitch, c_pitch, s_roll, c_roll;

		s_yaw = sinf(yaw * 0.5f);
		c_yaw = cosf(yaw * 0.5f);
		s_pitch = sinf(pitch * 0.5f);
		c_pitch = cosf(pitch * 0.5f);
		s_roll = sinf(roll * 0.5f);
		c_roll = cosf(roll * 0.5f);

		return Quaternion(
			s_yaw * c_pitch * s_roll + c_yaw * s_pitch * c_roll,
			s_yaw * c_pitch * c_roll - c_yaw * s_pitch * s_roll,
			c_yaw * c_pitch * s_roll - s_yaw * s_pitch * c_roll,
			c_yaw * c_pitch * c_roll + s_yaw * s_pitch * s_roll);
	}

	//=============================================================================
	// �֐����F		rot_matrix
	// �����F		�s�񂩂� Quaternion�쐬
	//=============================================================================
	Quaternion Quaternion::rot_matrix(const Matrix& m, const float& t) const
	{
		float s, inv_s, trace;
		Quaternion rtn;

		trace = m.m[0][0] + m.m[1][1] + m.m[2][2] + F_ONE;

		if(trace > F_ONE)
		{
			s = 2.0f * sqrtf(trace);
			inv_s = F_ONE / s;

			rtn.x = (m.m[1][2] - m.m[2][1]) * inv_s;
			rtn.y = (m.m[2][0] - m.m[0][2]) * inv_s;
			rtn.z = (m.m[0][1] - m.m[1][0]) * inv_s;
			rtn.w = 0.25f * s;

			return rtn;
		}

		int i, maxi = 0;

		for(i = 1; i < 3; i++)
		{
			if(m.m[i][i] > m.m[maxi][maxi])
			{
				maxi = i;
			}
		}

		switch(maxi)
		{
		case 0:
			s = 2.0f * sqrtf(F_ONE + m.m[0][0] - m.m[1][1] - m.m[2][2]);
			inv_s = F_ONE / s;

			rtn.x = 0.25f * s;
			rtn.y = (m.m[0][1] + m.m[1][0]) * inv_s;
			rtn.z = (m.m[0][2] + m.m[2][0]) * inv_s;
			rtn.w = (m.m[1][2] - m.m[2][1]) * inv_s;
			break;

		case 1:
			s = 2.0f * sqrtf(F_ONE + m.m[1][1] - m.m[0][0] - m.m[2][2]);
			inv_s = F_ONE / s;

			rtn.x = (m.m[0][1] + m.m[1][0]) * inv_s;
			rtn.y = 0.25f * s;
			rtn.z = (m.m[1][2] + m.m[2][1]) * inv_s;
			rtn.w = (m.m[2][0] - m.m[0][2]) * inv_s;
			break;

		case 2:
			s = 2.0f * sqrtf(F_ONE + m.m[2][2] - m.m[0][0] - m.m[1][1]);
			inv_s = F_ONE / s;

			rtn.x = (m.m[0][2] + m.m[2][0]) * inv_s;
			rtn.y = (m.m[1][2] + m.m[2][1]) * inv_s;
			rtn.z = 0.25f * s;
			rtn.w = (m.m[0][1] - m.m[1][0]) * inv_s;
			break;
		}

		return rtn;
	}

	//=============================================================================
	// �֐����F		add_diff
	// �����F
	//=============================================================================
	Quaternion Quaternion::add_diff(const Quaternion& q, const float& add) const
	{
		return Quaternion(*this + q * add);
	}

	//=============================================================================
	// �֐����F		lerp
	// �����F		const Quaternion& q	�Quaternion
	// �����F		float t				����
	// �����F		�Ăяo��(this)�@�Ɗ(v)�@�̊Ԃ�
	//				����(t)�@�ɂ��A���`��Ԃ���
	//=============================================================================
	Quaternion Quaternion::lerp(const Quaternion& q, const float& t) const
	{
		return *this + (q - *this) * t;
	}

	//=============================================================================
	// �֐����F		slerp
	// �����F		���ʐ��`���
	//=============================================================================
	Quaternion Quaternion::slerp(const Quaternion& q, const float& t) const
	{
		float doted, inv_t, temp = t;

		inv_t = F_ONE - temp;
		doted = dot(q);

		if(doted < F_ZERO)
		{
			temp *= -1;
			doted *= -1;
		}

		if(F_ONE - doted > 0.001f)
		{
			float theta = acosf(doted);
			float inv_sin = F_ONE / sin(theta);

			inv_t = sinf(theta * inv_t) * inv_sin;
			temp = sinf(theta * temp) * inv_sin;
		}

		return Quaternion(*this * inv_t + q * temp);
	}

	//=============================================================================
	// �֐����F		is_angle_sharp_by_3pt
	// �����F		3�_�̐����p�x���s�p��
	//=============================================================================
	bool is_angle_sharp_by_3pt(const Vector3& p1, const Vector3& p2, const Vector3& p3)
	{
		return (p1 - p2).is_angle_sharp_by_vec(p3 - p2);
	}

	//=============================================================================
	// �֐����F		vec3_catmullrom
	// �����F		Vector3& v0
	// �����F		Vector3& v1
	// �����F		Vector3& v2
	// �����F		Vector3& v3
	// �����F		float s
	// �����F		Catmull-Rom�X�v���C���Ȑ��̎擾(s: 0 �` 1�@���̋O��)
	//=============================================================================
	Vector3 vec3_catmullrom(
		const Vector3& v0, const Vector3& v1,
		const Vector3& v2, const Vector3& v3, float s)
	{
		return	(v1 * 2.0f + (v2 - v0) * s
			+ (v0 * 2.0f - v1 * 5.0f + v2 * 4.0f - v3) * s * s
			+ (v3 - v2 * 3.0f + v1 * 3.0f - v0) * s * s * s) * 0.5f;
	}

	//=============================================================================
	// �֐����F		vec3_hermite
	// �����F		Vector3& p0		�J�n�_
	// �����F		Vector3& v0		�J�n�_�ɂ�����x�N�g��
	// �����F		Vector3& p1		�I���_
	// �����F		Vector3& v1		�I���_�ɂ�����x�N�g��
	// �����F		float s
	// �����F		Hermite�Ȑ��̎擾(s: 0 �` 1�@���̋O��)
	//=============================================================================
	Vector3 vec3_hermite(
		const Vector3& p0, const Vector3& v0,
		const Vector3& p1, const Vector3& v1, float s)
	{
		float h1, h2, h3, h4;

		h1 = 2.0f * s * s * s - 3.0f * s * s + 1.0f;
		h2 = s * s * s - 2.0f * s * s + s;
		h3 = -2.0f * s * s * s + 3.0f * s * s;
		h4 = s * s * s - s * s;

		return (p0 * h1 + v0 * h2 + p1 * h3 + v1 * h4);
	}

	//=============================================================================
	// �֐����F		quat_squad
	// �����F		const Quaternion& q1	����_1
	// �����F		const Quaternion& q2	����_2
	// �����F		const Quaternion& q3	����_3
	// �����F		const Quaternion& q4	����_4
	// �����F		const float & t			�o�߈ʒu(0.0 �` F_ONE)
	// �����F		���ʓ񎟕��
	//=============================================================================
	Quaternion quat_squad(const Quaternion & q1, const Quaternion & q2, const Quaternion & q3, const Quaternion & q4, const float & t)
	{
		return (q1.slerp(q4, t)).slerp(q2.slerp(q3, t), 2.0f * t * (1.0f - t));
	}
}

