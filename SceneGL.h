#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Scene.h
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/4/22
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
#include "RendererGL.h"


/******************************************************************************
**	���C�u���������N
******************************************************************************/



/******************************************************************************
**	�}�N����`
******************************************************************************/

// �V�[���̃f�[�^
typedef enum
{
	SCENEPARAM_POS = 0,
	SCENEPARAM_ROT,
	SCENEPARAM_SCL,
	SCENEPARAM_SIZE, // x = width, y = height, z = depth
	SCENEPARAM_MAX,

}SCENEPARAM;


// �V�[���̎��
typedef enum
{
	SCENETYPE_NONE = 0,
	SCENETYPE_2D,
	SCENETYPE_3D,
	SCENETYPE_MODEL,
	SCENETYPE_PLAYER,
	SCENETYPE_ENEMY,
	SCENETYPE_SPHIRE,
	SCENETYPE_MESHFIELD,
	SCENETYPE_MESHDOME,
	SCENETYPE_LIVE2D_2D,
	SCENETYPE_LIVE2D_3D,
	SCENETYPE_MAX

}SCENETYPE;


/* �v���C�I���e�B */
typedef enum
{
	PRIORITY_3D = 0,
	PRIORITY_MODEL,
	PRIORITY_LIVE2D,
	PRIORITY_2D,
	PRIORITY_MAX

}PRIORITY;


/******************************************************************************
**	�N���X��`
******************************************************************************/
class SceneGL
{
	public:
	SceneGL( int Priority = 0 );
	virtual ~SceneGL();

	// ���\�b�h
	virtual HRESULT Init() = 0;
	virtual int Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static HRESULT InitAll();
	static int UninitAll();
	static void UpdateAll();
	static void DrawAll();
	void Release();


	// get,set
	OBJECT3D* GetObject3D();
	void SetObject3D( OBJECT3D );
	bool SetTexture( const char *pFilePath );
	virtual void SetParam( float *x, float *y, float *z, SCENEPARAM ParamName );
	virtual void SetParam( Vector3 *, SCENEPARAM ParamName );
	void SetColor( float *r, float *g, float *b, float *a );
	void SetColor( Color * );
	void SetAnimation( int ChangeTim, float PatternX, float PatternY );


	// Delete
	void DeleteTexture();


protected:
	static DWORD m_dwCreateCnt; // ������
	static SceneGL *m_Top[ PRIORITY_MAX ]; // �擪�A�h���X
	static SceneGL *m_Last[ PRIORITY_MAX ]; // ���݃|�C���^
	SceneGL *m_Prev; // �O�|�C���^
	SceneGL *m_Next; // ���|�C���^
	OBJECT3D m_Obj3d; // �I�u�W�F�N�g3D
	int m_Texture;
	char *m_pTexPath;
	bool m_bCreate;

};

