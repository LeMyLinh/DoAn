#ifndef _SCENE_H_
#define _SCENE_H_

class Scene
{
public:
	int Scene_Index;
	bool IsEnd,Is_NextScene;
	int Localtime;
	Scene()
	{
		IsEnd=false;
		Is_NextScene=false;
		Localtime=0;
	};
	~Scene(){};

	virtual void RenderFrame(int Delta){};
	virtual void UpdateGame(int Delta) {};
	virtual void ProcessInput_UP(int Delta){};
	virtual void ProcessInput_DOWN(int Delta){};
	virtual void ProcessInput_RIGHT(int Delta){};
	virtual void ProcessInput_LEFT(int Delta){};
	virtual void ProcessInput(int Delta){};
	virtual void LoadResources(){};
	virtual void OnKeyDown(int KeyCode){};
	void Effect(int Delta)
	{
		if (!Is_NextScene) return;
		Localtime+=Delta;
		if (Localtime>=500) IsEnd=true;
	}
};

#endif