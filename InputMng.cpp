//=====================================================================================================================
//	�t�@�C����:	InputMng.cpp
//	�쐬��:		�����O�X
//=====================================================================================================================
//	�X�V����
//		-ver 1.00	2016 / 07 / 07	�����O�X
//=====================================================================================================================
//	�t�@�C���̐���
//				���͊Ǘ�
//=====================================================================================================================

//====================================
//�@���@�C���N���[�h�@��
//====================================
//DirectX�EWindows�֘A
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <XInput.h>

#include "InputMng.h"

//====================================
//�@���@���C�u�����ւ̃����N�@��
//====================================
#pragma comment(lib, "Xinput.lib")

//====================================
//�@���@���O��ԁ@���p�錾�@��
//====================================
using namespace std;
using namespace t_lib;

//====================================
//�@���@�������O��ԁ@��
//====================================
namespace
{
	//�L�[�{�[�h��������l
	static const int KEY_JUDGE		= 0x80;

	XINPUT_STATE xinput_state;
	XINPUT_GAMEPAD* xinput_pad = &xinput_state.Gamepad;

	bool pre_key_state[2][KEY_NUM];				//�O��̃L�[
	bool is_key_press[2][KEY_NUM];				//���݂̃L�[
	bool is_key_trigger[2][KEY_NUM];			//�������u��
	bool is_key_release[2][KEY_NUM];			//�������u��
	unsigned long key_repeat_cnt[2][KEY_NUM];	//�����ꑱ���J�E���g

	//���z�L�[�R�[�h���X�g�@�� �Ή� :�@�L�[����@�w�胊�X�g
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

	//�����L�[�@���̓R�[�h
	enum KEYDIR_PTN
	{
		KEYDIR_UP = (1 << 0),		//������
		KEYDIR_DOWN = (1 << 1),		//������
		KEYDIR_RIGHT = (1 << 2),	//������
		KEYDIR_LEFT = (1 << 3),		//������
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
	// �֐���:	update_keyboard
	// �����F	�X�V�@�L�[�{�[�h
	//=====================================================================================================================
	inline void update_keyboard()
	{
		int*			ref_vkey_code;	//���z�L�[�R�[�h�@�ւ̎Q��
		bool*			ref_pre;		//�O��̓��͏󋵁@�ւ̎Q��
		bool*			ref_now;		//���݂̓��͏󋵁@�ւ̎Q��
		bool*			ref_trig;		//�������u�Ԕ���@�ւ̎Q��
		bool*			ref_rel;		//�������u�Ԕ���@�ւ̎Q��
		unsigned long*	ref_rep_cnt;	//���������J�E���^�@�ւ̎Q��

		bool			judge_base;		//Trig release�̔��f�

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
				//���݂̓��͂𔻒肵�@���f��̍쐬
				if(!j)
				{
					*ref_now |= (bool)GetAsyncKeyState(*ref_vkey_code);
				}

				judge_base = *ref_now ^ *ref_pre;

				//Trig release�̔���
				*ref_trig = (judge_base & *ref_now);
				*ref_rel = (judge_base & !(*ref_now));

				//�L�[�̏�Ԃ��X�V����
				*ref_pre = *ref_now;
				++(*ref_rep_cnt);

				//���݉�����Ă��Ȃ���΁@�������������OFF�A�J�E���^��0�ɂ��A���̃L�[��
				if(!*ref_now)
				{
					*ref_rep_cnt = 0;
				}

				//�e�Q�ƈʒu��i�߂�
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
	// �֐���:	update_xinput
	// �����F	�X�V�@XInput
	//=====================================================================================================================
	inline void update_xinput()
	{
		bool* ref_key;

		for(int i = 0; i < 2; ++i)
		{
			ref_key = is_key_press[i];

			//�Q�[���p�b�h�̏�Ԏ擾
			//�ڑ�����Ă�����A�Q�[���p�b�h�̒l���L�[�ɕϊ�
			if(XInputGetState(i, &xinput_state) == ERROR_SUCCESS)
			{
				//���s�ړ�
				ref_key[UP]		|= (xinput_pad->sThumbLY > 8192) ? true : false;
				ref_key[DOWN]	|= (xinput_pad->sThumbLY < -8192) ? true : false;
				ref_key[LEFT]	|= (xinput_pad->sThumbLX < -8192) ? true : false;
				ref_key[RIGHT]	|= (xinput_pad->sThumbLX > 8192) ? true : false;

				////���s�ړ�����2
				//ref_key[UP] |= (xinput_pad->sThumbRY > 8192) ? true : false;
				//ref_key[DOWN] |= (xinput_pad->sThumbRY < -8192) ? true : false;
				//ref_key[LEFT] |= (xinput_pad->sThumbRX < -8192) ? true : false;
				//ref_key[RIGHT] |= (xinput_pad->sThumbRX > 8192) ? true : false;

				//X B
				ref_key[X]		|= (xinput_pad->wButtons & XINPUT_GAMEPAD_X) ? true : false;
				ref_key[B]		|= (xinput_pad->wButtons & XINPUT_GAMEPAD_B) ? true : false;

				//A
				ref_key[A]		|= (xinput_pad->wButtons & XINPUT_GAMEPAD_A) ? true : false;

				////�|�b�h
				//ref_key[TRAP] |= (xinput_pad->bRightTrigger > 64) ? true : false;

				//Y
				ref_key[Y]		|= (xinput_pad->wButtons & XINPUT_GAMEPAD_Y) ? true : false;

				////�W�����v
				//ref_key[JUMP] |= (xinput_pad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? true : false;

				//�|�[�Y
				ref_key[PAUSE]	|= (xinput_pad->wButtons & XINPUT_GAMEPAD_START) ? true : false;
			}
		}
	}

	//=====================================================================================================================
	// �֐���:	update
	// �����F	�X�V
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
	// �֐���:	is_press
	// �����F	��������
	//=====================================================================================================================
	bool is_press(KEY code, int id)
	{
		return is_key_press[id][code];
	}

	//=====================================================================================================================
	// �֐���:	is_trigger
	// �����F	�������u�Ԕ���
	//=====================================================================================================================
	bool is_trigger(KEY code, int id)
	{
		return is_key_trigger[id][code];
	}

	//=====================================================================================================================
	// �֐���:	is_release
	// �����F	�������u�Ԕ���
	//=====================================================================================================================
	bool is_release(KEY code, int id)
	{
		return is_key_release[id][code];
	}

	//=====================================================================================================================
	// �֐���:	is_repeat
	// �����F	���������J�E���g�擾
	//=====================================================================================================================
	unsigned long is_repeat(KEY code, int id)
	{
		return key_repeat_cnt[id][code];
	}

	//=====================================================================================================================
	// �֐���:	is_each_press
	// �����F	��������
	//=====================================================================================================================
	bool is_each_press(KEY code)
	{
		return is_key_press[0][code] | is_key_press[1][code];
	}

	//=====================================================================================================================
	// �֐���:	is_each_trigger
	// �����F	�������u�Ԕ���
	//=====================================================================================================================
	bool is_each_trigger(KEY code)
	{
		return is_key_trigger[0][code] | is_key_trigger[1][code];
	}

	//=====================================================================================================================
	// �֐���:	is_each_release
	// �����F	�������u�Ԕ���
	//=====================================================================================================================
	bool is_each_release(KEY code)
	{
		return is_key_release[0][code] | is_key_release[1][code];
	}

	//=====================================================================================================================
	// �֐���:	is_each_repeat
	// �����F	���������J�E���g�擾
	//=====================================================================================================================
	unsigned long is_each_repeat(KEY code)
	{
		return is_key_release[0][code] + is_key_release[1][code];
	}

	//=====================================================================================================================
	// �֐���:	get_3d_xz_dir
	// �����F	���͕������@XZ���ʂł̈ړ������擾
	//=====================================================================================================================
	Vector3 get_3d_xz_dir(int id)
	{
		//�Q�[���p�b�h�̏�Ԏ擾
		//�ڑ�����Ă�����A�Q�[���p�b�h�̒l�����̂܂܈ړ������Ƃ��ēn��
		if(XInputGetState(id, &xinput_state) == ERROR_SUCCESS)
		{
			return Vector3(
				((is_out(xinput_pad->sThumbLX, -8192, 8192)) ? ((float)xinput_pad->sThumbLX * INV_32768) : (0.0f)),
				0.0f,
				((is_out(xinput_pad->sThumbLY, -8192, 8192)) ? ((float)xinput_pad->sThumbLY * INV_32768) : (0.0f)));
		}

		//====================================
		// �㉺���E�̃L�[���擾
		//====================================
		unsigned char keydir =
			is_key_press[id][UP] * KEYDIR_UP
			| is_key_press[id][DOWN] * KEYDIR_DOWN
			| is_key_press[id][LEFT] * KEYDIR_LEFT
			| is_key_press[id][RIGHT] * KEYDIR_RIGHT;

		return keydir <= 10 ? xz_vec_list[keydir] : VEC3_ZERO;
	}

	//=====================================================================================================================
	// �֐���:	get_2d_xy_dir
	// �����F	���͕������@XY���ʂł̈ړ������擾
	//=====================================================================================================================
	Vector2 get_2d_xy_dir(int id)
	{
		//�Q�[���p�b�h�̏�Ԏ擾
		//�ڑ�����Ă�����A�Q�[���p�b�h�̒l�����̂܂܈ړ������Ƃ��ēn��
		if(XInputGetState(id, &xinput_state) == ERROR_SUCCESS)
		{
			return Vector2(
				((is_out(xinput_pad->sThumbLX, -8192, 8192)) ? ((float)xinput_pad->sThumbLX * INV_32768) : (0.0f)),
				((is_out(xinput_pad->sThumbLY, -8192, 8192)) ? ((float)xinput_pad->sThumbLY * INV_32768) : (0.0f)));
		}

		//====================================
		// �㉺���E�̃L�[���擾
		//====================================
		unsigned char keydir =
			is_key_press[id][UP] * KEYDIR_UP
			| is_key_press[id][DOWN] * KEYDIR_DOWN
			| is_key_press[id][LEFT] * KEYDIR_LEFT
			| is_key_press[id][RIGHT] * KEYDIR_RIGHT;

		return keydir <= 10 ? xy_vec_list[keydir] : VEC2_ZERO;
	}
}
