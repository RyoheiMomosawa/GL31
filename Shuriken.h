#pragma once

#define SHURIKEN_TEXCOORD 3
#define SHURIKEN_ROTATION_INTERVAL 2

class Shuriken : public Scene2DGL
{
public:
	Shuriken();
	~Shuriken();

	HRESULT Init();
	int Uninit();
	void Update();
	void Draw();

	static Shuriken *Create();

private:
	int m_MoveDigit;//移動の分割数
	int m_CountMove;//移動のカウンタ

	Vector3 m_TexCoord;

	int m_TexCoordCount;

	float m_Force;//移動する力
	Vector3 m_BasePos;

protected:

};

