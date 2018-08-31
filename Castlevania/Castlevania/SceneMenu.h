#ifndef _SCENEMENU_H_
#define _SCENEMENU_H_

#include "Scene.h"
#include "CText.h"
#include "GTexture.h"
#include "Global.h"

class SceneMenu : public Scene
{
protected:
	CText * Text;
	RECT Region_Text;
	GTexture* BackGround;
public:
	SceneMenu();
	~SceneMenu();

	virtual void RenderFrame(int Delta);
	virtual void LoadResources();
	virtual void OnKeyDown(int KeyCode);
};
#endif