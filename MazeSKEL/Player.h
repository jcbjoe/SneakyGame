#ifndef PLAYER_H 
#define PLAYER_H 

#include <vector> 

#include "Mesh.h" 
#include "Model.h" 
#include "FPSCamera.h" 
#include "Input.h" 
#include "FX.h" 
#include "GameObjectManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Player
{
public:

	~Player()
	{
		Release();
	}
	void Update(float dTime);
	void Render(float dTime);
	void Initialise(const float&, const float&);
	void Release();

	//Gets
	int getScore();
	bool getHasRedKey();
	bool getHasBlueKey();
	bool getHasYellowKey();
	bool getOpenedRed();
	bool getOpenedBlue();
	bool getOpenedYellow();
	//int getKeyNo();
	//Sets
	void increaseScore();
	void setHasRedKey();
	void setHasBlueKey();
	void setHasYellowKey();
	void setOpenedRed();
	void setOpenedBlue();
	void setOpenedYellow();
	//void changeKeyNo(int x);
	void dropOffCoins();

	void toggleCrouch();
	Vector3 getCameraPosition();
	int getDeposited();
	void setDeposited(const int& val) { depositedCoins = val; }
	bool getCrouchStatus();
private:

	int coins = 0;
	int depositedCoins = 0;
	int keyNo = 0;
	float moveSpeed;
	float turnSpeed = 20.0f;
	bool isMoving = false;
	bool isCrouched = false;

	bool hasRedKey = false;
	bool openedRed = false;
	bool hasBlueKey = false;
	bool openedBlue = false;
	bool hasYellowKey = false;
	bool openedYellow = false;

	FPSCamera mCamera;
};

#endif
