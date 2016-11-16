/******************************************************************************
**	タイトル  :
**	ファイル名: SoundAL.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/6/20
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include "SoundAL.h"
#include <string.h>


/******************************************************************************
**	静的メンバ変数
******************************************************************************/
SOUND_SOURCE *SoundAL::m_pSource; // スピーカー
SOUND_BUFFERDATA *SoundAL::m_pSoundBuffData; // 音データ
int SoundAL::m_CreateSource; // ソースの生成数
int SoundAL::m_CreateBuffer; // バッファの生成数
bool SoundAL::m_bInit; // 初期化しているか


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
SoundAL::SoundAL()
{
	m_pSource = NULL;
	m_pSoundBuffData = NULL;
	m_CreateBuffer = m_CreateSource = 0;
	m_bInit = false;

}


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
SoundAL::~SoundAL()
{
}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  : void
**	戻り値: bool
**	説明  : 初期化処理
******************************************************************************/
bool SoundAL::Init()
{
	if( !m_bInit )
	{
		alutInit( NULL, NULL );
		m_bInit = true;

	}
	m_pSource = NULL;
	m_pSoundBuffData = NULL;
	m_CreateBuffer = m_CreateSource = 0;

	return true;

}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
int SoundAL::Uninit()
{
	// ソース
	if( m_pSource != NULL )
	{
		delete[] m_pSource;
		m_pSource = NULL;
		m_CreateSource = 0;

	}
	else
	{
		return 1;

	}

	// ソース
	if( m_pSoundBuffData != NULL )
	{
		// ファイル名削除
		for( int i = 0; i < m_CreateBuffer; i++ )
		{
			delete[] m_pSoundBuffData[ i ].pFileName;
			m_pSoundBuffData[ i ].pFileName = NULL;

		}

		delete[] m_pSoundBuffData;
		m_pSoundBuffData = NULL;
		m_CreateBuffer = 0;

	}
	else
	{
		return 1;

	}

	if( m_bInit )
	{
		alutExit();
		m_bInit = false;

	}

	return 0;

}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void SoundAL::Update()
{
	int value = 0;
	for( ALuint i = 0; i < m_CreateSource; i++ )
	{
		if( m_pSource[ i ].bUse && m_pSource[ i ].bPlay )
		{
			alGetSourcei( m_pSource[ i ].source, AL_SOURCE_STATE, &value );
			if( value == AL_STOPPED )
			{
				printf( "再生終了" );
				alSourcei( m_pSource[ i ].source, AL_INITIAL, NULL );
				m_pSource[ i ].bUse = false;
				m_pSource[ i ].bPlay = false;

			}
			else if( value == AL_PAUSED )
			{
				m_pSource[ i ].bPlay = false;

			}

		}

	}

}


/******************************************************************************
**	関数名: CreateSource
**	関数の概要
**	引数  : ALuint value
**	戻り値: bool
**	説明  :
******************************************************************************/
bool SoundAL::CreateSource( ALuint value )
{
	// 未生成の確認
	if( m_pSource == NULL )
	{
		m_CreateSource = value;
		m_pSource = new SOUND_SOURCE[ m_CreateSource ];
		alGenSources( m_CreateSource, &m_pSource[ 0 ].source );
		for( ALuint i = 0; i < m_CreateSource; i++ )
		{
			m_pSource[ i ].bUse = false;
			m_pSource[ i ].bPlay = false;

		}
		return true;

	}

	// 生成に失敗
	return false;

}


/******************************************************************************
**	関数名: CreateBuffer
**	関数の概要
**	引数  : ALuint value
**	戻り値: bool
**	説明  :
******************************************************************************/
bool SoundAL::CreateBuffer( ALuint value )
{
	// 未生成の確認
	if( m_pSoundBuffData == NULL )
	{
		m_CreateBuffer = value;
		m_pSoundBuffData = new SOUND_BUFFERDATA[ m_CreateBuffer ];
		for( ALuint i = 0; i < m_CreateBuffer; i++ )
		{
			m_pSoundBuffData[ i ].buffer = 0;
			m_pSoundBuffData[ i ].id = 0;
			m_pSoundBuffData[ i ].pFileName = 0;

		}
		return true;
	}

	// 生成に失敗
	return false;
}


/******************************************************************************
**	関数名: CreateBufferData
**	関数の概要
**	引数  : const char *pFileName, ALuint *out_ID, ALboolean Loop = AL_FALSE
**	戻り値: bool
**	説明  :
******************************************************************************/
bool SoundAL::CreateBufferData( const char *pFileName, ALuint *out_ID, ALboolean Loop = AL_FALSE )
{
	// ファイルオープン
	ALuint buffer;
	buffer = alutCreateBufferFromFile( pFileName );

	// データ生成に成功
	if( buffer != 0 )
	{
		for( ALuint i = 0; i < m_CreateBuffer; i++ )
		{
			if( m_pSoundBuffData[ i ].buffer == NULL )
			{
				int nFileNameLen = strnlen_s( pFileName, 256 );
				m_pSoundBuffData[ i ].buffer = buffer;
				m_pSoundBuffData[ i ].id = i;
				m_pSoundBuffData[ i ].pFileName = new char[ nFileNameLen + 1 ];
				strcpy_s( m_pSoundBuffData[ i ].pFileName, nFileNameLen + 1, pFileName );
				m_pSoundBuffData[ i ].bLoop = Loop;

				// IDの返却
				*out_ID = i;

				return true;

			}

		}

	}

	// 生成に失敗
	*out_ID = -1;
	return false;

}


/******************************************************************************
**	関数名: DeleteSource
**	関数の概要
**	引数  : ALuint id
**	戻り値: void
**	説明  :
******************************************************************************/
void SoundAL::DeleteSource( ALuint id )
{
}


/******************************************************************************
**	関数名: DeleteBuffer
**	関数の概要
**	引数  : ALuint id
**	戻り値: void
**	説明  :
******************************************************************************/
void SoundAL::DeleteBuffer( ALuint id )
{
}


/******************************************************************************
**	関数名: DeleteSourceAll
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void SoundAL::DeleteSourceAll()
{
	delete[] m_pSource;
	m_pSource = NULL;

}


/******************************************************************************
**	関数名: DeleteBufferAll
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void SoundAL::DeleteBufferAll()
{
	// ファイル名削除
	for( int i = 0; i < m_CreateBuffer; i++ )
	{
		delete[] m_pSoundBuffData[ i ].pFileName;
		m_pSoundBuffData[ i ].pFileName = NULL;

	}

	delete[] m_pSoundBuffData;
	m_pSoundBuffData = NULL;

}


/******************************************************************************
**	関数名: SetBuffer
**	関数の概要
**	引数  : ALuint id
**	戻り値: bool
**	説明  :
******************************************************************************/
bool SoundAL::SetBuffer( ALuint id )
{
	// 指定されたIDの範囲内チェック
	if( id < m_CreateBuffer )
	{
		for( ALuint i = 0; i < m_CreateSource; i++ )
		{
			// 未使用チェック
			if( !m_pSource[ i ].bUse )
			{
				alSourcei( m_pSource[ i ].source, AL_BUFFER, m_pSoundBuffData[ id ].buffer );
				alSourcei( m_pSource[ i ].source, AL_LOOPING, m_pSoundBuffData[ id ].bLoop );
				m_pSource[ i ].bUse = true;
				return true;

			}

		}

	}

	// セットに失敗
	return false;

}


/******************************************************************************
**	関数名: SetBuffer
**	関数の概要
**	引数  : ALuint id, ALboolean Loop
**	戻り値: bool
**	説明  :
******************************************************************************/
bool SoundAL::SetBuffer( ALuint id, ALboolean Loop )
{
	// 指定されたIDの範囲内チェック
	if( id < m_CreateBuffer )
	{
		for( ALuint i = 0; i < m_CreateSource; i++ )
		{
			// 未使用チェック
			if( !m_pSource[ i ].bUse )
			{
				alSourcei( m_pSource[ i ].source, AL_BUFFER, m_pSoundBuffData[ id ].buffer );
				alSourcei( m_pSource[ i ].source, AL_LOOPING, Loop );
				m_pSource[ i ].bUse = true;
				return true;

			}

		}

	}

	// セットに失敗
	return false;

}


/******************************************************************************
**	関数名: SetLoop
**	関数の概要
**	引数  : ALuint BufferID, int Loop
**	戻り値: void
**	説明  :
******************************************************************************/
void SoundAL::SetLoop( ALuint BufferID, int Loop )
{
	// 指定されたIDの範囲内チェック
	if( BufferID < m_CreateBuffer )
	{
		m_pSoundBuffData[ BufferID ].bLoop = Loop;
		alSourcei( m_pSource[ BufferID ].source, AL_LOOPING, Loop );

	}

}


/******************************************************************************
**	関数名: PlaySound
**	関数の概要
**	引数  : ALuint id
**	戻り値: bool
**	説明  :
******************************************************************************/
bool SoundAL::PlaySoundAL( ALuint id )
{
	// 指定されたIDの範囲内チェック
	if( id < m_CreateSource )
	{
		// 使用チェック
		if( m_pSource[ id ].bUse && !m_pSource[ id ].bPlay )
		{
			alSourcePlay( m_pSource[ id ].source );
			m_pSource[ id ].bPlay = true;
			return true;

		}

	}

	// セットに失敗
	return false;

}


/******************************************************************************
**	関数名: PlaySoundAll
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void SoundAL::PlaySoundAll()
{
	for( ALuint i = 0; i < m_CreateSource; i++ )
	{
		// 使用チェック
		if( m_pSource[ i ].bUse && !m_pSource[ i ].bPlay )
		{
			alSourcePlay( m_pSource[ i ].source );
			m_pSource[ i ].bPlay = true;

		}

	}	

}


/******************************************************************************
**	関数名: StopSound
**	関数の概要
**	引数  : ALuint id
**	戻り値: bool
**	説明  :
******************************************************************************/
bool SoundAL::StopSound( ALuint id )
{
	if( id < m_CreateSource )
	{
		// 使用チェック
		if( m_pSource[ id ].bUse && m_pSource[ id ].bPlay )
		{
			alSourceStop( m_pSource[ id ].source );
			m_pSource[ id ].bPlay = false;
			m_pSource[ id ].bUse = false;
			return true;

		}

	}

	// セットに失敗
	return false;

}


/******************************************************************************
**	関数名: StopSoundAll
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void SoundAL::StopSoundAll()
{
	for( ALuint i = 0; i < m_CreateSource; i++ )
	{
		// 使用チェック
		if( m_pSource[ i ].bUse && m_pSource[ i ].bPlay )
		{
			alSourceStop( m_pSource[ i ].source );
			m_pSource[ i ].bPlay = false;
			m_pSource[ i ].bUse = false;

		}

	}

}


/******************************************************************************
**	関数名: PauseSound
**	関数の概要
**	引数  : ALuint id
**	戻り値: bool
**	説明  :
******************************************************************************/
bool SoundAL::PauseSound( ALuint id )
{
	if( id < m_CreateSource )
	{
		// 使用チェック
		if( m_pSource[ id ].bUse && m_pSource[ id ].bPlay )
		{
			alSourcePause( m_pSource[ id ].source );
			m_pSource[ id ].bPlay = false;
			return true;

		}

	}

	// セットに失敗
	return false;

}


/******************************************************************************
**	関数名: PauseSoundAll
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void SoundAL::PauseSoundAll()
{
	for( ALuint i = 0; i < m_CreateSource; i++ )
	{
		// 使用チェック
		if( m_pSource[ i ].bUse && m_pSource[ i ].bPlay )
		{
			alSourcePause( m_pSource[ i ].source );
			m_pSource[ i ].bPlay = false;

		}

	}

}


