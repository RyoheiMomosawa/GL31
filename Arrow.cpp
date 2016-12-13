#include "main.h"
#include "Manager.h"
#include "Scene2DGL.h"
#include "Input.h"
#include "Arrow.h"

static int g_cnt = 0;

Arrow::Arrow()
{
}


Arrow::~Arrow()
{
}

Arrow *Arrow::Create()
{
	Arrow *arrow;

	arrow = new Arrow;

	if (arrow != nullptr)
	{
		arrow->Init();
	}

	return arrow;
}

HRESULT Arrow::Init()
{

	SetParam(&Vector3(0, 0, 0), SCENEPARAM_ROT);
	POINT p;
	GetCursorPos(&p);

	Vector3 ms = Vector3(p.x,p.y,0);

	SetParam(&Vector3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), SCENEPARAM_POS);

	m_MoveDigit = 32;

	m_Force = 5;
	float rad[4] = {0,90,180,270};
	Vector3 vec[4];

	for (int i = 0; i < 4; i++)
	{
		vec[i] = Vector3(0,0,rad[i]/360.0f);
	}
	int work = g_cnt % 4;

	//m_Obj3d.rot = Vector3(0, 0, rad[work]+90.0f);

	m_Obj3d.accPos = Vector3(cosf(vec[work].z*3.1415f * 2)*m_Force,sinf(vec[work].z*3.1415f * 2)*m_Force,0);

	g_cnt++;

	return S_OK;
}

int Arrow::Uninit()
{
	return 0;
}

void Arrow::Update()
{
	m_CountMove++;

	if (m_CountMove >= m_MoveDigit)
	{
		//Release();

		return;
	}
	float vec = m_Obj3d.rot.z / 360.0f;

	m_Obj3d.accPos = Vector3(cosf(vec*3.1415f * 2)*m_Force, sinf(vec*3.1415f * 2)*m_Force, 0);

	m_Obj3d.pos -= m_Obj3d.accPos;
}

void Arrow::Draw()
{
	// エラー回避
	if (m_Texture == EOF)
	{
		return;

	}

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0.0, 0.0, 1.0);

	// モデルビュー
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();


	/* 四角形描画 */
	// テクスチャ
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// アルファブレンド設定
	glEnable(GL_BLEND);
	//glBlendFunc( GL_SRC_ALPHA, GL_DST_ALPHA );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	// ライトの無効化
	glDisable(GL_LIGHTING);

	glTranslatef(m_Obj3d.pos.x, m_Obj3d.pos.y, 0);
	glRotatef(m_Obj3d.rot.z+m_Obj3d.rotMove.z-90.0f, 0, 0, 1);
	//glTranslatef(0, 0, 0);
	glScalef(1, 1, 1);

	// 描画開始
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(m_Obj3d.col.r, m_Obj3d.col.g, m_Obj3d.col.b, m_Obj3d.col.a);
	glTexCoord2f(0, 0.0f);
	glVertex2d(- m_Obj3d.width,m_Obj3d.height);

	glTexCoord2f(1, 0.0f);
	glVertex2d(m_Obj3d.width,m_Obj3d.height);

	glTexCoord2f(0, 1.0f);
	glVertex2d(- m_Obj3d.width, - m_Obj3d.height);

	glTexCoord2f(1, 1.0f);
	glVertex2d(m_Obj3d.width,- m_Obj3d.height);

	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	/* マトリックスを元に戻す */
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}