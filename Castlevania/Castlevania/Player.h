#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "GSprite.h"

#define TURN_LEFT -1
#define TURN_RIGHT 1
#define GROUND_Y 350

enum States { STANDs, RUN, JUMP, SIT };

class Player
{
private:
	GSprite* _sprite;
	int x;
	int y;
	int turn;
	int vecY;
	int VecX;
	int Santo;
	States state;
public:
	Player(GSprite *sprite);
	void Update();
	void Turn(int turn);
	void Draw();
	void SetState(States _state);
	int GetY();
	int GetX();
	~Player();
};

#endif


