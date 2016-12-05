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
	int m_MoveDigit;//ˆÚ“®‚Ì•ªŠ„”
	int m_CountMove;//ˆÚ“®‚ÌƒJƒEƒ“ƒ^

	Vector3 m_TexCoord;

	int m_TexCoordCount;

	float m_Force;//ˆÚ“®‚·‚é—Í
	Vector3 m_BasePos;

protected:

};

