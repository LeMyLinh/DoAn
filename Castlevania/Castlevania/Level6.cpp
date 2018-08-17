#include "Level6.h"
#include "Global.h"

Level6::Level6()
{
	Scene_Index = 2;
	LV5_STAGE1 = RECT{ 0,96,5632,96 + 352 };
	LV5_STAGE2 = RECT{ 3074,544,3074 + 1024, 544 + 352 };
	LV5_STAGE3 = RECT{ 0,544,1504, 544 + 352 };
	//LV5_STAGE3 = RECT{ 1056, 669, 1056 + 1536, 669 + 192 };
	LoadResources();
	Islockcamera = false;
}

void Level6::RenderFrame(int Delta)
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

void Level6::ProcessInput_UP(int Delta)
{
}

void Level6::ProcessInput_DOWN(int Delta)
{
}

void Level6::ProcessInput_RIGHT(int Delta)
{
}

void Level6::ProcessInput_LEFT(int Delta)
{
}

void Level6::ProcessInput(int Delta)
{
}

void Level6::UpdateGame(int Delta)
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

void Level6::LoadResources()
{
	Scene_Index = 1;
	map = new Map();
	simon = new Simon(LV5_STAGE3.left * 2 + 400, LV5_STAGE3.bottom * 2 - 200, 3);
	objManager = new ObjManager();
	blackBoard = new BlackBoard();

	KeyBoard::GetKey()->InitKeyboard();
	camera = new GCamera(G_ScreenWidth, G_ScreenHeight, 0, D3DXVECTOR3(1.0f, 1.0f, 1.0f), LV5_STAGE3.left * 2 + 400, LV5_STAGE3.bottom * 2 - 200, 3);
	map->Init(L"Map/level1_tile.png", "Map/level1_map.txt", 14, 8);
	//map->Init(L"Map/level5_tile.png", "Map/level1_map.txt", 8, 6);

	GTexture* t = new GTexture();
	t->loadTextTureFromFile(L"Map/level1_tile.png", D3DCOLOR_XRGB(255, 0, 255));
	simon->LoadResource(L"Resources/simon.png", 8, 3, 0);
	Font::GetFont()->Innit();
	objManager->Init("Map/Level1_Object.txt");

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

void Level6::OnKeyDown(int KeyCode)
{
}



Level6::~Level6()
{
}
