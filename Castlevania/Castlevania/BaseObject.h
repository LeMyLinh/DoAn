#ifndef _BASEOBJECT_H_
#define _BASEOBJECT_H_
#include "GSprite.h"
#include "Object.h"

class BaseObject: public Object
{
protected:	
	GSprite* Sprite;	
public:
	BaseObject();
	BaseObject(int _id, int _type, int _x, int _y, int _Width, int _Height);
	virtual void LoadResource(LPCWSTR resourceFile,int cols,int rows, int detalTime);
	virtual void Update();
	virtual void Draw();	
	~BaseObject();
};

#endif




