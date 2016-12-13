//=====================================================================================================================
//	�t�@�C����:	InputMng.h
//	�쐬��:		�����O�X
//=====================================================================================================================
//	�X�V����
//		-ver 1.00	2016 / 07 / 07	�����O�X
//=====================================================================================================================
//	�t�@�C���̐���
//				���͊Ǘ�
//=====================================================================================================================
#pragma once

//====================================
//�@���@�C���N���[�h�@��
//====================================
#include "UtlMath.h"

//====================================
//�@���O��ԁFinput
//====================================
namespace input
{
	//�L�[����@�w�胊�X�g
	typedef enum
	{//				XInput				Keyboard
		UP,		//	sThumbL sThumbR		VK_UP
		DOWN,	//	sThumbL sThumbR		VK_DOWN
		LEFT,	//	sThumbL sThumbR		VK_LEFT
		RIGHT,	//	sThumbL sThumbR		VK_RIGHT

		X,		//	button_x			'Z'
		B = X,	//	button_b
		DECIDE = X,

		A,		//	button_a			'X'
		CANSEL = A,
		
		Y,		//	button_r_thumb		VK_LSHIFT

		PAUSE,	//	button_start		VK_RETURN

		F1,		//						VK_F1

		KEY_0,	//						'0'
		KEY_1,	//						'1'
		KEY_2,	//						'2'
		KEY_3,	//						'3'
		KEY_4,	//						'4'
		KEY_5,	//						'5'
		KEY_6,	//						'6'
		KEY_7,	//						'7'
		KEY_8,	//						'8'
		KEY_9,	//						'9'

		KEY_NUM,
	}KEY;

	//�L�[���͕����@�߂�l�@(������Ɂ@�E��])
	enum KEYDIR
	{
		NONE,	//������ or �����ȕ���
		D,		//���̂�
		RD,		//�E��
		R,		//�E�̂�
		RU,		//�E��
		U,		//��̂�
		LU,		//����
		L,		//���̂�
		LD,		//����
	};

	void update();

	bool is_press(KEY code, int id = 0);
	bool is_trigger(KEY code, int id = 0);
	bool is_release(KEY code, int id = 0);
	unsigned long is_repeat(KEY code, int id = 0);

	bool is_each_press(KEY code);
	bool is_each_trigger(KEY code);
	bool is_each_release(KEY code);
	unsigned long is_each_repeat(KEY code);

	t_lib::Vector3 get_3d_xz_dir(int id = 0);
	t_lib::Vector2 get_2d_xy_dir(int id = 0);
};

//====================================
//�@���O��ԗ��p�Finput
//====================================
using namespace input;

