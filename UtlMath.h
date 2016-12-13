//=====================================================================================================================
//	ファイル名:	UtlMath.h
//	作成者:		高橋弘宜
//=====================================================================================================================
//	更新履歴
//		-ver 1.00	2016 / 06 / 27	高橋弘宜
//		-ver 1.01	2016 / 07 / 01	高橋弘宜	交差点取得関数に std::tuple を使用
//		-ver 1.02	2016 / 07 / 16	高橋弘宜	直線・線分・球などをUtlShapeに分離
//=====================================================================================================================
//	ファイルの説明
//				Vector, Matrix など物理・数学系
//=====================================================================================================================
#pragma once

//====================================
//　※　インクルード　※
//====================================
#include <tuple>
#include "UtlCommonLib.h"

//====================================
//　using namespece ： t_lib
//====================================
//using namespace t_lib;

//====================================
//　名前空間：t_lib
//====================================
namespace t_lib
{
	class Vector2;
	class Vector3;
	class Vector4;
	class Matrix;
	class Quaternion;

	//====================================
	// Vector2
	//====================================
	class Vector2
	{
	public:
		Vector2() : x(F_ZERO), y(F_ZERO) {}
		Vector2(float tx, float ty) : x(tx), y(ty) {}

		//キャスト
		operator float* () { return (float*)&x; }
		operator const float* () const { return (const float*)&x; }

		//複合代入演算子
		Vector2& operator += (const Vector2&);
		Vector2& operator -= (const Vector2&);
		Vector2& operator *= (float);
		Vector2& operator /= (float);

		//添字演算子
		Vector2 operator + () const { return *this; }
		Vector2 operator - () const { return Vector2(-x, -y); }

		//単項演算子
		Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
		Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
		Vector2 operator * (float t) const { return Vector2(x * t, y * t); }
		Vector2 operator / (float t) const;

		friend Vector2 operator * (float t, const Vector2& v) { return Vector2(t * v.x, t * v.y); }

		//比較演算子
		bool operator == (const Vector2& v) const { return x == v.x && y == v.y; }
		bool operator != (const Vector2& v) const { return x != v.x || y != v.y; }

		//====================================
		// Utl関数群
		//====================================
		Vector2& initialize();
		Vector2& normalize();
		Vector2& set_length(float f) { return normalize() *= f; }

		float length_sq() const { return x * x + y * y; }
		float length() const;
		float cross(const Vector2& v) const { return x * v.y - y * v.x; }
		float dot(const Vector2& v) const { return x * v.x + y * v.y; }
		Vector2 lerp(const Vector2&, float) const;

	public:
		union
		{
			struct { float x, y; };
			float p[2];
		};
	};

	//====================================
	// Vector3
	//====================================
	class Vector3
	{
	public:
		Vector3() : x(F_ZERO), y(F_ZERO), z(F_ZERO) {}
		Vector3(float tx, float ty, float tz) : x(tx), y(ty), z(tz) {}
		Vector3(const Vector2& v, float t = F_ZERO) : x(v.x), y(v.y), z(t) {}

		//キャスト
		operator float* () { return (float*)&x; }
		operator const float* () const { return (const float*)&x; }

		//複合代入演算子
		Vector3& operator += (const Vector3&);
		Vector3& operator -= (const Vector3&);
		Vector3& operator *= (float);
		Vector3& operator /= (float);

		//添字演算子
		Vector3 operator + () const { return *this; }
		Vector3 operator - () const { return Vector3(-x, -y, -z); }

		//単項演算子
		Vector3 operator + (const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
		Vector3 operator - (const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
		Vector3 operator + (float t) const { return Vector3(x + t, y + t, z + t); }
		Vector3 operator - (float t) const { return Vector3(x - t, y - t, z - t); }
		Vector3 operator * (float t) const { return Vector3(x * t, y * t, z * t); }
		Vector3 operator / (float t) const;

		friend Vector3 operator * (float t, const Vector3& v) { return Vector3(t * v.x, t * v.y, t * v.z); }

		//比較演算子
		bool operator == (const Vector3& v) const { return x == v.x && y == v.y && z == v.z; }
		bool operator != (const Vector3& v) const { return x != v.x || y != v.y || z != v.z; }

		//====================================
		// Utl関数群
		//====================================
		Vector3& initialize();
		Vector3& normalize();
		Vector3& set_length(float f) { return normalize() *= f; }

		float length_sq() const { return x * x + y * y + z * z; }
		float length() const;
		Vector3 get_normalized() const;
		float angle_by_vec3(const Vector3& v) const;
		bool is_vertical(const Vector3& v) const;
		bool is_parallel(const Vector3& v) const;
		bool is_angle_sharp_by_vec(const Vector3& v) const;
		Vector3 along(const Vector3& nor) const;
		Vector3 reflect(const Vector3& nor) const;
		Vector3 cross(const Vector3&) const;
		float dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
		Vector3 lerp(const Vector3&, float) const;
		Vector4 transform(const Matrix&) const;
		Vector3 transform_coord(const Matrix&) const;
		Vector3 transform_normal(const Matrix&) const;

		

	public:
		union
		{
			struct { float x, y, z; };
			float p[3];
		};
	};

	//====================================
	// Vector4
	//====================================
	class Vector4
	{
	public:
		Vector4() : x(F_ZERO), y(F_ZERO), z(F_ZERO), w(F_ZERO) {}
		Vector4(float tx, float ty, float tz, float tw) : x(tx), y(ty), z(tz), w(tw) {}
		Vector4(const Vector2& v, float tz = F_ZERO, float tw = F_ZERO);
		Vector4(const Vector3& v, float tw = F_ZERO) : x(v.x), y(v.y), z(v.z), w(tw) {}

		//キャスト
		operator float* () { return (float*)&x; }
		operator const float* () const { return (const float*)&x; }

		//複合代入演算子
		Vector4& operator += (const Vector4&);
		Vector4& operator -= (const Vector4&);
		Vector4& operator *= (float);
		Vector4& operator /= (float);

		//添字演算子
		Vector4 operator + () const { return *this; }
		Vector4 operator - () const { return Vector4(-x, -y, -z, -w); }

		//単項演算子
		Vector4 operator + (const Vector4& v) const { return Vector4(x + v.x, y + v.y, z + v.z, w + v.w); }
		Vector4 operator - (const Vector4& v) const { return Vector4(x - v.x, y - v.y, z - v.z, w - v.w); }
		Vector4 operator * (float t) const { return Vector4(x * t, y * t, z * t, w * t); }
		Vector4 operator / (float) const;

		friend Vector4 operator *(float t, const Vector4& v) { return Vector4(t * v.x, t * v.y, t * v.z, t * v.w); }

		//比較演算子
		bool operator == (const Vector4&) const;
		bool operator != (const Vector4&) const;

		//====================================
		// Utl関数群
		//====================================
		Vector4& initialize();
		Vector4& normalize();
		Vector4& set_length(float f) { return normalize() *= f; }

		float length_sq() const { return x * x + y * y + z * z + w * w; }
		float length() const;
		float dot(const Vector4&) const;
		Vector4 lerp(const Vector4&, float) const;

	public:
		union
		{
			struct { float x, y, z, w; };
			float p[4];
		};
	};

	//====================================
	// Matrix
	//====================================
	class Matrix
	{
	public:
		Matrix() :
			_11(F_ONE), _12(F_ZERO), _13(F_ZERO), _14(F_ZERO),
			_21(F_ZERO), _22(F_ONE), _23(F_ZERO), _24(F_ZERO),
			_31(F_ZERO), _32(F_ZERO), _33(F_ONE), _34(F_ZERO),
			_41(F_ZERO), _42(F_ZERO), _43(F_ZERO), _44(F_ONE)
		{}
		Matrix(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44);

		//access grants
		float& operator () (unsigned char y, unsigned char x) { return m[y][x]; }
		float  operator () (unsigned char y, unsigned char x) const { return m[y][x]; }

		//キャスト
		operator float* () { return (float*)&_11; }
		operator const float* () const { return (const float*)&_11; }

		//複合代入演算子
		Matrix& operator *= (const Matrix&);
		Matrix& operator += (const Matrix&);
		Matrix& operator -= (const Matrix&);
		Matrix& operator *= (float);
		Matrix& operator /= (float);

		//添字演算子
		Matrix operator + () const { return *this; }
		Matrix operator - () const;

		//単項演算子
		Matrix operator * (const Matrix&) const;
		Matrix operator + (const Matrix&) const;
		Matrix operator - (const Matrix&) const;
		Matrix operator * (float) const;
		Matrix operator / (float) const;

		friend Matrix operator * (float, const Matrix&);

		//比較演算子
		bool operator == (const Matrix&) const;
		bool operator != (const Matrix&) const;

		//====================================
		// Utl関数群
		//====================================
		Matrix& identity();
		Matrix& inverse();
		Matrix& multiply(const Matrix&);
		Matrix& rot_quaternion(const Quaternion& q);
		Matrix& translation(const Vector3& v);
		Matrix& rot_yaw_pitch_roll(float yaw, float pitch, float roll);
		Matrix& rot_yaw_pitch_roll(const Vector3& v);
		Matrix& scaling(const Vector3& v);

	public:
		union
		{
			struct
			{
				float	_11, _12, _13, _14;
				float	_21, _22, _23, _24;
				float	_31, _32, _33, _34;
				float	_41, _42, _43, _44;

			};

			float m[4][4];
		};
	};

	//====================================
	// Quaternion
	//====================================
	class Quaternion
	{
	public:
		Quaternion() : x(F_ZERO), y(F_ZERO), z(F_ZERO), w(F_ONE) {}
		Quaternion(float tx, float ty, float tz, float tw) : x(tx), y(ty), z(tz), w(tw) {}
		Quaternion(const Vector3& v, float tw = 1.0f) : x(v.x), y(v.y), z(v.z), w(tw) {}
		Quaternion(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

		//キャスト
		operator float* () { return (float*)&x; }
		operator const float* () const { return (const float*)&x; }

		//複合代入演算子
		Quaternion& operator += (const Quaternion&);
		Quaternion& operator -= (const Quaternion&);
		Quaternion& operator *= (float);
		Quaternion& operator *= (const Quaternion& t) { return this->multiply(t); }
		Quaternion& operator /= (float);

		//添字演算子
		Quaternion operator + () const { return *this; }
		Quaternion operator - () const { return Quaternion(-x, -y, -z, -w); }

		//単項演算子
		Quaternion operator + (const Quaternion& t) const { return Quaternion(x + t.x, y + t.y, z + t.z, w + t.w); }
		Quaternion operator - (const Quaternion& t) const { return Quaternion(x - t.x, y - t.y, z - t.z, w - t.w); }
		Quaternion operator * (float t) const { return Quaternion(x * t, y * t, z * t, w * t); }
		Quaternion operator * (const Quaternion& t) const { return Quaternion(*this).multiply(t); }
		Quaternion operator / (float) const;

		friend Quaternion operator * (float t, const Quaternion& q) { return Quaternion(t * q.x, t * q.y, t * q.z, t * q.w); }

		//比較演算子
		bool operator == (const Quaternion&) const;
		bool operator != (const Quaternion&) const;

		//====================================
		// Utl関数群
		//====================================
		Quaternion& identity();
		Quaternion& normalize();
		Quaternion& inverse();
		Quaternion& multiply(const Quaternion&);
		Quaternion& ln();

		bool is_identity() const { return *this == Quaternion(); }
		float length_sq() const { return x * x + y * y + z * z + w * w; }
		float length() const;
		float dot(const Quaternion&) const;
		Quaternion rot_axis(const Vector3& v, const float& t) const;
		Quaternion rot_yaw_pitch_roll(const float& yaw, const float& pitch, const float& roll) const;
		Quaternion rot_matrix(const Matrix& m, const float& t) const;
		Quaternion add_diff(const Quaternion& q, const float& add) const;
		Quaternion lerp(const Quaternion&, const float& t) const;
		Quaternion slerp(const Quaternion& q, const float& t) const;

	public:
		union
		{
			struct { float x, y, z, w; };
			float p[4];
		};
	};

	static const Vector2 VEC2_ZERO	= Vector2();
	static const Vector3 VEC3_ZERO	= Vector3();
	static const Vector4 VEC4_ZERO	= Vector4();
	static const Matrix MTX_IDT		= Matrix();

	static const Vector3 VEC3_ONE	= { 1.0f,			1.0f,		1.0f };

	static const Vector3 VEC3_RIGHT	= { 1.0f,			0.0f,		0.0f };
	static const Vector3 VEC3_LEFT	= { -1.0f,			0.0f,		0.0f };
	static const Vector3 VEC3_UP	= { 0.0f,			1.0f,		0.0f };
	static const Vector3 VEC3_DOWN	= { 0.0f,			-1.0f,		0.0f };
	static const Vector3 VEC3_FRONT	= { 0.0f,			0.0f,		1.0f };
	static const Vector3 VEC3_BACK	= { 0.0f,			0.0f,		-1.0f };
	
	static const Vector3 VEC3_RF	= { INV_SQRT2,		0.0f,		INV_SQRT2 };
	static const Vector3 VEC3_RB	= { INV_SQRT2,		0.0f,		-INV_SQRT2 };
	static const Vector3 VEC3_LF	= { -INV_SQRT2,		0.0f,		INV_SQRT2 };
	static const Vector3 VEC3_LB	= { -INV_SQRT2,		0.0f,		-INV_SQRT2 };

	static const Vector2 VEC2_RIGHT	= { 1.0f,			0.0f };
	static const Vector2 VEC2_LEFT	= { -1.0f,			0.0f };
	static const Vector2 VEC2_UP	= { 0.0f,			1.0f };
	static const Vector2 VEC2_DOWN	= { 0.0f,			-1.0f };

	static const Vector2 VEC2_RU	= { INV_SQRT2,		INV_SQRT2 };
	static const Vector2 VEC2_RD	= { INV_SQRT2,		-INV_SQRT2 };
	static const Vector2 VEC2_LU	= { -INV_SQRT2,		INV_SQRT2 };
	static const Vector2 VEC2_LD	= { -INV_SQRT2,		-INV_SQRT2 };

	// p1 p2 p3 の成す角が鋭角か
	bool is_angle_sharp_by_3pt(const Vector3& p1, const Vector3& p2, const Vector3& p3);

	//Catmull-Romスプライン曲線
	Vector3 vec3_catmullrom(
		const Vector3& v0, const Vector3& v1,
		const Vector3& v2, const Vector3& v3, float s);

	//エルミート線形補間
	Vector3 vec3_hermite(
		const Vector3& p0, const Vector3& v0,
		const Vector3& p1, const Vector3& v1, float s);

	//球面二次補間
	Quaternion quat_squad(
		const Quaternion & q1, const Quaternion & q2,
		const Quaternion & q3, const Quaternion & q4, const float & t);
}