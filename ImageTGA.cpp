/******************************************************************************
**	タイトル  :
**	ファイル名: .cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016//
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include "ImageTGA.h"
#include "RendererGL.h"
#include <Windows.h>
#include <stdio.h>


/******************************************************************************
**	静的メンバ変数
******************************************************************************/


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
ImageTGA::ImageTGA()
{
	ZeroMemory( &TGATexImg, sizeof TEXTUREIMAGE );

}


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
ImageTGA::~ImageTGA()
{
}


/******************************************************************************
**	関数名: Read
**	関数の概要
**	引数  : ファイルパス const char *FileName
**	戻り値: 読込成功時 true、失敗時 false
**	説明  :
******************************************************************************/
inline bool ImageTGA::Read( const char *FileName )
{
	/* 変数宣言 */
	FILE *fp; // ファイルポインタ
	unsigned int bytePerPixel; // 1ピクセルあたりの大きさ
	unsigned char header[ 18 ]; // ヘッダ情報
	unsigned int temp; // コピー用作業枠


	// ファイルオープン
	// エラーの返却、ファイルポインタがNULLだった場合はfalseを返す
	if( fopen_s( &fp, FileName, "rb" ) != 0 || fp == NULL )
	{
		return false;

	}


	// ヘッダの読み込み
	fread_s( header, sizeof( unsigned char ) * 18, 1, sizeof( header ), fp );


	// 大きさの設定
	TGATexImg.width = header[ 13 ] * 256 + header[ 12 ];
	TGATexImg.height = header[ 15 ] * 256 + header[ 14 ];


	// 1ピクセルの大きさ
	TGATexImg.bpp = header[ 16 ];


	// ピクセルサイズ指定
	switch( TGATexImg.bpp )
	{
		case 24:
			TGATexImg.format = TGATexImg.InternalFormat = GL_RGB;

			break;

		case 32:
			TGATexImg.format = TGATexImg.InternalFormat = GL_RGBA;

			break;

		default:

			return false;

	}


	// 1ピクセルあたりのバイト数
	bytePerPixel = TGATexImg.bpp / 8;


	// 画像のデータサイズ
	TGATexImg.ImageSize = TGATexImg.width * TGATexImg.height*bytePerPixel;


	// データサイズをメモリ確保
	TGATexImg.ImageData = new unsigned char[ TGATexImg.ImageSize ];


	// テクセルデータの読み込み
	fread_s( TGATexImg.ImageData, TGATexImg.ImageSize, 1, TGATexImg.ImageSize, fp );


	// テクセルデータをコンバート
	for( unsigned int i = 0; i < TGATexImg.ImageSize; i += bytePerPixel )
	{
		temp = TGATexImg.ImageData[ i ];
		TGATexImg.ImageData[ i ] = TGATexImg.ImageData[ i + 2 ];
		TGATexImg.ImageData[ i + 2 ] = temp;

	}


	// ファイルクローズ
	fclose( fp );


	// 成功時、trueを返す
	return true;

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値:
**	説明  :
******************************************************************************/
unsigned int ImageTGA::CreateTexture( const char *FileName )
{
	/* 変数宣言 */
	unsigned int texture; // テクスチャID
	unsigned char *image = NULL; // 画像データ


	// ファイル読み込み
	Read( FileName );


	//テクスチャ生成
	glGenTextures( 1, &texture );


	// テクスチャのバインド
	glBindTexture( GL_TEXTURE_2D, texture );


	// 1ピクセルのサイズを指定
	switch( TGATexImg.format )
	{
		case GL_RGB: // 24bitは「4」を指定
			glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );

			break;

		case GL_RGBA: // 32bitは「1」を指定
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

			break;

		default:

			break;
	
	}


	// テクスチャの拡縮方法の指定
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );


	// テクスチャの割り当て
	glTexImage2D( GL_TEXTURE_2D, 0, TGATexImg.InternalFormat, TGATexImg.width, TGATexImg.height, 0, TGATexImg.format, GL_UNSIGNED_BYTE, TGATexImg.ImageData );
	//gluBuild2DMipmaps( GL_TEXTURE_2D, TGATexImg.InternalFormat, TGATexImg.width, TGATexImg.height, TGATexImg.format, GL_UNSIGNED_BYTE, TGATexImg.ImageData );


	glBindTexture( GL_TEXTURE_2D, 0 );


	// メモリの解放
	if( TGATexImg.ImageData != NULL )
	{
		delete[] TGATexImg.ImageData;
		TGATexImg.ImageData = NULL;

	}

	
	return texture;

}
