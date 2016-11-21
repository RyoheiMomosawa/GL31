#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Game.h
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/7/19
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�X�V���e
**
**
**
******************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "Mode.h"


/******************************************************************************
**	���C�u���������N
******************************************************************************/


/******************************************************************************
**	�}�N����`
******************************************************************************/


/******************************************************************************
**	�N���X��`
******************************************************************************/
class SceneGL;
class SceneGLTimer;
class Game : public Mode
{
public:
	Game();
	virtual ~Game();


	// ���\�b�h
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// Set,Get


	// �����o�ϐ�
private:
	/// �I�u�W�F�N�g
	// �V�[��(�ėp�^ ���L�g�p�\)
	SceneGL *m_pScene;
	// �^�C�}�[
	static SceneGLTimer *m_pTimer;

};
