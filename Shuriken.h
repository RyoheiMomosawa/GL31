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
	int m_MoveDigit;//�ړ��̕�����
	int m_CountMove;//�ړ��̃J�E���^

	Vector3 m_TexCoord;

	int m_TexCoordCount;

	float m_Force;//�ړ������
	Vector3 m_BasePos;

protected:

};

