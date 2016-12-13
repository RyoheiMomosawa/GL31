//=====================================================================================================================
//	�t�@�C����:	UtlCommonLib.h
//	�쐬��:		�����O�X
//=====================================================================================================================
//	�X�V����
//		-ver 1.00	2016 / 06 / 27	�����O�X
//=====================================================================================================================
//	�t�@�C���̐���
//				���ʒ萔�E�֐��Q
//=====================================================================================================================
#pragma once

//=====================================================================================================================
//�@���@�C���N���[�h�@��
//=====================================================================================================================
#include <cmath>
#include <vector>
#include <string>
#include <sstream>

//====================================
//�@���O��ԁFt_lib
//====================================
namespace t_lib
{
	//====================================
	//�@�u������
	//====================================
	static const float CALC_EPS = 1e-7f;

	static const float PI = 3.141592654f;
	static const float PI2 = PI * 2;

	static const float INV_PI = 0.318309886f;
	static const float INV_SQRT2 = 0.707106781f;
	static const float INV_180 = 0.017453292f;
	static const float DIV180_BY_PI = 57.295779513f;
	static const float DIVPI_BY_180 = 0.0174444444f;

	static const float INV_2 = 0.5f;
	static const float INV_4 = 0.25f;
	static const float INV_8 = 0.125f;
	static const float INV_16 = 0.0625f;
	static const float INV_32 = 0.03125f;
	static const float INV_64 = 0.015625f;
	static const float INV_128 = 0.0078125f;
	static const float INV_256 = 0.00390625f;
	static const float INV_512 = 0.001953125f;
	static const float INV_1024 = 0.0009765625f;
	static const float INV_2048 = 0.00048828125f;
	static const float INV_4096 = 0.000244140625f;
	static const float INV_8192 = 0.0001220703125f;
	static const float INV_16384 = 0.00006103515625f;
	static const float INV_32768 = 0.000030517578125f;
	static const float INV_65536 = 0.0000152587890625f;

	//�ꎞ�I�u�W�F�N�g���p
	static const float F_ZERO = 0.0f;
	static const float F_ONE = 1.0f;
	static const unsigned char B_ZERO = 0;

	//====================================
	//�@����(�C�����C���֐�)
	//====================================

	//=============================================================================
	// �֐����F		power2_mod
	// �����F		int value	��]��������l
	// �����F		int pow		��]��l(2�̗ݏ����)
	// �����F		2�̗ݏ�̏�](����)
	//=============================================================================
	inline int power2_mod(int value, int pow) { return (value & (pow - 1)); }

	//=============================================================================
	// �֐����F		is_odd
	// �����F		�����
	//=============================================================================
	inline bool is_odd(int value) { return (value & 1); }

	//=============================================================================
	// �֐����F		is_in
	// �����F		value	�l
	// �����F		low		�ŏ��l
	// �����F		hi		�ő�l
	// �����F		�͈͓�����		�ilow <= value <= hi�j
	//=============================================================================
	inline bool is_in(float value, float low, float hi) { return (low <= value && value <= hi); }

	//=============================================================================
	// �֐����F		is_out
	// �����F		value	�l
	// �����F		low		�ŏ��l
	// �����F		hi		�ő�l
	// �����F		�͈͊O����		�ivalue < low or hi < value�j
	//=============================================================================
	inline bool is_out(float value, float low, float hi) { return (value < low || hi < value); }

	//=============================================================================
	// �֐����F		is_in
	// �����F		value	�l
	// �����F		low		�ŏ��l
	// �����F		hi		�ő�l
	// �����F		�͈͓�����		�ilow <= value <= hi�j
	//=============================================================================
	template<class T>
	inline bool is_in(T value, T low, T hi) { return ((unsigned int)(value - low) <= (hi - low)); }

	//=============================================================================
	// �֐����F		is_out
	// �����F		value	�l
	// �����F		low		�ŏ��l
	// �����F		hi		�ő�l
	// �����F		�͈͊O����		�ivalue < low or hi < value�j
	//=============================================================================
	template<class T>
	inline bool is_out(T value, T low, T hi) { return ((unsigned int)(value - low) > (hi - low)); }

	//====================================
	//�@�v�Z
	//====================================

	//=============================================================================
	// �֐����F		clamp_range
	// �����F		�͈͓��Ɏ��߂�(�ŏ�,�@�ő�)
	//=============================================================================
	template <class T>
	inline void clamp_range(T& value, T min_val, T max_val)
	{
		T maxed = (max_val < value) ? max_val : value;
		value = (min_val > maxed) ? min_val : maxed;
	}

	//=============================================================================
	// �֐����F		clamp_max
	// �����F		�͈͓��Ɏ��߂�(�ő�̂�)
	//=============================================================================
	template <class T>
	inline void clamp_max(T& value, T max_val) { value = (max_val < value) ? max_val : value; }

	//=============================================================================
	// �֐����F		clamp_min
	// �����F		�͈͓��Ɏ��߂�(�ŏ��̂�)
	//=============================================================================
	template <class T>
	inline void clamp_min(T& value, T min_val) { value = (min_val > value) ? min_val : value; }

	//=============================================================================
	// �֐����F		close_to_value
	// �����F		value	���̐��l
	// �����F		scale	������
	// �����F		to		�ڕW�l
	// �����F		���̒l��ڕW�l�ɁA�������ŋ߂Â���
	//=============================================================================
	template <class T>
	inline T close_to_value(T& value, float scale = F_ZERO, T to = F_ZERO)
	{
		value += (to - value) * scale;
	}

	//=============================================================================
	// �֐����F		lost_by_eps
	// �����F		double value	���̐��l
	// �����F		double eps		�덷���e�͈�
	// �����F		double to		�ڕW�l
	// �����F		�ڕW�l�Ƃ̍������덷���e�͈͂ɂȂ�����A�ڕW�l��������
	//=============================================================================
	inline void lost_by_eps(double& value, double eps = CALC_EPS, double to = F_ZERO)
	{
		if(fabs(value - to) < eps)
		{
			value = to;
		}
	}

	//=============================================================================
	// �֐����F		lost_by_eps
	// �����F		float value		���̐��l
	// �����F		float eps		�덷���e�͈�
	// �����F		float to		�ڕW�l
	// �����F		�ڕW�l�Ƃ̍������덷���e�͈͂ɂȂ�����A�ڕW�l��������
	//=============================================================================
	inline void lost_by_eps(float& value, float eps = CALC_EPS, float to = F_ZERO)
	{
		if(fabs(value - to) < eps)
		{
			value = to;
		}
	}

	//=============================================================================
	// �֐����F		lerp_constant
	// �����F		T value		���̒l
	// �����F		T to		�ڕW�l
	// �����F		float t		����
	// �����F		���̒l���A�ڕW�l�֕ω�������(0 �` 1)�@���̊�����
	//=============================================================================
	template<class T>
	inline T lerp_constant(T value, T to, float t)
	{
		return value + (to - value) * t;
	}

	//=============================================================================
	// �֐����F		lerp_slow_to_fast
	// �����F		T value		���̒l
	// �����F		T to		�ڕW�l
	// �����F		float t		����
	// �����F		���̒l���A�ڕW�l�֕ω�������(0 �` 1)�@������聨�}�㏸
	//=============================================================================
	template<class T>
	inline T lerp_slow_to_fast(T value, T to, float t)
	{
		return value + (to - value) * (t * t);
	}

	//=============================================================================
	// �֐����F		lerp_fast_to_slow
	// �����F		T value		���̒l
	// �����F		T to		�ڕW�l
	// �����F		float t		����
	// �����F		���̒l���A�ڕW�l�֕ω�������(0 �` 1)�@�}�㏸���������
	//=============================================================================
	template<class T>
	inline T lerp_fast_to_slow(T value, T to, float t)
	{
		return value + (to - value) * (t * (2 - t));
	}

	//=============================================================================
	// �֐����F		lerp_slow_fast_slow
	// �����F		T value		���̒l
	// �����F		T to		�ڕW�l
	// �����F		float t		����
	// �����F		���̒l���A�ڕW�l�֕ω�������(0 �` 1)�@������聨�}�㏸���������
	//=============================================================================
	template<class T>
	inline T lerp_slow_fast_slow(T value, T to, float t)
	{
		return value + (to - value) * (t * t * (3 - 2 * t));
	}

	//=============================================================================
	// �֐����F		get_range_of_coswave
	// �����F		int value		�W��
	// �����F		from to			���̒l�@�ڕW�l
	// �����F		float interval	�ǂ̂��炢�ŏz���邩
	// �����F		���̒l�E�ڕW�l�̊Ԃ� interval �Ԋu�ōs��������
	//
	// ��j 1�b�Ԋu�Ł@10�`100���s��������
	// 				get_range_of_coswave(value, 10, 100, 1/60);
	//=============================================================================
	template <class T>
	inline T get_range_of_coswave(int value, T from, T to, float interval)
	{
		return static_cast<T>(from + (to - from) * (cos(PI * value * interval) + 1) * 0.5f);
	}

	//=============================================================================
	// �֐����F		pi_to_degree
	// �����F		radian����x���@��
	//=============================================================================
	inline float pi_to_degree(float pi) { return pi * DIV180_BY_PI; }

	//=============================================================================
	// �֐����F		degree_to_pi
	// �����F		radian����x���@��
	//=============================================================================
	inline float degree_to_pi(float degree) { return degree * DIVPI_BY_180; }

	//=============================================================================
	// �֐����F		degree_to_pi
	// �����F		radian����x���@��
	//=============================================================================
	const char* printf_here(const char *fmt, ...);

	//=============================================================================
	// �֐����F		get_split_string
	// �����F		const std::string &str	���̕�����
	// �����F		char sep				��������
	// �����F		���������ŋ�؂�ꂽ�@������Q���擾
	//=============================================================================
	inline std::vector<std::string> get_split_string(const std::string &str, char sep)
	{
		std::vector<std::string> v;
		std::stringstream ss(str);
		std::string buffer;

		while(std::getline(ss, buffer, sep))
		{
			v.push_back(buffer);
		}

		return v;
	}
}

//====================================
//�@using namespece �F t_lib
//====================================
//using namespace t_lib;

