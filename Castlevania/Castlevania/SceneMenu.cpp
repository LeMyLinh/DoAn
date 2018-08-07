
#include "SceneMenu.h"


#define BACKGROUND_FILE L"Resources/mainmenu.png"

SceneMenu::SceneMenu()
{
	Scene_Index=0;
	LoadResources();
}
SceneMenu::~SceneMenu()
{
	if (BackGround != NULL) delete BackGround;
	if (Text != NULL) delete Text;
}
void SceneMenu::LoadResources()
{
	Text=new CText("PUSH START KEY",24,G_ScreenWidth/2 - 70,300,D3DCOLOR_ARGB(255, 255, 255, 255));
	BackGround=new GTexture();
	BackGround->loadTextTureFromFile(BACKGROUND_FILE);
}
void SceneMenu::RenderFrame(int Delta)
{
	if (G_lpDirect3DDevice->BeginScene())
	{
		G_lpDirect3DDevice->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
		G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		BackGround->SetFormat(D3DXVECTOR2((float)G_ScreenWidth / BackGround->Width, 1), 0, 1);
		BackGround->RenderTexture(G_ScreenWidth / 2, BackGround->Height / 2);
		G_SpriteHandler->End();
		if (Is_NextScene) Text->renderAnimation(Delta);
		else  Text->Draw();
		Effect(Delta);
		G_lpDirect3DDevice->EndScene();
	}
	G_lpDirect3DDevice->Present(NULL, NULL, NULL, NULL);
}
void SceneMenu::OnKeyDown(int KeyCode)
{
	if (KeyCode==DIK_RETURN) Is_NextScene=true;
}