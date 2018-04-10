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
	bool getOpenedRed();
	bool getOpenedBlue();
	//int getKeyNo();
	//Sets
	void increaseScore();
	void setHasRedKey();
	void setHasBlueKey();
	void setOpenedRed();
	void setOpenedBlue();
	//void changeKeyNo(int x);
	void dropOffCoins();

	void toggleCrouch();
	Vector3 getCameraPosition();
	int getDeposited();
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

	FPSCamera mCamera;
};

#endif
