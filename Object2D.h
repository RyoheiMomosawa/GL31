#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Object2D.h
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 38 ���V�ȕ�
**	�쐬��    : 2016/11/21
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�X�V���e
**	
**		
**		
**
**
******************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/


/******************************************************************************
**	���C�u���������N
******************************************************************************/


/******************************************************************************
**	�}�N����`
******************************************************************************/



/******************************************************************************
**	�N���X��`
******************************************************************************/
class CObject2D
{
public :
	///////////////////////////////////////////////////////////////////////////
	// �e�N�X�`���ژ^
	///////////////////////////////////////////////////////////////////////////
		typedef enum
		{
			TEXTURE_INDEX_0 = 0,
			TEXTURE_INDEX_1,
			TEXTURE_INDEX_MAX		// �e�N�X�`���ژ^�ő吔
		}TEXTURE_INDEX;	// �e�N�X�`���ژ^
	///////////////////////////////////////////////////////////////////////////
	// �p�����[�^�[�^�C�v 
	///////////////////////////////////////////////////////////////////////////
		typedef enum
		{
			POSITION = 0,			// ���W
			ROTATION,				// ��]
			SIZE,					// �T�C�Y
			PARAMETER_TPEY_MAX_NUM	// �p�����[�^�[�^�C�v�ő吔
		}PARAMETER_TYPE; 

	CObject2D();	// �R���X�g���N�^
	~CObject2D();	// �f�X�g���N�^

	// �e�N�X�`���ژ^�Ƀf�[�^����������
	static bool WritingTextureIndex(const char *pFilePath, TEXTURE_INDEX Index);
	// �쐬
	static CObject2D *Create(Vector3 *Position, Vector3 *Size, TEXTURE_INDEX Texture);

	// ������
	void Init(Vector3 *Position, Vector3 *Size, TEXTURE_INDEX Texture);
	// �I������
	void Uninit(void);
	// �X�V����
	void Update(void);
	// �`�揈��
	void Draw(void);

	// �S�ďI������
	static void UninitAll(void);
	// �S�čX�V����
	static void UpdateAll(void);
	// �S�ĕ`�揈��
	static void DrawAll(void);

	//////////////////////////////////////////////////////////////////////////////
	//	�����蔻��
	//////////////////////////////////////////////////////////////////////////////
		// �w�肵�����W�̎l�p�`�̓����蔻��
		bool CollisionDetection( Vector3 *Position);
		// ���Ƌ��̓����蔻��
		bool SphereAndSphereDetection(Vector3 PositionObj1, Vector3 SizeObj1, Vector3 PositionObj2, Vector3 SizeObj2);

	//////////////////////////////////////////////////////////////////////////////
	//	�p�����[�^�[�ݒ�
	//////////////////////////////////////////////////////////////////////////////
		// �p�����[�^�[�ݒ�
		void SetParameter( PARAMETER_TYPE type, Vector3 *parameter);


private:
	static CObject2D *m_TopAddress;		// �擪�A�h���X
	static CObject2D *m_CurrentAddress;	// ���݃A�h���X
	CObject2D *m_PreviousAddress;		// �O�A�h���X
	CObject2D *m_NextAddress;			// ���A�h���X

	VECTOR3 m_Position;					// ���W
	VECTOR3 m_Rotation;					// ��]
	VECTOR3 m_Size;						// �T�C�Y

	TEXTURE_INDEX m_UseTextureIndex;			// �g���e�N�X�`���ژ^
	static char *m_pTexPath[TEXTURE_INDEX_MAX];	// �e�N�X�`���p�X
	static int m_Texture[TEXTURE_INDEX_MAX];	// �e�N�X�`��
};
