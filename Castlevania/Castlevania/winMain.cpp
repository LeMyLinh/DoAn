#include <Windows.h>
#include "Game.h"
#include "SceneMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CGame* game= new SceneMain(nShowCmd);

	game->GameInit();
	game->GameRun();
	game->GameEnd();
	return 0;
}