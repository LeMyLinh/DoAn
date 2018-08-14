#ifndef _SCENEMAIN_H_
#define _SCENEMAIN_H_
#include "Game.h"
#include "Level6.h"
#include "Level5.h"
#include "SceneMenu.h"

class SceneMain: public CGame
{
public: 	
	SceneMain(int _nCmdShow);
	~SceneMain();
	Scene* scene;
protected:	
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void UpdateGame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void OnKeyDown(int KeyCode);
	void NextLevel();
};

#endif