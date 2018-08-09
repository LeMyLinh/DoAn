#include "QuadNode.h"

QuadNode::QuadNode()
{
	this->id = 0;
	this->bounds = { 0,0,0,0 };
	this->listObj.clear();
}

void QuadNode::SetNode(int _id)
{
	this->id = _id;
}


QuadNode::~QuadNode()
{

}


void QuadNode::SetNode(int _id, RECT _bounds, list<int> _list)
{
	id = _id;
	bounds = _bounds;	
	listObj = _list;
}

