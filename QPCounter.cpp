/******************************************************************************
**	タイトル  : 高解像度タイマーFPS QueryPerformanceCounter
**	ファイル名: QPCounter.cpp
**	作成者    : AT-12A-244 出席番号 16 木村 祥貴
**	作成日    : 2015/7/20
******************************************************************************/

/******************************************************************************
**	内容
**
**	時間やカウントに関するものを更に細かく値を取れる関数
**	timeGetTime()よりより細かく数値を取ることができる高解像度タイマー
**	ただ、PCやハードによっては対応していないので注意
**	FPSなどの値をより精密に測れることができる
**	また、音ゲーやエフェクトのタイミングなど、ズレてはならないものに対して
**	非常に有効
**
******************************************************************************/

/******************************************************************************
**	更新内容
**
******************************************************************************/


/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include "main.h"
#include "QPCounter.h"
//#include "debugProc.h"


/******************************************************************************
**	マクロ定義
******************************************************************************/

/**** マジックナンバー ****/

/*** FPS関連 ***/

/* 高解像度がFALSE時に使用する周波数の値 */
#define FALSE_FREQ ( 1000 )

/* FPS算出間隔時間 */
#define FPS_COUNT ( 500 )

/* FPS表示文字数 */
#define STR_FPS ( 10 )

/* 表示文字カラー */
#define TEXTCOLOR_FPS_R ( 255 )
#define TEXTCOLOR_FPS_G ( 255 )
#define TEXTCOLOR_FPS_B ( 0 )
#define TEXTCOLOR_FPS_A ( 60 )

/* 表示位置 */
#define POS_FPS_X ( 0 )
#define POS_FPS_Y ( 0 )

/* 時間解像度 */
#define PERFORMANCETIME_MS ( 60 )


/******************************************************************************
**	プロトタイプ宣言
******************************************************************************/


/******************************************************************************
**	グローバル変数
******************************************************************************/


/******************************************************************************
**	関数名: cQPCounter::cQPCounter
**		関数の概要
**	引数  : void
**	説明  : cQPCounterのコンストラクタ
********************************************************************************/
QPCounter::QPCounter( void )
{
	/**** 変数宣言 ****/
	LARGE_INTEGER ltQPFreq; // 高解像度周波数値


	/**** 高解像度が使用可能かの有無 ****/
	// 対応している時は高解像度モードをオン
	// 更にPCのシステム周波数を保存
	if( QueryPerformanceFrequency( &ltQPFreq ) ) // システムの周波数を取得
	{
		c_bPerformance = true;
		c_llSysFreq = ltQPFreq.QuadPart;


	}
	// 使えねぇ～時はオフ
	// いつものtimeGetTime()で代用する(周波数はFALSE_FREQに依存する)
	else
	{
		c_bPerformance = false;
		c_llSysFreq = ( LONGLONG )FALSE_FREQ;

		/* 分解能 */
		timeBeginPeriod( 1 );

	}

	/* 高解像度カウンターのクラスを初期化 */
	if( FAILED( QPCounter::Init() ) )
	{
		// 失敗したら、timeGetTime()で取得
		c_bPerformance = false;
		Init();

	}


	/**** キッチンタイマーの初期化 ****/
	c_bRanTimmer = false; // タイマー停止状態
	c_nMs = 0;
	c_cm = CHECKMETHOD_MAX;
	c_llStartTime = c_llStopTime = c_llContinueTime = c_llLastTime = 0;

}


/******************************************************************************
**	関数名: cQPCounter::~cQPCounter
**		関数の概要
**	引数  : void
**	説明  : cQPCounterのデストラクタ
********************************************************************************/
QPCounter::~QPCounter( void )
{
	/* 分解能を戻す */
	if( !c_bPerformance )
	{
		timeEndPeriod( 1 );

	}

}


/******************************************************************************
**	関数名: InitQPCounter
**		関数の概要
**	引数  : void
**	戻り値: HRESULT
**	説明  : 初期化
******************************************************************************/
HRESULT QPCounter::Init( void )
{
	// タイマーをセットする
	if( c_bPerformance )
	{
		/**** 変数宣言 ****/
		LARGE_INTEGER ltQPCnter; // 高解像度タイマー


		// 高解像度が使用可
		if( !QueryPerformanceCounter( &ltQPCnter ) ) // 時間の取得
		{
			return E_FAIL;

		}

		// タイマーのセット
		c_llFPSLastTime = c_llExecLastTime = ltQPCnter.QuadPart;

	}
	else
	{
		// 高解像度が使用不可
		c_llFPSLastTime = c_llExecLastTime = ( LONGLONG )timeGetTime();

	}

	/* その他、FPSカウンター、FPS値の初期化 */
	c_llFrameCount = 0;
	c_nCntFPS = 0;
	SetFPS( FPS ); // デフォルトで60が引数が自動で代入されている

	return S_OK;

}


/******************************************************************************
**	関数名: SetFPS
**		関数の概要
**	引数  : FPS値 int _nFPS
**	戻り値: void
**	説明  : FPS値をセット
******************************************************************************/
void QPCounter::SetFPS( int _nFPS )
{
	c_nFPS = _nFPS;

}


/******************************************************************************
**	関数名: SetPerformance
**	関数の概要
**	引数  : 解像度 nPerformance
**	戻り値: void
**	説明  : 解像度の設定
******************************************************************************/
void QPCounter::SetPerfoemance( int nPeformance )
{
	c_nPerformance = c_nPerformance;

}


/******************************************************************************
**	関数名: CountFPS
**		関数の概要
**	引数  : void
**	戻り値: bool
**	説明  : FPSカウント
******************************************************************************/
void QPCounter::CountFPS( void )
{
	/**** 変数宣言 ****/
	LONGLONG llCurrentTime; // 時間を取得


	/* 高解像度タイマーが使用可能有無 */
	if( c_bPerformance )
	{
		// 高解像度モード

		// 時間の取得
		LARGE_INTEGER ltQPCnter;
		QueryPerformanceCounter( &ltQPCnter );
		llCurrentTime = ltQPCnter.QuadPart;

	}
	else
	{
		// 低解像度モード

		// 時間の取得( timeGetTime() )
		llCurrentTime = ( LONGLONG )timeGetTime();

	}

	// FPS算出
	if( ( ( llCurrentTime - c_llFPSLastTime ) * PERFOEMANCE_FPS / c_llSysFreq ) >= FPS_COUNT )
	{
		c_nCntFPS = ( ( c_llFrameCount * PERFOEMANCE_FPS ) / ( ( llCurrentTime - c_llFPSLastTime ) * PERFOEMANCE_FPS / c_llSysFreq ) );

		/* 現在の時間を最後の時間として代入、フレームカウントをクリア */
		c_llFPSLastTime = llCurrentTime;
		c_llFrameCount = 0;

	}

}


/******************************************************************************
**	関数名: cQPCounter::CallFPS
**		関数の概要
**	引数  : void
**	戻り値: bool
**	説明  : FPS処理
******************************************************************************/
bool QPCounter::CallFPS( void )
{
	/**** 変数宣言 ****/
	LONGLONG llCurrentTime; // 時間を取得


	/* 高解像度タイマーが使用可能有無 */
	if( c_bPerformance )
	{
		// 高解像度モード

		// 時間の取得
		LARGE_INTEGER ltQPCnter;
		QueryPerformanceCounter( &ltQPCnter );
		llCurrentTime = ltQPCnter.QuadPart;

	}
	else
	{
		// 低解像度モード

		// 時間の取得( timeGetTime() )
		llCurrentTime = ( LONGLONG ) timeGetTime();

	}


	/**** FPS処理 ****/

	// FPS毎の処理( デフォルトで1/60回毎に更新 )
	if( ( ( llCurrentTime - c_llExecLastTime ) * PERFOEMANCE_FPS / c_llSysFreq ) >= ( 1000 / c_nFPS ) )
	{
		// 更新できるタイミングでtrueを返す
		return true;

	}
	else
	{
		// 更新できないタイミングはfalseを返す
		return false;

	}

}


/******************************************************************************
**	関数名: EndFPS
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : 最後の処理
******************************************************************************/
void QPCounter::EndFPS( void )
{
	/**** 変数宣言 ****/
	LONGLONG llCurrentTime; // 時間を取得


	/* 高解像度タイマーが使用可能有無 */
	if ( c_bPerformance )
	{
		// 高解像度モード

		// 時間の取得
		LARGE_INTEGER ltQPCnter;
		QueryPerformanceCounter( &ltQPCnter );
		llCurrentTime = ltQPCnter.QuadPart;

	}
	else
	{
		// 低解像度モード

		// 時間の取得( timeGetTime() )
		llCurrentTime = ( LONGLONG )timeGetTime();

	}

	// 現在の時間を最後の時間として代入、更新ごとにフレームカウントをプラス
	c_llExecLastTime = llCurrentTime;
	c_llFrameCount++;

}


/******************************************************************************
**	関数名: DrawFPS
**		関数の概要
**	引数  : フォントデバイス pFont
**	戻り値: void
**	説明  : FPS値を表示
******************************************************************************/
void QPCounter::DrawFPS()
{
	//PrintDebugProc( "FPS:%d\n", c_nCntFPS );

}


/******************************************************************************
**	関数名: SetTimmerMs
**	関数の概要
**	引数  : セットする時間 int ms , チェック方式 CHECKMETHOD cm
**	戻り値: 成否 bool
**	説明  : チェックする時間をチェック方式にしたがってチェックしていく
******************************************************************************/
bool QPCounter::SetTimmerMs( int ms , CHECKMETHOD cm )
{
	c_nMs = ms;
	c_cm = cm;
	c_PerformanceTime = PERFORMANCETIME_MS;
	c_bRanTimmer = false;

	return true;

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値: 成否 bool
**	説明  :
******************************************************************************/
bool QPCounter::StartTimmer( void )
{
	// 高解像度タイマーに対応しているか
	if( c_bPerformance )
	{
		// 高解像度モード

		// 時間の取得
		LARGE_INTEGER ltQPCnter;
		QueryPerformanceCounter( &ltQPCnter );
		c_llStartTime = ltQPCnter.QuadPart;

	}
	else
	{
		// 低解像度モード

		// 時間の取得( timeGetTime() )
		c_llStartTime = ( LONGLONG )timeGetTime();

	}

	// タイマー起動をON
	c_bRanTimmer = true;

	return true;

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値: 成否 bool
**	説明  :
******************************************************************************/
bool QPCounter::CheckTimmer( void )
{
	// タイマーがONになていたら処理をする
	if( c_bRanTimmer == true )
	{
		/* 変数宣言 */
		LONGLONG llCurrentTime; // 時間を取得

		// 高解像度タイマーに対応しているか
		if( c_bPerformance )
		{
			// 高解像度モード

			// 時間の取得
			LARGE_INTEGER ltQPCnter;
			QueryPerformanceCounter( &ltQPCnter );
			llCurrentTime = ltQPCnter.QuadPart;

		}
		else
		{
			// 低解像度モード

			// 時間の取得( timeGetTime() )
			llCurrentTime = ( LONGLONG )timeGetTime();

		}

		// 時間経過の確認
		/****************************************
		 * 
		 * (現在の時間 - 再開した時間) + (停止した時間 - 開始した時間)
		 * 一回も停止しなかった場合でも開始した時間がマイナス値になる
		 * 
		 ***************************************/
		if( ( ( ( llCurrentTime - c_llContinueTime ) + ( c_llStopTime - c_llStartTime ) ) * c_PerformanceTime / c_llSysFreq ) >= c_nMs )
		{
			// 繰り返し指定
			switch( c_cm )
			{
				case CHECKMETHOD_ONLY_ONCE: // 1回のみはタイマーをOFFにする
					c_bRanTimmer = false;

					break;

				case CHECKMETHOD_REPETITION: // 繰り返しは取得した時間をStartTimeにリセットする
					c_llStartTime = llCurrentTime;
					c_llContinueTime = c_llStopTime = 0;

					break;

				case CHECKMETHOD_REGINTVL: // 一定間隔は・・・
					/***** バージョンアップにて実装 **/
					break;

				default: // エラー回避のため、ここはfalseにする
					c_bRanTimmer = false;

					break;

			}

			// 指定された時間だったらtrueを返す
			return true;

		}
		else
		{
			// 指定された時間外だったらfalseを返す
			return false;

		}
		
	}
	else
	{
		// OFF(false)だった場合はfalseを返す
		return false;

	}

	return false;

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値: 成否 bool
**	説明  :
******************************************************************************/
bool QPCounter::StopTimmer( void )
{
	/* 最初に時間を受け取りタイマーを止める */
	// タイマーがONだったら処理をする
	if( c_bRanTimmer )
	{
		/* 変数宣言 */
		LONGLONG llCurrentTime; // 時間を取得

		// 高解像度タイマーに対応しているか
		if( c_bPerformance )
		{
			// 高解像度モード

			// 時間の取得
			LARGE_INTEGER ltQPCnter;
			QueryPerformanceCounter( &ltQPCnter );
			llCurrentTime = ltQPCnter.QuadPart;

		}
		else
		{
			// 低解像度モード

			// 時間の取得( timeGetTime() )
			llCurrentTime = ( LONGLONG )timeGetTime();

		}

		// 時間の受け渡し、タイマーの停止
		c_llStopTime = llCurrentTime;
		c_bRanTimmer = false;

		return true;

	}
	else
	{
		// 既にOFFだった場合はfalseを返す
		return false;

	}

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値: 成否 bool
**	説明  :
******************************************************************************/
bool QPCounter::RestartTimmer( void )
{
	/* 最初にタイマーをONにしてから時間を受け取る */
	// タイマーがOFFだったら処理をする
	if( c_bRanTimmer == false )
	{
		/* 変数宣言 */
		LONGLONG llCurrentTime; // 時間を取得

		// 高解像度タイマーに対応しているか
		if( c_bPerformance )
		{
			// 高解像度モード

			// 時間の取得
			LARGE_INTEGER ltQPCnter;
			QueryPerformanceCounter( &ltQPCnter );
			llCurrentTime = ltQPCnter.QuadPart;

		}
		else
		{
			// 低解像度モード

			// 時間の取得( timeGetTime() )
			llCurrentTime = ( LONGLONG )timeGetTime();

		}

		// 時間の受け渡し、タイマーの再生
		c_llContinueTime = llCurrentTime;
		c_bRanTimmer = true;

		return true;

	}
	else
	{
		// 既にOFFだった場合はfalseを返す
		return false;

	}

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値: 成否 bool
**	説明  :
******************************************************************************/
bool QPCounter::ResetTimmer( void )
{
	c_bRanTimmer = false;
	c_nMs = 0;
	c_cm = CHECKMETHOD_MAX;
	c_llStartTime = c_llStopTime = c_llContinueTime = c_llLastTime = 0;

	return true;

}


/******************************************************************************
**	関数名: CreateRandomNumber
**	関数の概要
**	引数  : 数値の範囲 int Min , int Max , 乱数の種 seed(デフォルトで1が代入)
**	戻り値: 乱数 double型
**	説明  : 乱数作成
******************************************************************************/
double CreateRandomNumber( int nRange_Min , int nRange_Max , int seed )
{
	/**** 変数宣言 ****/
	LARGE_INTEGER QPFreq; // 周波数
	LARGE_INTEGER QPCntr; // 現在の時間
	static long seed2; // 乱数調整用


	/* 高解像度タイマーが使用可能有無 */
	if( QueryPerformanceFrequency( &QPFreq ) )
	{
		// 高解像度モード

		// 時間の取得
		QueryPerformanceCounter( &QPCntr );

	}
	else
	{
		// 低解像度モード

		// 時間の取得( timeGetTime() )
		QPCntr.QuadPart = ( LONGLONG )timeGetTime();

	}

	// 乱数作成
	seed2 = rand();
	srand( seed * seed2 );
	double RandNum = ( int )( QPCntr.QuadPart / QPFreq.QuadPart * rand() ) % nRange_Max;

	// 範囲チェック 
	/********************************************
	 * 
	 * 範囲以下の時は以下の計算をする
	 * 範囲最小値と生成された乱数(以下乱数)の差分を乱数に足す
	 * 範囲の差分値でrand()で生成された乱数の余りを足す = 範囲内で乱数が生成される
	 * 
	********************************************/
	if( RandNum < nRange_Min )
	{
		RandNum += nRange_Min - RandNum + ( rand() % ( nRange_Max - nRange_Min ) );

	}

	return RandNum;

}

