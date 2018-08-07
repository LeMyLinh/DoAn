#include "QuadTree.h"
#include "QuadNode.h"
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include "Collision.h"
using namespace std;


QuadTree::QuadTree()
{
	this->Root = new QuadNode();
}

bool _IsNumber(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

void QuadTree::GetQuadTreeFromFile(char * FileName)
{
	fstream f;
	f.open(FileName, ios::in);
	int row = 0;
	QuadNode* node = new QuadNode();
	string line;
	string strTemp;
	Root->SetNode(1);
	//Read file
	while (!f.eof())
	{
		getline(f, line);	
		if (line == "")
			break;
		strTemp = "";
		//int iTemp;
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] != '\t' && _IsNumber(line[i]))
			{
				strTemp += line[i];
			}			
			else
			{
				if (_IsNumber(strTemp[0]))
				{
					node->listObj.push_back(atoi(strTemp.c_str()));
					strTemp = "";
				}				
			}
			if (i == line.length() - 1)
			{
				node->listObj.push_back(atoi(strTemp.c_str()));				
			}						
		}
		node->id = node->listObj.front();
		node->listObj.pop_front();
		node->bounds.left = node->listObj.front();
		node->listObj.pop_front();
		node->bounds.top = node->listObj.front();
		node->listObj.pop_front();
		node->bounds.right = node->listObj.front() + node->bounds.left;
		node->listObj.pop_front();
		node->bounds.bottom = node->listObj.front() + node->bounds.top;
		node->listObj.pop_front();
		BuidQuadTree(this->Root, node);
		node = new QuadNode();
	}
	
}

//Ham buid Quadtree
void QuadTree::BuidQuadTree(QuadNode* Root, QuadNode* line)
{
	if (line->id == Root->id)
	{
		Root->id = line->id;
		Root->bounds = line->bounds;
		Root->listObj = line->listObj;
		return;
	}
	else
	{
		switch (GetIdChild(Root->id, line->id) % (Root->id * 8))
		{
		case 1:			
			if (Root->_nodeTL == NULL)
			{
				Root->_nodeTL = new QuadNode();
				Root->_nodeTL->SetNode(GetIdChild(Root->id, line->id));
			}				
			BuidQuadTree(Root->_nodeTL, line);
			break;
		case 2:
			if (Root->_nodeTR == NULL)
			{
				Root->_nodeTR = new QuadNode();
				Root->_nodeTR->SetNode(GetIdChild(Root->id, line->id));
			}				
			BuidQuadTree(Root->_nodeTR, line);;
			break;
		case 3:
			if (Root->_nodeBL==NULL)
			{
				Root->_nodeBL = new QuadNode();
				Root->_nodeBL->SetNode(GetIdChild(Root->id, line->id));
			}				
			BuidQuadTree(Root->_nodeBL, line);
			break;
		case 4:
			if (Root->_nodeBR == NULL)
			{
				Root->_nodeBR = new QuadNode();
				Root->_nodeBR->SetNode(GetIdChild(Root->id, line->id));
			}				
			BuidQuadTree(Root->_nodeBR, line);
			break;
		default:
			break;
		}
	}
}


//GetLevel
int QuadTree::GetIdChild(int idRoot,int idChild)
{
	int result = idChild;
	while (((int)result / 8) != idRoot)
	{
		result = ((int)(result) / 8);
	}
	return result;
}

//get obj
void QuadTree::GetlistObj(QuadNode* root,RECT rectCamera, list<int> &result)
{
	std::list<int>::iterator it;
	if (!Collision::CheckCollison(root->bounds, rectCamera))
	{
		return;
	}
	else
	{
		if (root->_nodeBL != NULL)
		{
			GetlistObj(root->_nodeBL, rectCamera, result);
			GetlistObj(root->_nodeBR, rectCamera, result);
			GetlistObj(root->_nodeTL, rectCamera, result);
			GetlistObj(root->_nodeTR, rectCamera, result);
		}
		else
		{
			for (it = root->listObj.begin(); it != root->listObj.end(); it++)
			{
				result.push_back(*it);
			}
			return;
		}
	}
}


QuadTree::~QuadTree()
{
	//f.close();
}
