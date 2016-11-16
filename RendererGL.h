#pragma once
/******************************************************************************
**	タイトル  :
**	ファイル名: Renderer.h
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
#include <gl\gl.h>
#include <gl\glu.h>
#include "Color.h"
#include "Vector3.h"


/******************************************************************************
**	ライブラリリンク
******************************************************************************/

/* OpenGL Library */
#pragma comment ( lib , "opengl32.lib" )
#pragma comment ( lib , "glu32.lib" )


/* 音の再生に必要なコンポーネント(FPSなどにも使用) */
#pragma comment ( lib , "winmm.lib" )


/******************************************************************************
**	マクロ定義
******************************************************************************/

// 円周率
#define GL_PI ( 3.141592654f )

// 重力
#define GL_GRAVITY ( 9.8f )

// 背景色
#define BGCOLOR_R ( 0.0f )
#define BGCOLOR_G ( 0.0f )
#define BGCOLOR_B ( 0.0f )
#define BGCOLOR_A ( 1.0f )


/* レンダーステート */
typedef enum
{
	GLRS_FILLMODE = 0,
	GLRS_CULLMODE,
	GLRS_LIGHTING,
	GLRS_TEXTURE,
	GLRS_MAX

}GLRENDERSTATE;

/* フィルモード */
enum GLFILLMODE
{
	GLFILL_POINT = 0,
	GLFILL_WIREFRAME,
	GLFILL_SOLID,
	GLFILL_MAX

};

/* カリングモード */
enum GLCULL
{
	GLCULL_CU = 0,
	GLCULL_CUU,
	GLCULL_MAX

};


/* 動作ステート */
typedef enum
{
	MOVESTATE_NONE = 0, // 待機中
	MOVESTATE_MOVE, // 移動中
	MOVESTATE_STOP, // 停止中
	MOVESTATE_MAX

}MOVESTATE;


/* アニメーション */
typedef struct tagANIMETION
{
	int nCounterAnim; // 1フレーム毎切換えカウント
	int nChangeTimming; // アニメーション切換タイミング
	int nPosPatternAnim_X; // 画像の位置X座標
	int nPosPatternAnim_Y; // 画像の位置Y座標
	float fPattern_X; // X座標に対してのアニメーション間隔
	float fPattern_Y; // Y座標に対してのアニメーション間隔
	float fAnimWidth; // アニメーション切換間隔 幅
	float fAnimHeight; // アニメーション切換間隔 高さ

}ANIMETION, *LPANIMETION;


/* ポジション */
typedef struct tagOBJECT3D
{
	// 位置、大きさ
	Vector3 pos; // ポジション
	Vector3 accPos; // 移動量(速度量)
	Vector3 posSet; // 目的位置
	Vector3 rot; // 回転
	Vector3 rotMove; // 回転量
	Vector3 rotSetMove; // 目的角度
	Vector3 scl; // 大きさ
	Vector3 normal; // 法線
	//D3DXMATRIX mtxWorld; // ワールドマトリックス
	Color col; // 色
	float velocity; // ジャンプ初速度
	float fall; // 落下速度
	float velocityJumpVec; // ジャンプ初速量
	float accJumpVec; // ジャンプ速度量
	float moveVec; // 進む距離の長さ
	float length2D; // 方形対角線
	float length3D; // 立方体対角線
	float angleXZ; // 斜辺角
	float angleYX; // 斜辺角
	float width; // 幅
	float height; // 高さ
	float depth; // 奥行き
	int nLife; // 寿命、HP
	int JumpCnt; // ジャンプ中のカウント
	bool bUse; // 使用中の有無
	bool bUpdate; // アップデート有無
	bool bDraw; // 描画有無
	bool bHit; // 衝突判定

	// アニメーション関連
	ANIMETION anim;

	// 各種ステート
	MOVESTATE movestate;

}OBJECT3D, *LPOBJECT3D;


/******************************************************************************
**	クラス定義
******************************************************************************/

/* レンダラGLクラス */
class RendererGL
{
public:
	RendererGL();
	virtual ~RendererGL();

	// メソッド
	HRESULT Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow );
	int Uninit();
	void Update();

	bool BeginDraw();
	void EndDraw();

	// デバイス関連の受け渡し
	static HDC GetHDC();
	static HGLRC GetHGLRC();


	// Set,Get
	static void SetRenderMode( GLRENDERSTATE glrs, DWORD value );
	static void SetRenderMode( DWORD glrs, GLboolean value );
	static void SetBgColor( float r, float g, float b, float a );
	static void SetBgColor( Color *col );
	static void SetBgColor( unsigned long col );
	static Color GetBgColor();


private:
	// メンバ変数
	int m_nFormat; // 描画のフォーマット番号

	// デバイス関連
	static HDC m_hDC; // デバイスコンテキスト
	static HGLRC m_hGLRC; // OpenGLのデバイス

	// 色
	static Color m_BgCol;

};

