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
class CharaSelect : public Mode
{
public:
	CharaSelect();
	virtual ~CharaSelect();


	// メソッド
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	void UpdateSelectCharactor();
	void UpdateAskToBattle();

private:
	// メンバ変数
	Scene2DGL *m_pBg;

	int m_selectId[2];								// 選択キャラクターID
	bool m_isDecide[2];								// 決定フラグ

	Scene2DGL *m_p1PDecide,		*m_p2PDecide;		// 決定(文字)
	Scene2DGL *m_p1PIcon,		*m_p2PIcon;			// １Ｐ２Ｐ(文字)
	Scene2DGL *m_p1PCharactor,	*m_p2PCharactor;	// キャラクター画像
	Scene2DGL *m_p1PJobName,	*m_p2PJobName;		// ジョブ名(文字)
	Scene2DGL *m_p1PActName[2],	*m_p2PActName[2];	// プレイヤー技名(文字)
	Scene2DGL *m_p1PBtnIcon[2], *m_p2PBtnIcon[2];	// ボタンアイコン(AX)

	Scene2DGL *m_pDecideMask,	*m_pAskMask;		// 決定マスク(前の画面全体, 確認ウィンドウ)
	Scene2DGL *m_pAskToStart;						// 勝負をはじめる？
	Scene2DGL *m_pYes,			*m_pNo;				// はい　いいえ
};

