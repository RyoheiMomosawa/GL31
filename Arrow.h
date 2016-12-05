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
	int m_MoveDigit;//�ړ��̕�����
	int m_CountMove;//�ړ��̃J�E���^

	float m_Force;//�ړ������
	Vector3 m_BasePos;

protected:

};

