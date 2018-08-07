#ifndef _QUANODE_H_
#define _QUANODE_H_
#include <d3d.h>
#include <list>

using namespace std;

class QuadNode
{
public:
	const int MIN_SIZE_OF_NODE = 400;

	int id; //Id của node
	RECT bounds; // vị trí của node
	list<int> listObj; // Danh sách các đối tượng trong node
	QuadNode* _nodeTL; // Node con left top
	QuadNode* _nodeTR; // Node con right top
	QuadNode* _nodeBL; // Node con left bottom
	QuadNode* _nodeBR; // Node con right bottom

	QuadNode();
	void SetNode(int _id);
	void SetNode(int _id, RECT _bounds, list<int> _list);
	~QuadNode();
;
};

#endif // !_QUANODE_H_


