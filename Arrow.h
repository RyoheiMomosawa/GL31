#pragma once
class Arrow : public Scene2DGL
{
public:
	Arrow();
	~Arrow();

	HRESULT Init();
	int Uninit();
	void Update();
	void Draw();

	static Arrow *Create();

private:
	int m_MoveDigit;//ˆÚ“®‚Ì•ªŠ„”
	int m_CountMove;//ˆÚ“®‚ÌƒJƒEƒ“ƒ^

	float m_Force;//ˆÚ“®‚·‚é—Í
	Vector3 m_BasePos;

protected:

};

