#include "Map.h"
#include <fstream>
#include <iostream>
#include <string>
#include "GTexture.h"
#include "GSprite.h"
#include <list>
#pragma warning(disable:4996)
using namespace std;


Map::Map()
{
	quadTree = new QuadTree();
}

void Map::Init(LPCWSTR fileTileMap, char * fileMattrix, char * fileQuadTree, int col,int row)
{
	GTexture* texture = new GTexture();
	texture->loadTextTureFromFile(fileTileMap);
	BackGround = new GSprite(texture, col, row, 0);	
	LoadMattrixFromFile(fileMattrix);
	quadTree->GetQuadTreeFromFile(fileQuadTree);
}

bool IsNumber(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

void Map::LoadMattrixFromFile(char * FileName)
{
	fstream f;
	f.open(FileName, ios::in);
	string line;
	string strTemp = "";
	getline(f, line);
	//get collumn and row

	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] != '\t' && IsNumber(line[i]))
			strTemp += line[i];
		else
		{	
			if(IsNumber(strTemp[0]))
			{
				row = atoi(strTemp.c_str());
				strTemp = "";
			}			
		}			
		if (i == line.length() - 1)
			col = atoi(strTemp.c_str());
	}
	//get size tile
	getline(f, line);
	//get mattrix
	Mattrix = new int*[row];
	for (int i = 0; i < row; i++)
	{
		Mattrix[i] = new int[col];
	}
	int i = 0;
	int j = 0;
	while (!f.eof())
	{
		strTemp = "";
		j = 0;
		getline(f, line);
		if (line == "")
			break;
		for (int n = 0; n < line.length(); n++)
		{
			if (line[n] != '\t' )
				strTemp += line[n];
			else
			{
				Mattrix[i][j] = atoi(strTemp.c_str());
				j++;
				strTemp = "";
			}
		}
		i++;
	}

	
}

void Map::SelectScene(RECT rectCamera)
{
	rectCamera.top /= 2;
	rectCamera.left /= 2;
	rectCamera.bottom /= 2;
	rectCamera.right /= 2;
	listObj.clear();
	quadTree->GetlistObj(quadTree->Root, rectCamera, listObj);	
}

int Map::GetIndexFromTile(int idTile)
{
	int i, j;
	i = (int)idTile / col;
	j = idTile%col;
	int result= Mattrix[i][j];
	return result;
}

void Map::DrawMap()
{
	std::list<int>::iterator it;
	//zoom x2
	BackGround->SetFormat(D3DXVECTOR2(2, 2), 0, 1);
	//duyet list obj
	for (it = listObj.begin(); it != listObj.end(); it++)
	{
		//detection position
		
		BackGround->Draw(((int)(*it % col) + 1)* 64 - 32 ,((*it / col) + 1) * 64 -32, GetIndexFromTile(*it));
	}
}



Map::~Map()
{
	
}
