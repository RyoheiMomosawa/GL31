#pragma once
#include "Scene2DGL.h"
class SceneTestPlayer : public Scene2DGL
{
public:
	SceneTestPlayer( int Priority = PRIORITY_2D );
	virtual ~SceneTestPlayer();

	HRESULT Init(); // ������
	int Uninit(); // �I��
	void Update(); // �X�V
	void Draw(); // �`��
	static SceneTestPlayer *Create();

	// Set,Get


	// Delete


protected:
	// �����o�ϐ�


private:

};

