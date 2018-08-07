#ifndef _QUADTREE_H_
#define _QUADTREE_H_
#include <fstream>
#include <iostream>
#include "QuadNode.h"
#include <d3d9.h>
using namespace std;
class QuadTree
{
	
public:
	QuadNode* Root;
	QuadTree();
	void GetQuadTreeFromFile(char* FileName);
	void BuidQuadTree(QuadNode* Root, QuadNode* line);
	int GetIdChild(int idRoot, int idChild);
	void GetlistObj(QuadNode *root, RECT rectCamera, list<int> &result);
	~QuadTree();
};
#endif // !_QUADTREE_H_



