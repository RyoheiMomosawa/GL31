/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: .cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016//
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "ImageTGA.h"
#include "RendererGL.h"
#include <Windows.h>
#include <stdio.h>


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
ImageTGA::ImageTGA()
{
	ZeroMemory( &TGATexImg, sizeof TEXTUREIMAGE );

}


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
ImageTGA::~ImageTGA()
{
}


/******************************************************************************
**	�֐���: Read
**	�֐��̊T�v
**	����  : �t�@�C���p�X const char *FileName
**	�߂�l: �Ǎ������� true�A���s�� false
**	����  :
******************************************************************************/
inline bool ImageTGA::Read( const char *FileName )
{
	/* �ϐ��錾 */
	FILE *fp; // �t�@�C���|�C���^
	unsigned int bytePerPixel; // 1�s�N�Z��������̑傫��
	unsigned char header[ 18 ]; // �w�b�_���
	unsigned int temp; // �R�s�[�p��Ƙg


	// �t�@�C���I�[�v��
	// �G���[�̕ԋp�A�t�@�C���|�C���^��NULL�������ꍇ��false��Ԃ�
	if( fopen_s( &fp, FileName, "rb" ) != 0 || fp == NULL )
	{
		return false;

	}


	// �w�b�_�̓ǂݍ���
	fread_s( header, sizeof( unsigned char ) * 18, 1, sizeof( header ), fp );


	// �傫���̐ݒ�
	TGATexImg.width = header[ 13 ] * 256 + header[ 12 ];
	TGATexImg.height = header[ 15 ] * 256 + header[ 14 ];


	// 1�s�N�Z���̑傫��
	TGATexImg.bpp = header[ 16 ];


	// �s�N�Z���T�C�Y�w��
	switch( TGATexImg.bpp )
	{
		case 24:
			TGATexImg.format = TGATexImg.InternalFormat = GL_RGB;

			break;

		case 32:
			TGATexImg.format = TGATexImg.InternalFormat = GL_RGBA;

			break;

		default:

			return false;

	}


	// 1�s�N�Z��������̃o�C�g��
	bytePerPixel = TGATexImg.bpp / 8;


	// �摜�̃f�[�^�T�C�Y
	TGATexImg.ImageSize = TGATexImg.width * TGATexImg.height*bytePerPixel;


	// �f�[�^�T�C�Y���������m��
	TGATexImg.ImageData = new unsigned char[ TGATexImg.ImageSize ];


	// �e�N�Z���f�[�^�̓ǂݍ���
	fread_s( TGATexImg.ImageData, TGATexImg.ImageSize, 1, TGATexImg.ImageSize, fp );


	// �e�N�Z���f�[�^���R���o�[�g
	for( unsigned int i = 0; i < TGATexImg.ImageSize; i += bytePerPixel )
	{
		temp = TGATexImg.ImageData[ i ];
		TGATexImg.ImageData[ i ] = TGATexImg.ImageData[ i + 2 ];
		TGATexImg.ImageData[ i + 2 ] = temp;

	}


	// �t�@�C���N���[�Y
	fclose( fp );


	// �������Atrue��Ԃ�
	return true;

}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l:
**	����  :
******************************************************************************/
unsigned int ImageTGA::CreateTexture( const char *FileName )
{
	/* �ϐ��錾 */
	unsigned int texture; // �e�N�X�`��ID
	unsigned char *image = NULL; // �摜�f�[�^


	// �t�@�C���ǂݍ���
	Read( FileName );


	//�e�N�X�`������
	glGenTextures( 1, &texture );


	// �e�N�X�`���̃o�C���h
	glBindTexture( GL_TEXTURE_2D, texture );


	// 1�s�N�Z���̃T�C�Y���w��
	switch( TGATexImg.format )
	{
		case GL_RGB: // 24bit�́u4�v���w��
			glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );

			break;

		case GL_RGBA: // 32bit�́u1�v���w��
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

			break;

		default:

			break;
	
	}


	// �e�N�X�`���̊g�k���@�̎w��
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );


	// �e�N�X�`���̊��蓖��
	glTexImage2D( GL_TEXTURE_2D, 0, TGATexImg.InternalFormat, TGATexImg.width, TGATexImg.height, 0, TGATexImg.format, GL_UNSIGNED_BYTE, TGATexImg.ImageData );
	//gluBuild2DMipmaps( GL_TEXTURE_2D, TGATexImg.InternalFormat, TGATexImg.width, TGATexImg.height, TGATexImg.format, GL_UNSIGNED_BYTE, TGATexImg.ImageData );


	glBindTexture( GL_TEXTURE_2D, 0 );


	// �������̉��
	if( TGATexImg.ImageData != NULL )
	{
		delete[] TGATexImg.ImageData;
		TGATexImg.ImageData = NULL;

	}

	
	return texture;

}
