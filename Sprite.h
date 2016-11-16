#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Sprite.h
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/5/23
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
#include "Vector3.h"


/******************************************************************************
**	���C�u���������N
******************************************************************************/


/******************************************************************************
**	�}�N����`
******************************************************************************/

/* �C���f�b�N�X�o�b�t�@ */
typedef struct tagMESHDATA
{
	unsigned int nLabel; // �Ǘ��ԍ�
	unsigned int *lpIdxBuff; // �C���f�b�N�X�o�b�t�@�̐擪�A�h���X
	unsigned long dIdxSize; // �C���f�b�N�X��
	Vector3 *pVtx; // ���_���
	//Vec2 *pVtxTex; // �e�N�X�`�����W
	unsigned long dVtxSize; // ���_��
	Vector3 *pNor; // �@��
	unsigned long dNorSize; // �@����
	int NorFormat;

}MESHDATA, *LPMESHDATA;


/******************************************************************************
**	���O��Ԓ�`
******************************************************************************/
namespace SpriteLib
{
	/* ���b�V���f�[�^ */
	static LPMESHDATA g_lpMeshData = NULL;

	/* ���b�V���f�[�^�̐� */
	static unsigned g_lMeshDataNum = 0;

	/* �C���f�b�N�X�o�b�t�@�֘A */
	void CreateIndexBuffer( unsigned int *nLabel, unsigned int *lpIdxBuff, unsigned long size );
	bool CreateVtxBuffer( unsigned int nLabel, Vector3 *pVtx, unsigned long size );
	bool CreateNorBuffer( unsigned int nLabel, Vector3 *pNor, unsigned long size, int format );
	//bool CreateVtxTexture( unsigned int nLabel, Vec2 *pVexTexture );
	void DrawIndex( unsigned int nLabel );
	void DrawIndex( unsigned int nLabel, Vector3 *pos );
	void DeleteIndex( void );

}
