//=====================================================================================================================
//	ファイル名:	InputMng.cpp
//	作成者:		高橋弘宜
//=====================================================================================================================
//	更新履歴
//		-ver 1.00	2016 / 07 / 07	高橋弘宜
//=====================================================================================================================
//	ファイルの説明
//				入力管理
//=====================================================================================================================

//====================================
//　※　インクルード　※
//====================================
//DirectX・Windows関連
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <XInput.h>

#include "InputMng.h"

//====================================
//　※　ライブラリへのリンク　※
//====================================
#pragma comment(lib, "Xinput.lib")

//====================================
//　※　名前空間　利用宣言　※
//====================================
using namespace std;
using namespace t_lib;

//====================================
//　※　無名名前空間　※
//====================================
namespace
{
	//キーボード押下判定値
	static const int KEY_JUDGE		= 0x80;

	XINPUT_STATE xinput_state;
	XINPUT_GAMEPAD* xinput_pad = &xinput_state.Gamepad;

	bool pre_key_state[2][KEY_NUM];				//前回のキー
	bool is_key_press[2][KEY_NUM];				//現在のキー
	bool is_key_trigger[2][KEY_NUM];			//押した瞬間
	bool is_key_release[2][KEY_NUM];			//離した瞬間
	unsigned long key_repeat_cnt[2][KEY_NUM];	//押され続けカウント

	//仮想キーコードリスト　※ 対応 :　キー判定　指定リスト
	int vkey_code[] = 
	{
		VK_UP,			//UP,
		VK_DOWN,		//DOWN,
		VK_LEFT,		//LEFT,
		VK_RIGHT,		//RIGHT,

		'Z',			//SHOT,
		'X',			//BOMB,
		VK_LSHIFT,		//POD,
		VK_SPACE,		//BOOST,

		'C',			//JUMP,

		VK_RETURN,		//PAUSE,

		VK_F1,			//F1

		'0',			//KEY_0
		'1',			//KEY_1
		'2',			//KEY_2
		'3',			//KEY_3
		'4',			//KEY_4
		'5',			//KEY_5
		'6',			//KEY_6
		'7',			//KEY_7
		'8',			//KEY_8
		'9',			//KEY_9
	};

	//方向キー　入力コード
	enum KEYDIR_PTN
	{
		KEYDIR_UP = (1 << 0),		//↑入力
		KEYDIR_DOWN = (1 << 1),		//↓入力
		KEYDIR_RIGHT = (1 << 2),	//→入力
		KEYDIR_LEFT = (1 << 3),		//←入力
	};

	Vector3 xz_vec_list[] =
	{
		VEC3_ZERO,		//0
		VEC3_FRONT,		//1
		VEC3_BACK,		//2
		VEC3_ZERO,		//3
		VEC3_RIGHT,		//4
		VEC3_RF,		//5
		VEC3_RB,		//6
		VEC3_ZERO,		//7
		VEC3_LEFT,		//8
		VEC3_LF,		//9
		VEC3_LB,		//10
	};

	Vector2 xy_vec_list[] =
	{
		VEC2_ZERO,		//0
		VEC2_UP,		//1
		VEC2_DOWN,		//2
		VEC2_ZERO,		//3
		VEC2_RIGHT,		//4
		VEC2_RU,		//5
		VEC2_RD,		//6
		VEC2_ZERO,		//7
		VEC2_LEFT,		//8
		VEC2_LU,		//9
		VEC2_LD,		//10
	};
}

namespace input
{
	//=====================================================================================================================
	// 関数名:	update_keyboard
	// 説明：	更新　キーボード
	//=====================================================================================================================
	inline void update_keyboard()
	{
		int*			ref_vkey_code;	//仮想キーコード　への参照
		bool*			ref_pre;		//前回の入力状況　への参照
		bool*			ref_now;		//現在の入力状況　への参照
		bool*			ref_trig;		//押した瞬間判定　への参照
		bool*			ref_rel;		//離した瞬間判定　への参照
		unsigned long*	ref_rep_cnt;	//押し続けカウンタ　への参照

		bool			judge_base;		//Trig releaseの判断基準

		for(int j = 0; j < 2; ++j)
		{
			ref_vkey_code = vkey_code;
			ref_pre = pre_key_state[j];
			ref_now = is_key_press[j];
			ref_trig = is_key_trigger[j];
			ref_rel = is_key_release[j];
			ref_rep_cnt = key_repeat_cnt[j];

			for(int i = 0; i < KEY_NUM; ++i)
			{
				//現在の入力を判定し　判断基準の作成
				if(!j)
				{
					*ref_now |= (bool)GetAsyncKeyState(*ref_vkey_code);
				}

				judge_base = *ref_now ^ *ref_pre;

				//Trig releaseの判定
				*ref_trig = (judge_base & *ref_now);
				*ref_rel = (judge_base & !(*ref_now));

				//キーの状態を更新する
				*ref_pre = *ref_now;
				++(*ref_rep_cnt);

				//現在押されていなければ　押し続け判定をOFF、カウンタを0にし、次のキーへ
				if(!*ref_now)
				{
					*ref_rep_cnt = 0;
				}

				//各参照位置を進める
				++ref_vkey_code;
				++ref_pre;
				++ref_now;
				++ref_trig;
				++ref_rel;
				++ref_rep_cnt;
			}
		}
	}

	//=====================================================================================================================
	// 関数名:	update_xinput
	// 説明：	更新　XInput
	//=====================================================================================================================
	inline void update_xinput()
	{
		bool* ref_key;

		for(int i = 0; i < 2; ++i)
		{
			ref_key = is_key_press[i];

			//ゲームパッドの状態取得
			//接続されていたら、ゲームパッドの値をキーに変換
			if(XInputGetState(i, &xinput_state) == ERROR_SUCCESS)
			{
				//平行移動
				ref_key[UP]		|= (xinput_pad->sThumbLY > 8192) ? true : false;
				ref_key[DOWN]	|= (xinput_pad->sThumbLY < -8192) ? true : false;
				ref_key[LEFT]	|= (xinput_pad->sThumbLX < -8192) ? true : false;
				ref_key[RIGHT]	|= (xinput_pad->sThumbLX > 8192) ? true : false;

				////平行移動その2
				//ref_key[UP] |= (xinput_pad->sThumbRY > 8192) ? true : false;
				//ref_key[DOWN] |= (xinput_pad->sThumbRY < -8192) ? true : false;
				//ref_key[LEFT] |= (xinput_pad->sThumbRX < -8192) ? true : false;
				//ref_key[RIGHT] |= (xinput_pad->sThumbRX > 8192) ? true : false;

				//X B
				ref_key[X]		|= (xinput_pad->wButtons & XINPUT_GAMEPAD_X) ? true : false;
				ref_key[B]		|= (xinput_pad->wButtons & XINPUT_GAMEPAD_B) ? true : false;

				//A
				ref_key[A]		|= (xinput_pad->wButtons & XINPUT_GAMEPAD_A) ? true : false;

				////ポッド
				//ref_key[TRAP] |= (xinput_pad->bRightTrigger > 64) ? true : false;

				//Y
				ref_key[Y]		|= (xinput_pad->wButtons & XINPUT_GAMEPAD_Y) ? true : false;

				////ジャンプ
				//ref_key[JUMP] |= (xinput_pad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? true : false;

				//ポーズ
				ref_key[PAUSE]	|= (xinput_pad->wButtons & XINPUT_GAMEPAD_START) ? true : false;
			}
		}
	}

	//=====================================================================================================================
	// 関数名:	update
	// 説明：	更新
	//=====================================================================================================================
	void update()
	{
		for(int i = 0; i < KEY_NUM; ++i)
		{
			is_key_press[0][i] = false;
			is_key_press[1][i] = false;
		}

		update_xinput();
		update_keyboard();
	}

	//=====================================================================================================================
	// 関数名:	is_press
	// 説明：	押下判定
	//=====================================================================================================================
	bool is_press(KEY code, int id)
	{
		return is_key_press[id][code];
	}

	//=====================================================================================================================
	// 関数名:	is_trigger
	// 説明：	押した瞬間判定
	//=====================================================================================================================
	bool is_trigger(KEY code, int id)
	{
		return is_key_trigger[id][code];
	}

	//=====================================================================================================================
	// 関数名:	is_release
	// 説明：	離した瞬間判定
	//=====================================================================================================================
	bool is_release(KEY code, int id)
	{
		return is_key_release[id][code];
	}

	//=====================================================================================================================
	// 関数名:	is_repeat
	// 説明：	押し続けカウント取得
	//=====================================================================================================================
	unsigned long is_repeat(KEY code, int id)
	{
		return key_repeat_cnt[id][code];
	}

	//=====================================================================================================================
	// 関数名:	is_each_press
	// 説明：	押下判定
	//=====================================================================================================================
	bool is_each_press(KEY code)
	{
		return is_key_press[0][code] | is_key_press[1][code];
	}

	//=====================================================================================================================
	// 関数名:	is_each_trigger
	// 説明：	押した瞬間判定
	//=====================================================================================================================
	bool is_each_trigger(KEY code)
	{
		return is_key_trigger[0][code] | is_key_trigger[1][code];
	}

	//=====================================================================================================================
	// 関数名:	is_each_release
	// 説明：	離した瞬間判定
	//=====================================================================================================================
	bool is_each_release(KEY code)
	{
		return is_key_release[0][code] | is_key_release[1][code];
	}

	//=====================================================================================================================
	// 関数名:	is_each_repeat
	// 説明：	押し続けカウント取得
	//=====================================================================================================================
	unsigned long is_each_repeat(KEY code)
	{
		return is_key_release[0][code] + is_key_release[1][code];
	}

	//=====================================================================================================================
	// 関数名:	get_3d_xz_dir
	// 説明：	入力方向より　XZ平面での移動方向取得
	//=====================================================================================================================
	Vector3 get_3d_xz_dir(int id)
	{
		//ゲームパッドの状態取得
		//接続されていたら、ゲームパッドの値をそのまま移動方向として渡す
		if(XInputGetState(id, &xinput_state) == ERROR_SUCCESS)
		{
			return Vector3(
				((is_out(xinput_pad->sThumbLX, -8192, 8192)) ? ((float)xinput_pad->sThumbLX * INV_32768) : (0.0f)),
				0.0f,
				((is_out(xinput_pad->sThumbLY, -8192, 8192)) ? ((float)xinput_pad->sThumbLY * INV_32768) : (0.0f)));
		}

		//====================================
		// 上下左右のキーを取得
		//====================================
		unsigned char keydir =
			is_key_press[id][UP] * KEYDIR_UP
			| is_key_press[id][DOWN] * KEYDIR_DOWN
			| is_key_press[id][LEFT] * KEYDIR_LEFT
			| is_key_press[id][RIGHT] * KEYDIR_RIGHT;

		return keydir <= 10 ? xz_vec_list[keydir] : VEC3_ZERO;
	}

	//=====================================================================================================================
	// 関数名:	get_2d_xy_dir
	// 説明：	入力方向より　XY平面での移動方向取得
	//=====================================================================================================================
	Vector2 get_2d_xy_dir(int id)
	{
		//ゲームパッドの状態取得
		//接続されていたら、ゲームパッドの値をそのまま移動方向として渡す
		if(XInputGetState(id, &xinput_state) == ERROR_SUCCESS)
		{
			return Vector2(
				((is_out(xinput_pad->sThumbLX, -8192, 8192)) ? ((float)xinput_pad->sThumbLX * INV_32768) : (0.0f)),
				((is_out(xinput_pad->sThumbLY, -8192, 8192)) ? ((float)xinput_pad->sThumbLY * INV_32768) : (0.0f)));
		}

		//====================================
		// 上下左右のキーを取得
		//====================================
		unsigned char keydir =
			is_key_press[id][UP] * KEYDIR_UP
			| is_key_press[id][DOWN] * KEYDIR_DOWN
			| is_key_press[id][LEFT] * KEYDIR_LEFT
			| is_key_press[id][RIGHT] * KEYDIR_RIGHT;

		return keydir <= 10 ? xy_vec_list[keydir] : VEC2_ZERO;
	}
}
