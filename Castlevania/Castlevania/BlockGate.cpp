#include "BlockGate.h"
#include "Constant.h"

BlockGate* BlockGate::pStaticObj = 0;

BlockGate::BlockGate()
{	
	blockGate = new GTexture();

}

BlockGate::~BlockGate()
{
}

void BlockGate::Init()
{
	//BaseObject::LoadResource(BLOCKGATE_IMAGE, 1, 1, 0);
	blockGate->loadTextTureFromFile(BLOCKGATE_IMAGE, COLOR_LOAD_TEXTURE);
}

void BlockGate::Draw()
{
	//Sprite->Draw(x + Sprite->_FrameWidth / 2, y + Sprite->_FrameHeight / 2);
	blockGate->RenderTexture(x + blockGate->Width / 2, y + blockGate->Height / 2);
}

BlockGate* BlockGate::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new BlockGate();

	return pStaticObj;
}