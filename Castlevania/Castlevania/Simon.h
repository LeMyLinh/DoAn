#ifndef _SIMON_H_
#define _SIMON_H_
#include "BaseObject.h"
#include "GSprite.h"
#include "Object.h"
#include "Box.h"
#include "BlackBoard.h"
#include "Enemy.h"
#include "GCamera.h"
#include "ObjManager.h"
#include <vector>
#define TURN_LEFT -1
#define TURN_RIGHT 1
#define HIGHT_JUMP 64
#define SPEED_SIMON 3.5

enum State
{
	STAND =0,
	RUNING,
	JUMPING,
	SITING,
	CLIMBING_UP,
	CLIMBING_DOWN,
	FIGHTING,
	SIT_FIGHTING,
	UP_FIGHTING,
	DOWN_FIGHTING
};
class Simon: public BaseObject
{
private:
	int turn;
	State state;
	bool IsFalling; // trang thai roi
	bool IsSkill; //combo chieu
	bool IsCombo;
	bool IsMoving; //cho phep di chuyen
	bool IsFight; //Danh
	bool IsOnTheStair; //dang tren cau thang	
	bool IsJumping; //dang nhay
	bool IsOntheGround; 
	GSprite* MoringStar; //Roi
	GTexture* simonDeath;
	int lvOfMorningStar;

	float y_old;
	int oldIndex;
	State oldState;

	int inLayer; //vi tri tren map
	int sitDelay;
	bool Isfind; //dang tim duong
	Object tempobj;
	Box MorningStarBox;
	int coutIndex; // sua loi cau thang
	bool IsContinousClimb; //
	int tempMin;
	bool Isfind_Down;//tim duong xuong
	bool IsBeaten; //bi danh
	int effectDelay;
	int timeLocal;
	int timeEffect;
	bool IsInvincible;
	bool FlipStair;
	int countWall;
	bool IsStop;	
	bool IscolorEffect;
	bool b;
	int yold;
	int delayDeath;
	bool UseWP5;
	//thuoc tinh
	int HP;
	int localTime;

	int debug=0;
	int debug2 = 0;
	float debug3 = 1;
	int debug4 = 0;
	int ct =0;
	
public:
	Simon(int _x, int _y, int _inlayer);
	bool IsNextStage; // chuyen man
	bool IsAutoRun;
	void Turn(int turn);
	void SetStateFight();
	void SetState();
	void climb(Object* x);
	void climbDown(Object *x);
	void SetAnimation(State _state);
	void Update(std::vector<Object*> listObject, std::vector<int*> &listInfo, BlackBoard* blacBoard, vector<Enemy*> listEnemy, int detaltime, GCamera* camera,ObjManager* objManager);
	void Draw(int DeltaTime);
	void LoadResource(LPCWSTR resourceFile, int cols, int rows, int detalTime);
	Box GetBox();
	int GetLayerMap();
	// tim duong len cau thang.
	void TimDuong(Object o);
	void TimDuongXuong(Object* o);
	void PickUpItem(BlackBoard* blacBoard, ObjManager* objManager);
	void CollisonWithEnemy(std::vector<Enemy*> listEnemy);
	void beaten();
	void ThrowSubweapon(BlackBoard* blacBoard);
	//Kiem tra Danh
	void Fight(Object *o, std::vector<int*> &listInf,bool& fhidden);
	void FightEnemy(vector<Enemy*> listEnemy);
	void EffectColor(int delta);
	void CheckDie();
	int GetHP();
	~Simon();
};
#endif // !_SIMON_H_



