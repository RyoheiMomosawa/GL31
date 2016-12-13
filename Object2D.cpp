/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Object2D.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 38 ���V�ȕ�
**	�쐬��    : 2016/11/21
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�X�V���e
**
******************************************************************************/


/******************************************************************************
�C���N���[�h�t�@�C��
******************************************************************************/
#include "main.h"
#include "Manager.h"
#include "RendererGL.h"

#include "Scene2DGL.h"
#include "ImageTGA.h"

#include "Object2D.h"


/******************************************************************************
**	�}�N����`
******************************************************************************/

///////////////////////////////////////////////////////////////////////////////
//	�ÓI�ϐ�
///////////////////////////////////////////////////////////////////////////////
//	�擪�A�h���X
CObject2D *CObject2D::m_TopAddress = NULL;
//	���݃A�h���X
CObject2D *CObject2D::m_CurrentAddress = NULL;
// �e�N�X�`���ژ^
int CObject2D::m_Texture[CObject2D::TEXTURE_INDEX_MAX] = { NULL };
// �e�N�X�`���p�X
char *CObject2D::m_pTexPath[CObject2D::TEXTURE_INDEX_MAX] = { NULL };

/******************************************************************************
**	�v���g�^�C�v�錾
******************************************************************************/


/******************************************************************************
**	�O���[�o���ϐ�
******************************************************************************/

///////////////////////////////////////////////////////////////////////////////
//	�֐���	: CObject2D::CObject2D()
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	����	: �R���X�g���N�^
//
///////////////////////////////////////////////////////////////////////////////
CObject2D::CObject2D()
{
	//	�ŏ��̎�
	if (m_TopAddress == NULL)
	{
		//	�g�b�v�A�h���X�X�V
		m_TopAddress = this;
		//	���݂̃A�h���X�X�V
		m_CurrentAddress = this;
		//	�O�A�h���X�X�V
		m_PreviousAddress = NULL;
		//	���̃A�h���X�X�V
		m_NextAddress = NULL;
	}
	//	�ŏ��̎��ȊO
	else
	{
		//	���݃A�h���X�̑O�A�h���X�̎��A�h���X�Ɍ��݃A�h���X����
		m_CurrentAddress->m_NextAddress = this;
		//	�O�A�h���X�X�V
		m_PreviousAddress = m_CurrentAddress;
		//	���݂̃A�h���X�X�V
		m_CurrentAddress = this;
		//	���̃A�h���X�X�V
		m_NextAddress = NULL;
	}
}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: CObject2D::~CObject2D()
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	����	: �f�X�g���N�^
//
///////////////////////////////////////////////////////////////////////////////
CObject2D::~CObject2D()
{
}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: CObject2D *CObject2D::Create(Vector3 *Position, Vector3 *Size, TEXTURE_INDEX Texture )
//	�߂�l	: CObject2D�̃|�C���^
//	����	: ���W, �T�C�Y, �e�N�X�`���ژ^
//	����	: 2D�|���S���̍쐬
//
///////////////////////////////////////////////////////////////////////////////
CObject2D *CObject2D::Create(Vector3 *Position, Vector3 *Size, TEXTURE_INDEX Texture )
{
	CObject2D *pObject2D = new CObject2D;
	pObject2D->Init(Position, Size, Texture);
	return pObject2D;
}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: void CObject2D::Init(Vector3 *Position, Vector3 *Size, TEXTURE_INDEX Texture)
//	�߂�l	: �Ȃ�
//	����	: ���W, �T�C�Y, �e�N�X�`���ژ^
//	����	: ������
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::Init(Vector3 *Position, Vector3 *Size, TEXTURE_INDEX Texture)
{
	// ���
	m_Position = *Position;
	m_Size = *Size;
	m_UseTextureIndex = Texture;
	m_Rotation = Vector3(0.0f, 0.0f, 90.0f);
}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: void CObject2D::Uninit(void)
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	����	: �I������
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::Uninit(void)
{
}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: void CObject2D::UninitAll(void)
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	����	: �S�ďI������
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::UninitAll(void)
{
	//	�A�h���X�̓��ꕨ
	CObject2D *Address = m_TopAddress;
	CObject2D *Address2 = NULL;

	while (Address != NULL)
	{
		//	�A�h���X�̏I���������s��
		Address->Uninit();
		//	�A�h���X�̍X�V
		Address2 = Address->m_NextAddress;
		//	
		delete Address;
		//
		Address = Address2;
	}
	m_TopAddress = NULL;

	// �e�N�X�`�����
	for (int i = 0; i < TEXTURE_INDEX_MAX; i++)
	{
		if (m_Texture[i] != NULL)
		{
			glDeleteTextures(GL_TEXTURE_2D, (unsigned int *)&m_Texture[i]);
			m_Texture[i] = NULL;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: void CObject2D::Update(void)
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	����	: �X�V����
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::Update(void)
{

}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: void CObject2D::UpdateAll(void)
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	����	: �S�čX�V����
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::UpdateAll(void)
{
	if (m_TopAddress != NULL)
	{
		//	�A�h���X�̓��ꕨ
		CObject2D *Address = m_TopAddress;
		CObject2D *Address2 = m_TopAddress->m_NextAddress;

		while (Address != NULL)
		{
			Address2 = Address->m_NextAddress;
			//	�A�h���X�̍X�V�������s��
			Address->Update();

			//	�A�h���X�̍X�V
			Address = Address2;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: void CObject2D::Draw(void) 
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	����	: �`�揈��
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::Draw(void) 
{
	////////////////////////////////////////////////////////////
	// �v���W�F�N�V�����}�g���N�X
	////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);		// �v���W�F�N�V�����}�g���N�X�ݒ�錾
	glPushMatrix();						// ���̑ޔ�
	glLoadIdentity();					// �}�g���N�X�N���A
	glOrtho(0.0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0.0, 0.0, 1.0);

	/////////////////////////////////////////////////////////////
	//	���f���r���[�}�g���N�X
	/////////////////////////////////////////////////////////////
	glMatrixMode(GL_MODELVIEW);		// ���f���r���[�}�g���N�X�ݒ�錾
	glPushMatrix();						// ���̑ޔ�
	glLoadIdentity();					// �}�g���N�X�ޔ�


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Texture[m_UseTextureIndex]);


	// �A���t�@�u�����h�ݒ�
	glEnable(GL_BLEND);
	//glBlendFunc( GL_SRC_ALPHA, GL_DST_ALPHA );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	// ���C�g�̖�����
	glDisable(GL_LIGHTING);

	// �ړ�
	glTranslated(m_Position.x, m_Position.y, m_Position.z);
	// ��]
	glRotatef(m_Rotation.x, 1.0, 0.0, 0.0);
	glRotatef(m_Rotation.y, 0.0, 1.0, 0.0);
	glRotatef(m_Rotation.z, 0.0, 0.0, 1.0);

	/////////////////////////////////////////////////////////////
	//	�|���S���`��
	/////////////////////////////////////////////////////////////
	// �`�悱������
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(0xff, 0xff, 0xff, 0x01);	// �F

	glTexCoord2f(0.0f, 0.0f);
	glVertex2d(  -m_Size.x/2.0f, m_Size.y/2.0f);		// ���W

	glTexCoord2f(1.0f, 0.0f);
	glVertex2d(	 m_Size.x / 2.0f, m_Size.y / 2.0f);	// ���W

	glTexCoord2f(0.0f, 1.0f);
	glVertex2d( -m_Size.x / 2.0f, -m_Size.y / 2.0f);	// ���W

	glTexCoord2f(1.0f, 1.0f);
	glVertex2d( m_Size.x / 2.0f, -m_Size.y / 2.0f);	// ���W

	// �`�悱���܂�
	glEnd();


	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	/////////////////////////////////////////////////////////////
	//	�v���W�F�N�V�����}�g���N�X�ݒ��߂�
	/////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	/////////////////////////////////////////////////////////////
	//	���f���r���[�}�g���N�X�ݒ��߂�
	/////////////////////////////////////////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: void CObject2D::DrawAll(void)
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	����	: �S�ĕ`�揈��
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::DrawAll(void)
{
	if (m_TopAddress != NULL)
	{
		//	�A�h���X�̓��ꕨ
		CObject2D *Address = m_TopAddress;

		while (Address != NULL)
		{
			//	�A�h���X�̕`�揈�����s��
			Address->Draw();
			//	�A�h���X�̍X�V
			Address = Address->m_NextAddress;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: bool CObject2D::WritingTextureIndex(const char *pFilePath, TEXTURE_INDEX Index)
//	�߂�l	: true, false
//	����	: �t�@�C���p�X, �e�N�X�`���ژ^
//	����	: �e�N�X�`���ژ^�Ƀf�[�^����������
//
///////////////////////////////////////////////////////////////////////////////
bool CObject2D::WritingTextureIndex(const char *pFilePath, TEXTURE_INDEX Index)
{
	// �e�N�X�`���ݒ�
	if (m_Texture[Index] == NULL)
	{
		ImageTGA cTexture;
		m_Texture[Index] = cTexture.CreateTexture(pFilePath);
	}
	// �f�[�^�������Ă���ꍇ�͍폜���Ă���ǂݍ���
	else
	{
		glDeleteTextures(GL_TEXTURE_2D, (unsigned int *)&m_Texture[Index]);
		m_Texture[Index] = NULL;
		ImageTGA cTexture;
		m_Texture[Index] = cTexture.CreateTexture(pFilePath);
	}

	// �t�@�C�������邩�ǂ������ׂ�
	if (m_Texture[Index]!= NULL)
	{
		m_pTexPath[Index] = (char *)pFilePath;
		return true;
	}
	else
	{
		// �����ꍇ��false��Ԃ�
		m_pTexPath[Index] = NULL;
		m_Texture[Index] = NULL;
		return false;
	}

}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: bool CObject2D::CollisionDetection(Vector3 *Position)
//	�߂�l	: ������ true, �����ĂȂ� false
//	����	: �����蔻�肷����W
//	����	: �w�肵�����W�̎l�p�`�̓����蔻��
//
///////////////////////////////////////////////////////////////////////////////
bool CObject2D::CollisionDetection(Vector3 *Position)
{
	
	VECTOR3 CheckPos = *Position;		// �`�F�b�N������W
	if ((m_Position.x - m_Size.x/2.0f <= CheckPos.x) && (m_Position.x + m_Size.x/2.0f >= CheckPos.x) &&
		(m_Position.y - m_Size.y/2.0f <= CheckPos.y) && (m_Position.y + m_Size.y/2.0f >= CheckPos.y))
	{
		return true;
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: SphereAndSphereDetection
//	�߂�l	: ������ true, �����ĂȂ� false
//	����	: Objct1�̍��W�ƃT�C�Y�AObjct2�̍��W�ƃT�C�Y
//	����	: ���Ƌ��̓����蔻��
//
///////////////////////////////////////////////////////////////////////////////
bool CObject2D::SphereAndSphereDetection(Vector3 PositionObj1, Vector3 SizeObj1, Vector3 PositionObj2, Vector3 SizeObj2)
{
	float f_Length1, f_Length2;
	float f_Distance;

	// Obj1�̔��a�̒���
	f_Length1 = sqrtf(((SizeObj1.x / 2.0f)*(SizeObj1.x / 2.0f)) + ((SizeObj1.y / 2.0f)*(SizeObj1.y / 2.0f)));

	// Obj2�̔��a�̒���
	f_Length2 = sqrtf(((SizeObj2.x / 2.0f)*(SizeObj2.x / 2.0f)) + ((SizeObj2.y / 2.0f)*(SizeObj2.y / 2.0f)));

	// Obj1��Obj2�̋���
	f_Distance = sqrtf( (PositionObj1.x - PositionObj2.x)*(PositionObj1.x - PositionObj2.x)
						+ (PositionObj1.y - PositionObj2.y)*(PositionObj1.y - PositionObj2.y));

	// ����Obj1��obj2�̋�����\�������Z���ꍇ
	if (f_Distance <= f_Length1 + f_Length2)
	{
		return true;
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////////
//	�֐���	: void CObject2D::SetParameter(Vector3 *parameter)
//	�߂�l	: �Ȃ�
//	����	: �p�����[�^�[�̃^�C�v, �p�����[�^�[
//	����	: �p�����[�^�[�̕ύX������B
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::SetParameter(PARAMETER_TYPE type, Vector3 *parameter)
{
	switch (type)
	{
	case POSITION:	// ���W
		{
			m_Position = *parameter;
			break;
		}
		case ROTATION:	// ��]
		{
			m_Rotation = *parameter;
			break;
		}
		case SIZE:	// �T�C�Y
		{
			m_Size = *parameter;
			break;
		}

	}
}