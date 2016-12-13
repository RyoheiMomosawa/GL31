//=====================================================================================================================
//	ファイル名:	UtlCommonLib.cpp
//	作成者:		高橋弘宜
//=====================================================================================================================
//	更新履歴
//		-ver 1.00	2016 / 06 / 27	高橋弘宜
//=====================================================================================================================
//	ファイルの説明
//				マクロ・関数群	(依存なし)
//=====================================================================================================================

//=====================================================================================================================
//　※　インクルード　※
//=====================================================================================================================

#include "UtlCommonLib.h"

#include <stdio.h>
#include <stdarg.h>
#include <tchar.h>
#include <assert.h>

namespace t_lib
{
	//=============================================================================
	// 関数名：		printf_here
	// 説明：		呼び出し位置にprintf形式で文字を出す
	//=============================================================================
	const char* printf_here(const char* fmt, ...)
	{
		static char szBuff[2048];
		va_list args;

		va_start(args, fmt);

#if _DEBUG
		assert(_vsctprintf(fmt, args) < 2048);
#endif

		_vstprintf_s(szBuff, fmt, args);
		return szBuff;
	}
}

