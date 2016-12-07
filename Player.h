#pragma once
/******************************************************************************
**	タイトル  :
**	ファイル名: .h
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016//
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
#include "Mode.h"


/******************************************************************************
**	ライブラリリンク
******************************************************************************/


/******************************************************************************
**	マクロ定義
******************************************************************************/


/******************************************************************************
**	クラス定義
******************************************************************************/
class Scene2DGL;
class Player
{
public:
	Player() {}
	virtual ~Player() {}

	// メソッド
	virtual void Init(int id) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void Attack0() = 0;
	virtual void Attack1() = 0;
	virtual void Move() = 0;


protected:
	// メンバ変数
	Scene2DGL *m_pScene;

	int m_Hp;
	float m_Forward_direction;
};

