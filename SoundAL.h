#pragma once
/******************************************************************************
**	タイトル  :
**	ファイル名: SoundAL.h
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/6/20
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	更新内容
**	2016/6/24
**		ストップ、ポーズ機能追加、細かなバグ修正
**		ループ設定時に即反映できるよう修正
**
**
******************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include <alut.h>
#include <stdio.h>


/******************************************************************************
**	ライブラリリンク
******************************************************************************/
#pragma comment( lib, "OpenAL32.lib" )
#pragma comment( lib, "alut.lib" )


/******************************************************************************
**	マクロ定義
******************************************************************************/

/* ソース */
typedef struct
{
	ALuint source;
	bool bUse; // 使用中の有無
	bool bPlay; // 再生中

}SOUND_SOURCE;

/* データ音 */
typedef struct
{
	ALuint buffer; // データ音
	char *pFileName; // ファイルネーム
	ALuint id; // このデータのID,0～65535
	ALboolean bLoop;

}SOUND_BUFFERDATA;


/******************************************************************************
**	クラス定義
******************************************************************************/
class SoundAL
{
public:
	SoundAL();
	virtual ~SoundAL();

	// メソッド
	static bool Init();
	static int Uninit();
	static void Update();


	// Create
	static bool CreateSource( ALuint value );
	static bool CreateBuffer( ALuint value );
	static bool CreateBufferData( const char *pFileName, ALuint *out_id, ALboolean Loop );


	// Delete
	static void DeleteSource( ALuint id );
	static void DeleteBuffer( ALuint id );
	static void DeleteSourceAll();
	static void DeleteBufferAll();


	// Set
	static bool SetBuffer( ALuint id );
	static bool SetBuffer( ALuint id, ALboolean Loop );
	static void SetLoop( ALuint BufferID, int Loop );


	// Get


	// Play,Stop,Pause
	static bool PlaySoundAL( ALuint id );
	static void PlaySoundAll();
	static bool StopSound( ALuint id );
	static void StopSoundAll();
	static bool PauseSound( ALuint id );
	static void PauseSoundAll();


protected:
	// メンバ変数
	static SOUND_SOURCE *m_pSource; // スピーカー
	static SOUND_BUFFERDATA *m_pSoundBuffData; // 音データ
	static int m_CreateSource; // ソースの生成数
	static int m_CreateBuffer; // バッファの生成数
	static bool m_bInit; // 初期化しているか

};

