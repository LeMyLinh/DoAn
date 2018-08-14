#ifndef _MAP_H_
#define _MAP_H_
#include "GSprite.h"
#include <d3d9.h>
#include <list>
using namespace std;

class Map
{
private:

	int col; // so cot cua ma tran
	int row; // so hang cua ma tran
	int** Mattrix; //Ma tran load map obj
	GSprite* BackGround; //Sprite chua hinh nen

public:
	Map();
	void Init(LPCWSTR fileTileMap, char* fileMattrix, int col, int row);
	void LoadMattrixFromFile(char * FileName);
	void DrawMap();

	~Map();
};

#endif // !_MAP_H_



