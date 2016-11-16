/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Sprite.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/5/23
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "Sprite.h"
#include "RendererGL.h"


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/


/******************************************************************************
**	�C���f�b�N�X�o�b�t�@�̃Z�b�g
**
**	�g�p���@
**	unsigned int nLabel�E�E�E�Ǘ��ԍ��i�[��A�h���X �`�掚�ɂ��̔ԍ����w�肷�邱�Ƃŕ`��ł���
**	void lpIdxBuff�E�E�E�C���f�b�N�X���i�[���Ă���z��̐擪�|�C���^
**	unsigned long size�E�E�E�C���f�b�N�X�̌��A�傫��
******************************************************************************/
void SpriteLib::CreateIndexBuffer( unsigned int *nLabel, unsigned int *lpIdxBuff, unsigned long size )
{
	/* �C���f�b�N�X�o�b�t�@�̕ۑ��̈搶�� */
	// �f�[�^��1���Ȃ������琶��������ɂ��̂܂܈������R�s�[
	*nLabel = g_lMeshDataNum;
	if( g_lMeshDataNum == 0 )
	{
		// ���b�V���f�[�^����
		g_lpMeshData = new MESHDATA;

		// �����̃f�[�^���R�s�[
		g_lpMeshData[ 0 ].nLabel = *nLabel;
		g_lpMeshData[ 0 ].lpIdxBuff = lpIdxBuff;
		g_lpMeshData[ 0 ].dIdxSize = size;

		// �o�^���J�E���g�A�b�v
		g_lMeshDataNum++;

	}
	else if( g_lMeshDataNum > 0 )
	{
		// ��Ɨ̈�̊m�� �R�s�[�̈�
		LPMESHDATA lpMeshData = new MESHDATA[ g_lMeshDataNum ];

		// �o�^���J�E���g�A�b�v
		g_lMeshDataNum++;

		// ���̃f�[�^���R�s�[������Ƀf�[�^��}������
		for( unsigned long nCntMesh = 0; nCntMesh < g_lMeshDataNum - 1; nCntMesh++ )
		{
			lpMeshData[ nCntMesh ] = g_lpMeshData[ nCntMesh ];

		}

		// �f�[�^���폜��A�V���ɐ���
		delete[] g_lpMeshData;
		g_lpMeshData = new MESHDATA[ g_lMeshDataNum ];

		// ���f�[�^���ڂ��ς�
		for( unsigned long nCntMesh = 0; nCntMesh < g_lMeshDataNum - 1; nCntMesh++ )
		{
			g_lpMeshData[ nCntMesh ] = lpMeshData[ nCntMesh ];

		}

		// �V�����f�[�^��}��
		g_lpMeshData[ g_lMeshDataNum - 1 ].nLabel = *nLabel;
		g_lpMeshData[ g_lMeshDataNum - 1 ].lpIdxBuff = lpIdxBuff;
		g_lpMeshData[ g_lMeshDataNum - 1 ].dIdxSize = size;

		// ��Ɨ̈���폜
		delete[] lpMeshData;

	}

}


/******************************************************************************
**	���_�o�b�t�@�̓o�^
**
**	�g�p���@
**	unsigned int nLabel�E�E�E�ύX�������Ǘ��ԍ�
**	Vector3 *pVtx�E�E�E���_�����i�[���Ă���z��̐擪�|�C���^
**	unsigned long size�E�E�E���_��
******************************************************************************/
bool SpriteLib::CreateVtxBuffer( unsigned int nLabel, Vector3 *pVtx, unsigned long size )
{
	// �Ǘ��ԍ��̌���
	for( unsigned long nCntLabel = 0; nCntLabel < g_lMeshDataNum; nCntLabel++ )
	{
		// �Y���̊Ǘ��ԍ�����������R�s�[����������
		if( g_lpMeshData[ nCntLabel ].nLabel == nLabel )
		{
			g_lpMeshData[ nCntLabel ].pVtx = pVtx;
			g_lpMeshData[ nCntLabel ].dVtxSize = size;

			// �R�s�[�ɐ���������true��Ԃ�
			return true;

		}

	}

	// �Y���̊Ǘ��ԍ����Ȃ�������false��Ԃ�
	return false;

}


/******************************************************************************
**	�@���o�b�t�@�̓o�^
**
**	�g�p���@
**	unsigned int nLabel�E�E�E�ύX�������Ǘ��ԍ�
**	Vector3 *pVtx�E�E�E���_�����i�[���Ă���z��̐擪�|�C���^
**	unsigned long size�E�E�E�@����
******************************************************************************/
bool SpriteLib::CreateNorBuffer( unsigned int nLabel, Vector3 *pNor, unsigned long size, int format )
{
	// �Ǘ��ԍ��̌���
	for( unsigned long nCntLabel = 0; nCntLabel < g_lMeshDataNum; nCntLabel++ )
	{
		// �Y���̊Ǘ��ԍ�����������R�s�[����������
		if( g_lpMeshData[ nCntLabel ].nLabel == nLabel )
		{
			g_lpMeshData[ nCntLabel ].pNor = pNor;
			g_lpMeshData[ nCntLabel ].dNorSize = size;
			g_lpMeshData[ nCntLabel ].NorFormat = format;

			// �R�s�[�ɐ���������true��Ԃ�
			return true;

		}

	}

	// �Y���̊Ǘ��ԍ����Ȃ�������false��Ԃ�
	return false;

}


/******************************************************************************
**	�e�N�X�`�����W�̓o�^
**
**	�g�p���@
**	unsigned int nLabel�E�E�E�ύX�������Ǘ��ԍ�
**	Vec2 *pVexTexture�E�E�E�e�N�X�`�����W���i�[���Ă���z��̐擪�|�C���^
******************************************************************************/
//bool SpriteLib::CreateVtxTexture( unsigned int nLabel, Vec2 *pVexTexture )
//{
//	// �Ǘ��ԍ��̌���
//	for( long nCntLabel = 0; nCntLabel < g_lMeshDataNum; nCntLabel++ )
//	{
//		// �Y���̊Ǘ��ԍ�����������R�s�[����������
//		if( g_lpMeshData[ nCntLabel ].nLabel == nLabel )
//		{
//			g_lpMeshData[ nCntLabel ].pVtxTex = pVexTexture;
//
//			// �R�s�[�ɐ���������true��Ԃ�
//			return true;
//
//		}
//
//	}
//
//	// �Y���̊Ǘ��ԍ����Ȃ�������false��Ԃ�
//	return false;
//
//}


/******************************************************************************
**	���b�V���t�B�[���h�̕`��(�|�W�V�������ʒu)
**
**	�g�p���@
**	unsigned int nLabel�E�E�E�`�悵�����Ǘ��ԍ�
******************************************************************************/
void SpriteLib::DrawIndex( unsigned int nLabel )
{
	// ���f���r���[�̑ޔ�
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	/* �}�g���b�N�X���� */


	/* �`��J�n */
	unsigned int *p = g_lpMeshData[ nLabel ].lpIdxBuff;
	glBegin( GL_TRIANGLE_STRIP );
	int NorFmtCnt = -1;
	for( unsigned int nCntDraw = 0; nCntDraw < g_lpMeshData[ nLabel ].dIdxSize; nCntDraw++ )
	{
		// �@���ݒ�
		NorFmtCnt += 0 + ( nCntDraw % g_lpMeshData[ nLabel ].NorFormat == 0 );
		glNormal3f(
			g_lpMeshData[ nLabel ].pNor[ NorFmtCnt ].x,
			g_lpMeshData[ nLabel ].pNor[ NorFmtCnt ].y,
			g_lpMeshData[ nLabel ].pNor[ NorFmtCnt ].z );

		// �F�ݒ�
		glColor4f( 1.0f, 1.0f, 0.2f, 1.0f );

		// ���W�ݒ�
		glVertex3d(
			g_lpMeshData[ nLabel ].pVtx[ p[ nCntDraw ] ].x,
			g_lpMeshData[ nLabel ].pVtx[ p[ nCntDraw ] ].y,
			g_lpMeshData[ nLabel ].pVtx[ p[ nCntDraw ] ].z );

	}
	glEnd();


	/* �}�g���b�N�X�����ɖ߂� */
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

}


/******************************************************************************
**	���b�V���t�B�[���h�̕`��(�|�W�V�����ω\)
**
**	�g�p���@
**	unsigned int nLabel�E�E�E�`�悵�����Ǘ��ԍ�
**	Vec pos�E�E�E�`��ʒu
******************************************************************************/
void SpriteLib::DrawIndex( unsigned int nLabel, Vector3 *pos )
{
	/* �`��J�n */
	unsigned int *p = g_lpMeshData[ nLabel ].lpIdxBuff;
	glBegin( GL_TRIANGLE_STRIP );
	glColor4f( 1.0f, 1.0f, 0.2f, 1.0f );
	int NorFmtCnt = 0;
	for( unsigned int nCntDraw = 0; nCntDraw < g_lpMeshData[ nLabel ].dIdxSize; nCntDraw++ )
	{
		// �@���ݒ�
		NorFmtCnt += ( g_lpMeshData[ nLabel ].NorFormat % nCntDraw == 0 );
		glNormal3f(
			g_lpMeshData[ nLabel ].pNor[ p[ NorFmtCnt ] ].x,
			g_lpMeshData[ nLabel ].pNor[ p[ NorFmtCnt ] ].y,
			g_lpMeshData[ nLabel ].pNor[ p[ NorFmtCnt ] ].z );

		// ���W�ݒ�
		glVertex3d(
			g_lpMeshData[ nLabel ].pVtx[ p[ nCntDraw ] ].x + pos->x,
			g_lpMeshData[ nLabel ].pVtx[ p[ nCntDraw ] ].y + pos->y,
			g_lpMeshData[ nLabel ].pVtx[ p[ nCntDraw ] ].z + pos->z );

	}
	glEnd();

}


/******************************************************************************
**	�폜�֐�
**
******************************************************************************/
void SpriteLib::DeleteIndex( void )
{
	// �f�[�^������ꍇ�͍폜
	if( g_lpMeshData != NULL )
	{
		delete[] g_lpMeshData;
	}

	// �A�h���X�Q�Ƃ���Ȃ��悤NULL��}��
	g_lpMeshData = NULL;
	g_lMeshDataNum = 0;

}