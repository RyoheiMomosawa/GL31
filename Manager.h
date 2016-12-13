#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Manager.h
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/5/9
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

// �V�X�e���֘A
#include <Windows.h>
#include "DIKeyboard.h"
#include "DIMouse.h"
#include "SoundAL.h"
#include "WindowsSocketService.h"


/******************************************************************************
**	���C�u���������N
******************************************************************************/


/******************************************************************************
**	�}�N����`
******************************************************************************/

// �T�E���h�֘A
#define SOURCE_MAX ( 5 )
#define BUFFER_MAX ( 2 )


/******************************************************************************
**	�N���X��`
******************************************************************************/
class RendererGL;
class SceneGL;
class Mode;
class Fade;
class Server;
class Client;
class Manager
{
public:
	Manager();
	virtual ~Manager();


	// ���\�b�h
	static HRESULT Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow );
	static int Uninit();
	static void Update();
	static void Draw();


	// Set,Get
	static input::DirectInput *GetKeyboard();
	static input::DIMouse *GetMouse();
	static void SetMode( Mode *Mode );
	static Client *GetClient();


	// �����o�ϐ�
private:
	/// �V�X�e���֘A
	// �����_��
	static RendererGL *m_pRenderer;
	// �V�[���N���X
	static SceneGL *m_pScene;
	// �n�[�h�E�F�A
	static input::DirectInput *m_pKeyboard;
	static input::DIMouse *m_Mouse;
	// �T�E���h
	static SoundAL *m_pSound;
	// ���[�h�Ǘ�
	static Mode *m_pMode;
	// �t�F�[�h
	static Fade *m_pFade;


	// BGM�f�[�^
	static ALuint m_bgm001ID;

	static Client *m_pReceive;
	static HANDLE m_hClient;
	static unsigned int m_thClient;

};

