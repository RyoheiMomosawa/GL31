#pragma once
/******************************************************************************
**	タイトル  :
**	ファイル名: Vector3.h
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/4/22
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	更新内容
**
**
**
******************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include < windows.h >
#include <string.h>
#include <stdio.h>


/******************************************************************************
**	ライブラリリンク
******************************************************************************/



/******************************************************************************
**	マクロ定義
******************************************************************************/

/* Vector3 */
typedef struct tagVECTOR3
{
	float x;
	float y;
	float z;

}VECTOR3 , *LPVECTOR3;


/******************************************************************************
**	クラス定義
******************************************************************************/
class Vector3 : public VECTOR3
{
	public:
	Vector3();
	Vector3( float x, float y, float z );
	virtual ~Vector3();

	// メソッド

	/* オペレータ */
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

