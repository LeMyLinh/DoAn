#ifndef _TILE_H_
#define _TILE_H_
#include "BaseObject.h"

class Tile:public BaseObject
{
protected:
	static Tile* pStaticObj;
public:
	Tile();
	void Init();
	static Tile* GetStaticObj();
	void Draw(int _x, int _y, int _index);
	~Tile();
};

#endif // !_TILE_H_


