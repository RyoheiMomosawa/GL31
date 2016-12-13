#pragma once
#include "Scene2DGL.h"
class SceneTestPlayer : public Scene2DGL
{
public:
	SceneTestPlayer( int Priority = PRIORITY_2D );
	virtual ~SceneTestPlayer();

	HRESULT Init(); // 初期化
	int Uninit(); // 終了
	void Update(); // 更新
	void Draw(); // 描画
	static SceneTestPlayer *Create();

	// Set,Get


	// Delete


protected:
	// メンバ変数


private:

};

