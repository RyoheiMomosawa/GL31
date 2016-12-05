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
#include "Player.h"


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
class PlayerSamurai : public Player
{
public:
	PlayerSamurai();
	virtual ~PlayerSamurai();


	// メソッド
	void Init(int id);
	void Uninit();
	void Update();
	void Draw();

	void Attack0();
	void Attack1();
	void Move();

private:

};

