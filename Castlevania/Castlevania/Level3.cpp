#include "Level3.h"
#include "Global.h"



Level3::Level3()
{
	Scene_Index = 2;
	lv2_Layer1 = RECT{ 1024,48,3584,223 };
	lv2_Layer2 = RECT{ 0,240,1536,416 };
	lv2_Layer3 = RECT{ 0,432,768,607 };
	LoadResources();
	Islockcamera = false;
}

void Level3::RenderFrame(int Delta)
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
		G_bossHP = 16;
		char str[100];
		blackBoard->RenderFrame(Delta, camera->GetRectCamera().left, camera->GetRectCamera().top, simon->GetHP());
		G_SpriteHandler->End();

		G_lpDirect3DDevice->EndScene();
	}
	G_lpDirect3DDevice->Present(NULL, NULL, NULL, NULL);
}

void Level3::ProcessInput_UP(int Delta)
{
}

void Level3::ProcessInput_DOWN(int Delta)
{
}

void Level3::ProcessInput_RIGHT(int Delta)
{
}

void Level3::ProcessInput_LEFT(int Delta)
{
}

void Level3::ProcessInput(int Delta)
{
}

void Level3::UpdateGame(int Delta)
{
	KeyBoard::GetKey()->ProcessKeyBoard();
	camera->Update(simon->GetX(), G_ScreenHeight / 2, simon->GetLayerMap(), simon->IsNextStage, simon->IsAutoRun, Delta);
	map->SelectScene(camera->GetRectCamera());

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

void Level3::LoadResources()
{
	//
	Scene_Index = 1;
	map = new Map();
	simon = new Simon(lv2_Layer3.right*2 - 200 /*6400*/, lv2_Layer3.bottom * 2 - 300 /*90*/,3);
	objManager = new ObjManager();
	blackBoard = new BlackBoard();


	//
	KeyBoard::GetKey()->InitKeyboard();
	GTexture* texture = new GTexture();
	texture->loadTextTureFromFile(L"caveman.bmp", D3DCOLOR_XRGB(255, 0, 255));
	camera = new GCamera(G_ScreenWidth, G_ScreenHeight, 0, D3DXVECTOR3(1.0f, 1.0f, 1.0f), lv2_Layer3.right * 2 - 200, lv2_Layer3.bottom * 2 - 200, 3);
	//
	GTexture* t = new GTexture();
	t->loadTextTureFromFile(L"Data/lv2.png", D3DCOLOR_XRGB(255, 0, 255));
	simon->LoadResource(L"Resources/simon.png", 8, 3, 0);
	Font::GetFont()->Innit();
	objManager->Init("Data/lv2-GameObj.txt", "Data/lv2-GameObj-Quadtree.txt");
	map->Init(L"Data/lv2.png", "Data/lv2-MAP.txt", "Data/lv2-MAP-quadtree.txt",10,6);

	Tile::GetStaticObj()->Init();
	BigCandel::GetStaticObj()->Init();
	SmallCandle::GetStaticObj()->Init();
	Stair::GetStaticObj()->Init();
	TopStair::GetStaticObj()->Init();
	Effect::GetStaticObj()->Init();
	EnemyRender::GetStaticObj()->Init();
	Item::GetStaticObj()->Init();
	CGate::GetStaticObj()->Init();
	Weapon::GetStaticObj()->Init();
}

void Level3::OnKeyDown(int KeyCode)
{
}



Level3::~Level3()
{
}
