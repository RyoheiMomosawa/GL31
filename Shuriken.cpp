#include "main.h"
#include "Manager.h"
#include "Scene2DGL.h"
#include "Input.h"
#include "Shuriken.h"

static int g_cnt2 = 0;
Shuriken::Shuriken()
{
}


Shuriken::~Shuriken()
{
}

Shuriken *Shuriken::Create()
{
	Shuriken *shuriken;

	shuriken = new Shuriken;

	if (shuriken != nullptr)
	{
		shuriken->Init();
	}

	return shuriken;
}

HRESULT Shuriken::Init()
{
	SetParam(&Vector3(0, 0, 0), SCENEPARAM_ROT);
	POINT p;
	GetCursorPos(&p);

	Vector3 ms = Vector3(p.x, p.y, 0);

	SetParam(&Vector3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), SCENEPARAM_POS);

	m_MoveDigit = 32;

	m_Force = 5;
	float rad[4] = { 0,90,180,270 };
	Vector3 vec[4];

	for (int i = 0; i < 4; i++)
	{
		vec[i] = Vector3(0, 0, rad[i] / 360.0f);
	}
	int work = g_cnt2 % 4;

	m_Obj3d.rot = Vector3(0, 0, rad[work] + 90.0f);

	m_Obj3d.accPos = Vector3(cosf(vec[work].z*3.1415f * 2)*m_Force, sinf(vec[work].z*3.1415f * 2)*m_Force, 0);

	g_cnt2++;

	//POINT p;
	//GetCursorPos(&p);

	//SetParam(&Vector3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), SCENEPARAM_POS);

	//m_MoveDigit = 32;
	//Vector3 SubMousePosToInitPos = Vector3(m_Obj3d.pos.x - p.x, m_Obj3d.pos.y - p.y,0);

	////float theta = atanf(SubMousePosToInitPos.y/ SubMousePosToInitPos.x);

	////float rad = theta * 180.0f / 3.1415f;

	////if (rad <= 0)
	////{
	////	rad += 360.0f;
	////}

	//Vector3	MovePosFrame = Vector3(SubMousePosToInitPos.x/ (float)m_MoveDigit, SubMousePosToInitPos.y/ (float)m_MoveDigit,0);
	//m_CountMove = 0;

	//m_Obj3d.accPos = MovePosFrame;

	m_TexCoord = Vector3(0,0,0);

	return S_OK;
}

int Shuriken::Uninit()
{
	return 0;
}

void Shuriken::Update()
{
	m_CountMove++;

	if (m_CountMove >= m_MoveDigit)
	{
		//Release();

		return;
	}

	if (m_CountMove % SHURIKEN_ROTATION_INTERVAL == 0)
	{
		m_TexCoord += Vector3(1.0f/ (float)SHURIKEN_TEXCOORD,0,0);
	}

	if (m_TexCoord.x >= 0.99f)
	{
		m_TexCoord.x = 0;
	}

	m_Obj3d.pos -= m_Obj3d.accPos;
}

void Shuriken::Draw()
{
	// �G���[���
	if (m_Texture == EOF)
	{
		return;
	}

	/* �}�g���b�N�X���� */
	// �v���W�F�N�V����
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0.0, 0.0, 1.0);

	// ���f���r���[
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();


	/* �l�p�`�`�� */
	// �e�N�X�`��
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// �A���t�@�u�����h�ݒ�
	glEnable(GL_BLEND);
	//glBlendFunc( GL_SRC_ALPHA, GL_DST_ALPHA );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	// ���C�g�̖�����
	glDisable(GL_LIGHTING);

	glTranslatef(m_Obj3d.pos.x, m_Obj3d.pos.y, 0);
	glRotatef(m_Obj3d.rot.z + m_Obj3d.rotMove.z, 0, 0, 1);
	//glTranslatef(0, 0, 0);
	glScalef(1, 1, 1);

	// �`��J�n
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(m_Obj3d.col.r, m_Obj3d.col.g, m_Obj3d.col.b, m_Obj3d.col.a);
	glTexCoord2f(m_TexCoord.x, 0.0f);
	glVertex2d(-m_Obj3d.width, m_Obj3d.height);

	glTexCoord2f(m_TexCoord.x+1.0f/(float)SHURIKEN_TEXCOORD, 0.0f);
	glVertex2d(m_Obj3d.width, m_Obj3d.height);

	glTexCoord2f(m_TexCoord.x, 1.0f);
	glVertex2d(-m_Obj3d.width, -m_Obj3d.height);

	glTexCoord2f(m_TexCoord.x+1.0f/(float)SHURIKEN_TEXCOORD, 1.0f);
	glVertex2d(m_Obj3d.width, -m_Obj3d.height);

	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	/* �}�g���b�N�X�����ɖ߂� */
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
