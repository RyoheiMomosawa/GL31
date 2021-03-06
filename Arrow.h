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
	int m_MoveDigit;//移動の分割数
	int m_CountMove;//移動のカウンタ

	float m_Force;//移動する力
	Vector3 m_BasePos;

protected:

};

