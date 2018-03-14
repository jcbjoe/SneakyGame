#ifndef PLAYER_H 
#define PLAYER_H 

#include <vector> 

#include "Mesh.h" 
#include "Model.h" 
#include "FPSCamera.h" 
#include "Input.h" 
#include "FX.h" 

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
	void Initialise();
	void Release();

	void toggleCrouch();
	Vector3 getCameraPosition();
	void initCamera(const float&, const float&);
	bool getCrouchStatus();
private:

	float moveSpeed = 5.0f;
	float turnSpeed = 20.0f;
	bool isCrouched = false;

	FPSCamera mCamera;
};

#endif
