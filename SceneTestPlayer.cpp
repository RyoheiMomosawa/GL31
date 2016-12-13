#include "SceneTestPlayer.h"
#include "Client.h"
#include "Manager.h"



SceneTestPlayer::SceneTestPlayer( int Priority ) : Scene2DGL( Priority )
{
}


SceneTestPlayer::~SceneTestPlayer()
{
}

HRESULT SceneTestPlayer::Init()
{
	return Scene2DGL::Init();

}

int SceneTestPlayer::Uninit()
{
	return Scene2DGL::Uninit();

}

void SceneTestPlayer::Update()
{
	if( Manager::GetKeyboard()->GetPress( DIK_W ) )
	{
		m_Obj3d.pos.y -= 2.0f;

	}
	else if( Manager::GetKeyboard()->GetPress( DIK_S ) )
	{
		m_Obj3d.pos.y += 2.0f;

	}
	else if( Manager::GetKeyboard()->GetPress( DIK_A ) )
	{
		m_Obj3d.pos.x -= 2.0f;

	}
	else if( Manager::GetKeyboard()->GetPress( DIK_D ) )
	{
		m_Obj3d.pos.x += 2.0f;

	}

	Manager::GetClient()->SetSendData( (char *)&m_Obj3d.pos, sizeof Vector3 );

}

void SceneTestPlayer::Draw()
{
	Scene2DGL::Draw();

}

SceneTestPlayer *SceneTestPlayer::Create()
{
	SceneTestPlayer *p;
	p = new SceneTestPlayer;

	if FAILED( p->Init() )
	{
		delete p;
		return NULL;

	}
	else
	{
		return p;

	}

}
