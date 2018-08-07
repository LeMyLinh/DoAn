#include "SceneMain.h"
SceneMain::SceneMain(int _nCmdShow): CGame(_nCmdShow)
{
}
void SceneMain::NextLevel()
{
	if (scene->IsEnd)
	{
		if (scene->Scene_Index==0) 
		{ 
			scene=new Level2(); return; 
		}
		if (scene->Scene_Index == 1)
		{
			scene = new Level3(); return;
		}
		//if()
	}

}
void SceneMain::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	scene=new SceneMenu();
	//scene = new Level2();
	//scene = new Level3();
}

void SceneMain::UpdateGame(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	scene->UpdateGame(Delta);
}

void SceneMain::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	scene->RenderFrame(Delta);
	NextLevel();
}
void SceneMain::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	if (IsKeyDown(DIK_UP))
	{
		scene->ProcessInput_UP(Delta);
		return;
	}
	if (IsKeyDown(DIK_DOWN))
	{
		scene->ProcessInput_DOWN(Delta);
		return;
	}
	if (IsKeyDown(DIK_RIGHT))
	{
		scene->ProcessInput_RIGHT(Delta);
		return;
	}

	if (IsKeyDown(DIK_LEFT))
	{
		scene->ProcessInput_LEFT(Delta);
		return;
	}
	scene->ProcessInput(Delta);
}

void SceneMain::OnKeyDown(int KeyCode)
{
	scene->OnKeyDown(KeyCode);
}
SceneMain::~SceneMain(void)
{
}