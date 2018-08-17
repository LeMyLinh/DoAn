#include "Level5.h"

Level5::Level5()
{
	LoadResources();
}
Level5::~Level5()
{
}
void Level5::LoadResources()
{
	Scene_Index = 1;
	map = new Map();
	simon = new Simon(LV5_STAGE4.left * 2 + 200, LV5_STAGE4.bottom * 2 - 150, 4);
	objManager = new ObjManager();
	blackBoard = new BlackBoard();

	KeyBoard::GetKey()->InitKeyboard();
	camera = new GCamera(G_ScreenWidth, G_ScreenHeight, 0, D3DXVECTOR3(1.0f, 1.0f, 1.0f), LV5_STAGE4.left * 2 + 200, LV5_STAGE4.bottom * 2 - 150, 4);
	map->Init(L"Map/level5_tile.png", "Map/Level5_map.txt", 8, 6);
	GTexture* t = new GTexture();
	t->loadTextTureFromFile(L"Map/level5_tile.png", D3DCOLOR_XRGB(255, 0, 255));
	simon->LoadResource(L"Resources/simon.png", 8, 3, 0);
	Font::GetFont()->Innit();
	objManager->Init("Map/Level5_Object.txt");
	Tile::GetStaticObj()->Init();
	SmallCandle::GetStaticObj()->Init();
	Stair::GetStaticObj()->Init();
	TopStair::GetStaticObj()->Init();
	Effect::GetStaticObj()->Init();
	EnemyRender::GetStaticObj()->Init();
	Item::GetStaticObj()->Init();
	CGate::GetStaticObj()->Init();
	Weapon::GetStaticObj()->Init();
}
void Level5::RenderFrame(int Delta)
{
	if (G_lpDirect3DDevice->BeginScene())
	{
		G_lpDirect3DDevice->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));



		G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		camera->SetTransForm();
		map->DrawMap();

		objManager->Draw();
		Effect::GetStaticObj()->Draw();
		Weapon::GetStaticObj()->Draw();
		simon->Draw(Delta);
		Item::GetStaticObj()->Draw(Delta);

		char str[100];
		blackBoard->RenderFrame(Delta, camera->GetRectCamera().left, camera->GetRectCamera().top, simon->GetHP());
		G_SpriteHandler->End();

		G_lpDirect3DDevice->EndScene();
	}
	G_lpDirect3DDevice->Present(NULL, NULL, NULL, NULL);

}
void Level5::UpdateGame(int Delta)
{
	KeyBoard::GetKey()->ProcessKeyBoard();
	camera->Update(simon->GetX(), simon->GetY(), simon->GetLayerMap(), simon->IsNextStage, simon->IsAutoRun, Delta);

	objManager->UpDate(camera->GetRectCamera(), Item::GetStaticObj()->GetListItem(), Delta, simon->GetBox());
	simon->Update(objManager->GetListObj(), objManager->GetListInfo(), blackBoard, objManager->GetlistEnemy(), Delta, camera, objManager);
	Item::GetStaticObj()->Update(Delta);
	Weapon::GetStaticObj()->Update(camera->GetRectCamera(), blackBoard, simon->GetBox(), Delta);
	if (NextLevel)
	{
		NextLevel = false;
		IsEnd = true;
	}

}
void Level5::ProcessInput(int Delta)
{
}

void Level5::ProcessInput_UP(int Delta)
{

}
void Level5::ProcessInput_DOWN(int Delta)
{

}
void Level5::ProcessInput_RIGHT(int Delta)
{

}
void Level5::ProcessInput_LEFT(int Delta)
{

}

void Level5::OnKeyDown(int KeyCode)
{
}