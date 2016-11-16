#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Vector3.h
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
#include < windows.h >
#include <string.h>
#include <stdio.h>


/******************************************************************************
**	���C�u���������N
******************************************************************************/



/******************************************************************************
**	�}�N����`
******************************************************************************/

/* Vector3 */
typedef struct tagVECTOR3
{
	float x;
	float y;
	float z;

}VECTOR3 , *LPVECTOR3;


/******************************************************************************
**	�N���X��`
******************************************************************************/
class Vector3 : public VECTOR3
{
	public:
	Vector3();
	Vector3( float x, float y, float z );
	virtual ~Vector3();

	// ���\�b�h

	/* �I�y���[�^ */
	// assignment operators
	Vector3& operator += ( const Vector3& );
	Vector3& operator -= ( const Vector3& );
	Vector3& operator *= ( const Vector3& );
	Vector3& operator *= ( const float );
	Vector3& operator /= ( const Vector3& );
	Vector3& operator /= ( const float );

	// unary operators
	Vector3 operator + () const;
	Vector3 operator - () const;

	// binary operators
	Vector3 operator + ( const Vector3& ) const;
	Vector3 operator - ( const Vector3& ) const;
	Vector3 operator * ( const Vector3& ) const;
	Vector3 operator * ( const float ) const;
	Vector3 operator / ( const Vector3& ) const;
	Vector3 operator / ( const float ) const;

};

