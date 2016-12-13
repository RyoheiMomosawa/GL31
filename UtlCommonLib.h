//=====================================================================================================================
//	ファイル名:	UtlCommonLib.h
//	作成者:		高橋弘宜
//=====================================================================================================================
//	更新履歴
//		-ver 1.00	2016 / 06 / 27	高橋弘宜
//=====================================================================================================================
//	ファイルの説明
//				共通定数・関数群
//=====================================================================================================================
#pragma once

//=====================================================================================================================
//　※　インクルード　※
//=====================================================================================================================
#include <cmath>
#include <vector>
#include <string>
#include <sstream>

//====================================
//　名前空間：t_lib
//====================================
namespace t_lib
{
	//====================================
	//　置き換え
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

	//一時オブジェクト回避用
	static const float F_ZERO = 0.0f;
	static const float F_ONE = 1.0f;
	static const unsigned char B_ZERO = 0;

	//====================================
	//　判定(インライン関数)
	//====================================

	//=============================================================================
	// 関数名：		power2_mod
	// 引数：		int value	剰余をかける値
	// 引数：		int pow		剰余基準値(2の累乗限定)
	// 説明：		2の累乗の剰余(高速)
	//=============================================================================
	inline int power2_mod(int value, int pow) { return (value & (pow - 1)); }

	//=============================================================================
	// 関数名：		is_odd
	// 説明：		奇数判定
	//=============================================================================
	inline bool is_odd(int value) { return (value & 1); }

	//=============================================================================
	// 関数名：		is_in
	// 引数：		value	値
	// 引数：		low		最小値
	// 引数：		hi		最大値
	// 説明：		範囲内判定		（low <= value <= hi）
	//=============================================================================
	inline bool is_in(float value, float low, float hi) { return (low <= value && value <= hi); }

	//=============================================================================
	// 関数名：		is_out
	// 引数：		value	値
	// 引数：		low		最小値
	// 引数：		hi		最大値
	// 説明：		範囲外判定		（value < low or hi < value）
	//=============================================================================
	inline bool is_out(float value, float low, float hi) { return (value < low || hi < value); }

	//=============================================================================
	// 関数名：		is_in
	// 引数：		value	値
	// 引数：		low		最小値
	// 引数：		hi		最大値
	// 説明：		範囲内判定		（low <= value <= hi）
	//=============================================================================
	template<class T>
	inline bool is_in(T value, T low, T hi) { return ((unsigned int)(value - low) <= (hi - low)); }

	//=============================================================================
	// 関数名：		is_out
	// 引数：		value	値
	// 引数：		low		最小値
	// 引数：		hi		最大値
	// 説明：		範囲外判定		（value < low or hi < value）
	//=============================================================================
	template<class T>
	inline bool is_out(T value, T low, T hi) { return ((unsigned int)(value - low) > (hi - low)); }

	//====================================
	//　計算
	//====================================

	//=============================================================================
	// 関数名：		clamp_range
	// 説明：		範囲内に収める(最小,　最大)
	//=============================================================================
	template <class T>
	inline void clamp_range(T& value, T min_val, T max_val)
	{
		T maxed = (max_val < value) ? max_val : value;
		value = (min_val > maxed) ? min_val : maxed;
	}

	//=============================================================================
	// 関数名：		clamp_max
	// 説明：		範囲内に収める(最大のみ)
	//=============================================================================
	template <class T>
	inline void clamp_max(T& value, T max_val) { value = (max_val < value) ? max_val : value; }

	//=============================================================================
	// 関数名：		clamp_min
	// 説明：		範囲内に収める(最小のみ)
	//=============================================================================
	template <class T>
	inline void clamp_min(T& value, T min_val) { value = (min_val > value) ? min_val : value; }

	//=============================================================================
	// 関数名：		close_to_value
	// 引数：		value	元の数値
	// 引数：		scale	減衰率
	// 引数：		to		目標値
	// 説明：		元の値を目標値に、減衰率で近づける
	//=============================================================================
	template <class T>
	inline T close_to_value(T& value, float scale = F_ZERO, T to = F_ZERO)
	{
		value += (to - value) * scale;
	}

	//=============================================================================
	// 関数名：		lost_by_eps
	// 引数：		double value	元の数値
	// 引数：		double eps		誤差許容範囲
	// 引数：		double to		目標値
	// 説明：		目標値との差分が誤差許容範囲になったら、目標値を代入する
	//=============================================================================
	inline void lost_by_eps(double& value, double eps = CALC_EPS, double to = F_ZERO)
	{
		if(fabs(value - to) < eps)
		{
			value = to;
		}
	}

	//=============================================================================
	// 関数名：		lost_by_eps
	// 引数：		float value		元の数値
	// 引数：		float eps		誤差許容範囲
	// 引数：		float to		目標値
	// 説明：		目標値との差分が誤差許容範囲になったら、目標値を代入する
	//=============================================================================
	inline void lost_by_eps(float& value, float eps = CALC_EPS, float to = F_ZERO)
	{
		if(fabs(value - to) < eps)
		{
			value = to;
		}
	}

	//=============================================================================
	// 関数名：		lerp_constant
	// 引数：		T value		元の値
	// 引数：		T to		目標値
	// 引数：		float t		割合
	// 説明：		元の値を、目標値へ変化させる(0 ～ 1)　一定の割合で
	//=============================================================================
	template<class T>
	inline T lerp_constant(T value, T to, float t)
	{
		return value + (to - value) * t;
	}

	//=============================================================================
	// 関数名：		lerp_slow_to_fast
	// 引数：		T value		元の値
	// 引数：		T to		目標値
	// 引数：		float t		割合
	// 説明：		元の値を、目標値へ変化させる(0 ～ 1)　ゆっくり→急上昇
	//=============================================================================
	template<class T>
	inline T lerp_slow_to_fast(T value, T to, float t)
	{
		return value + (to - value) * (t * t);
	}

	//=============================================================================
	// 関数名：		lerp_fast_to_slow
	// 引数：		T value		元の値
	// 引数：		T to		目標値
	// 引数：		float t		割合
	// 説明：		元の値を、目標値へ変化させる(0 ～ 1)　急上昇→ゆっくり
	//=============================================================================
	template<class T>
	inline T lerp_fast_to_slow(T value, T to, float t)
	{
		return value + (to - value) * (t * (2 - t));
	}

	//=============================================================================
	// 関数名：		lerp_slow_fast_slow
	// 引数：		T value		元の値
	// 引数：		T to		目標値
	// 引数：		float t		割合
	// 説明：		元の値を、目標値へ変化させる(0 ～ 1)　ゆっくり→急上昇→ゆっくり
	//=============================================================================
	template<class T>
	inline T lerp_slow_fast_slow(T value, T to, float t)
	{
		return value + (to - value) * (t * t * (3 - 2 * t));
	}

	//=============================================================================
	// 関数名：		get_range_of_coswave
	// 引数：		int value		係数
	// 引数：		from to			元の値　目標値
	// 引数：		float interval	どのくらいで循環するか
	// 説明：		元の値・目標値の間を interval 間隔で行き来する
	//
	// 例） 1秒間隔で　10～100を行き来する
	// 				get_range_of_coswave(value, 10, 100, 1/60);
	//=============================================================================
	template <class T>
	inline T get_range_of_coswave(int value, T from, T to, float interval)
	{
		return static_cast<T>(from + (to - from) * (cos(PI * value * interval) + 1) * 0.5f);
	}

	//=============================================================================
	// 関数名：		pi_to_degree
	// 説明：		radianから度数法へ
	//=============================================================================
	inline float pi_to_degree(float pi) { return pi * DIV180_BY_PI; }

	//=============================================================================
	// 関数名：		degree_to_pi
	// 説明：		radianから度数法へ
	//=============================================================================
	inline float degree_to_pi(float degree) { return degree * DIVPI_BY_180; }

	//=============================================================================
	// 関数名：		degree_to_pi
	// 説明：		radianから度数法へ
	//=============================================================================
	const char* printf_here(const char *fmt, ...);

	//=============================================================================
	// 関数名：		get_split_string
	// 引数：		const std::string &str	元の文字列
	// 引数：		char sep				分割文字
	// 説明：		分割文字で句切られた　文字列群を取得
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
//　using namespece ： t_lib
//====================================
//using namespace t_lib;

