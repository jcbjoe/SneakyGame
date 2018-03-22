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

	void increaseScore();
	int getScore();
	void setHasKey(bool x);
	bool getHasKey();

	void toggleCrouch();
	Vector3 getCameraPosition();
	bool getCrouchStatus();
private:

	int coins = 0;
	float moveSpeed = 5.0f;
	float turnSpeed = 20.0f;
	bool isCrouched = false;
	bool hasKey = false;

	FPSCamera mCamera;
};

#endif
