/******************************************************************************
	タイトル  : 高解像度タイマーFPS
	ファイル名: QPCounter.h
	作成者    : AT-12A-244 出席番号 16 木村 祥貴
	作成日    : 2015/7/20
	バージョン: 1.0.1
******************************************************************************/

/******************************************************************************
	更新内容

	2015/7/28	ver1.0.0
				高解像度タイマー仕様のFPSをサポート
				上記が使用出来ない場合は低解像度をサポートする

	2015/7/29	ver1.0.1
				高解像度タイマーのサポートを任意で変更できるように
				変更の際は"bool c_bPerformance"を呼び、値を代入する

	2015/9/22	ver.1.2.0
				キッチンタイマー実装
				指定された時間を知らせるように
				正確に時間指定で動かしたいものに最適

******************************************************************************/

/******************************************************************************
	インクルードガード
******************************************************************************/
#ifndef _QPCCOUNTER_H_
#define _QPCCOUNTER_H_


/******************************************************************************
	インクルードファイル
******************************************************************************/
#include "main.h"

/******************************************************************************
	ライブラリリンク
******************************************************************************/


/******************************************************************************
	マクロ定義
******************************************************************************/

/**** マジックナンバー ****/

/* FPS値算出更新度 */
#define FPSCOUNT ( 500 )

/* FPS更新頻度 */
#define FPS ( 60 )

/* 解像度率 */
#define PERFOEMANCE_FPS ( 1000 )


/**** 構造体宣言 ****/
typedef enum
{
	CHECKMETHOD_ONLY_ONCE = 0, // 一回のみ
	CHECKMETHOD_REPETITION , // 繰り返し
	CHECKMETHOD_REGINTVL , // 一定間隔
	CHECKMETHOD_MAX

}CHECKMETHOD; // タイマーのチェック方法


/**** クラス定義 ****/
class QPCounter
{
	public :
		QPCounter();
		~QPCounter();

		/* プロトタイプ宣言 */
		// FPS、高解像度タイマーの設定
		HRESULT Init( void );
		void SetFPS( int _nFPS = FPS );
		void SetPerfoemance( int nPerformance = PERFOEMANCE_FPS );
		void CountFPS( void );
		bool CallFPS( void ); // 更新するタイミングかどうか
		void EndFPS( void ); // 更新した最後のタイミング
		//int Ran( void );
		void DrawFPS();

		// キッチンタイマー
		bool SetTimmerMs( int ms , CHECKMETHOD cm ); // ms単位で時間経過を計る時間のセット
		bool StartTimmer( void ); // 計測スタート
		bool CheckTimmer( void ); // 指定された時間が経過したかどうか
		bool StopTimmer( void ); // 時間をストップ
		bool RestartTimmer( void ); // 時間経過をリセット
		bool ResetTimmer( void ); // 指定された時間をリセット

		/* 変数宣言 */
		bool c_bPerformance; // 高解像度タイマーが仕様できるか
		bool c_bRanTimmer; // タイマーが動いているか


	private:
		DWORD c_nCntFPS; // 現在のFPS値
		DWORD c_nPerformance; // 解像度
		DWORD c_nFPS; //	更新するタイミング
		DWORD c_llFrameCount; // 更新・描画した回数
		//LONGLONG c_llCurrentTime; // 現在の時間
		LONGLONG c_llExecLastTime; // 更新・描画した回数
		LONGLONG c_llFPSLastTime; // FPSの数値を取得した最後の時間
		LONGLONG c_llSysFreq; // システムの周波数

		// キッチンタイマー
		int c_nMs; // セットされる時間(ms)
		int c_PerformanceTime; // 時間解像度
		CHECKMETHOD c_cm; // 時間経過のチェック方式
		LONGLONG c_llStartTime; // 開始時間
 		LONGLONG c_llLastTime; // 最後の時間
		LONGLONG c_llContinueTime; // 続きの時間
		LONGLONG c_llStopTime; // 止めた時間

};


/******************************************************************************
	プロトタイプ宣言
******************************************************************************/
double CreateRandomNumber( int nRange_Min , int nRange_Max , int seed );


/******************************************************************************
	インクルードガード
******************************************************************************/
#endif

