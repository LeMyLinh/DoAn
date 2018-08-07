#include "GTexture.h"
#include "Global.h"



GTexture::GTexture()
{
	scale = { 1,1 };
	angle = 0;
	deep = 1;
	color = 0xffffffff;
}

GTexture::GTexture(const GTexture & ctexture)
{
	this->Texture = ctexture.Texture;
	this->angle = ctexture.angle;
	this->color = ctexture.color;
	this->deep = ctexture.deep;
	this->scale = ctexture.scale;
	this->srcRect = ctexture.srcRect;
	this->Width = ctexture.Width;
	this->Height = ctexture.Height;
}

void GTexture::loadTextTureFromFile(LPCWSTR fileName, D3DXCOLOR ColorKey)
{
	D3DXIMAGE_INFO info;
	HRESULT hr;
	hr = D3DXGetImageInfoFromFile(fileName, &info);
	if (FAILED(hr))
	{
		MessageBox(G_hWnd, L"Failed to get information from image", L"Error", MB_OK);
		return;
	}
	Width = info.Width;
	Height = info.Height;
	srcRect = { 0,0, Width,Height };
	hr = D3DXCreateTextureFromFileEx(
		G_lpDirect3DDevice,
		fileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		ColorKey,
		&info,
		0,
		&Texture
		);
	if (FAILED(hr))
	{
		MessageBox(G_hWnd, L"Failed to create texture", L"Error", MB_OK);
		return;
	}
}

void GTexture::RenderTexture(int x,int y, RECT sourceRect)
{
	this->srcRect = sourceRect;
	this->RenderTexture(x, y);
}

void GTexture::RenderTexture(int x, int y)
{
	
	D3DXVECTOR3 currentPosition(x, y, deep);
	//toa do trong the gioi thuc

	D3DXMATRIX oldMatrix;
	//ma tran luu lai phep transform cua SpriteBatch

	G_SpriteHandler->GetTransform(&oldMatrix);

	D3DXVECTOR2 centerScaleAndRotate = D3DXVECTOR2(x, y);
	//lay vi tri cua vat the lam tam xoay(vi vi tri cua vat la vi tri chinh giua cua vat)

	D3DXMATRIX matrixScalingRotate;
	//ma tran rotate, scale

	D3DXMatrixTransformation2D(&matrixScalingRotate,
		&centerScaleAndRotate,
		0.0f,
		&scale,
		&centerScaleAndRotate,
		D3DXToRadian(angle), 0);

	D3DXMATRIX finalMatrix = matrixScalingRotate * oldMatrix;

	G_SpriteHandler->SetTransform(&finalMatrix);
	//ma tran chuyen toa do vi tri cua vat the tu the gioi thuc sang toa do trong directX de ve
	D3DXVECTOR3 center((float)(srcRect.right - srcRect.left) / 2, (float)(srcRect.bottom - srcRect.top) / 2, 0);
	G_SpriteHandler->Draw(
		this->Texture,
		&srcRect,
		&center,
		&currentPosition,
		color);

	G_SpriteHandler->SetTransform(&oldMatrix);
}


void GTexture::SetDefaul()
{
	scale = { 1,1 };
	angle = 0;
	deep = 1;
	color = 0xffffffff;
	srcRect = { 0, 0, this->Width, this->Height };
}

void GTexture::SetFormat(D3DXVECTOR2 _scale, float _angle, float _deep, D3DCOLOR _color)
{
	scale = _scale;
	angle = _angle;
	deep = _deep;
	color = _color;
}

void GTexture::SetColor(D3DCOLOR _color)
{
	color = _color;
}



GTexture::~GTexture()
{
	if (Texture != NULL) Texture->Release();
}
