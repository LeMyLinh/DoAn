#ifndef _GCAMERA_H_
#define _GCAMERA_H_

#include <DirectXMath.h>
#include <d3dx9.h>

struct SaveStage
{
	int layer;
	int xObj;
	int yObj;
	int stage;
	int turn;
	float x;
	float y;
};

class GCamera
{
private:
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;

	D3DXVECTOR3 scaleFactors;
	float angle;
	int Width;
	int Height;
	int cameraX;
	int cameraY;
	int locaTime;
	bool OpenGate;
	bool CloseGate;
	int indexGate;
public:
	int widthMap;
	int xMap;
	int gate;
	SaveStage save;
	GCamera(int width, int height, float angle, D3DXVECTOR3 scaleFactors, int x, int y, int layer);
	void Update(int x, int y,int layer, bool &IsNextSatge, bool &IsAutoRun, int delta);
	void SetTransForm();
	void LockCamera();
	RECT GetRectCamera();
	~GCamera();
};

#endif // !_GCAMERA_H_



